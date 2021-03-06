#include "secnum.h"

#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_BITS              32
#define MAX_BITS_GROUP        MAX_BITS / 8

SecNum gZero;

SecNum::SecNum() :  _bytes_idx(0) {
	zero();
}

SecNum::~SecNum() {}

int SecNum::get_max_bits() {
	return MAX_BITS;
}

struct secint* SecNum::get_secint() {
	return &_secnum;
}

void SecNum::zero() {
	memset(&_secnum, 0, sizeof(struct secint));
}

int SecNum::set(unsigned v) {
	set_internal(v);
	return 0;
}

int SecNum::set(struct secint& v) {
	memcpy(&_secnum, &v, sizeof(struct secint));
	return 0;
}

int SecNum::set(SecNum& v) {
	memcpy(&_secnum, v.get_secint(), sizeof(struct secint));
	return 0;
}

#define COUNT_VALID_BYTES(x, v)					\
	(x) += (v) & 0xFF ? 1 : 0;					\
	(x) += (v) & 0xFF00 ? 1 : 0;				\
	(x) += (v) & 0xFF0000 ? 1 : 0;				\
	(x) += (v) & 0xFF000000 ? 1 : 0;

void SecNum::set_internal(unsigned v) {
	if (0 == v) {
		zero();
        return;
	}

	unsigned char* x = reinterpret_cast<unsigned char*>(&_secnum);
	unsigned mask = 1, i = 0;
	while (mask) {
		*(x + i) = (v & mask) ? 1 : 0;
		mask = mask << 1;
		i++;
	}
	COUNT_VALID_BYTES(_bytes_idx, v);
}

unsigned SecNum::get() {
	unsigned char* x = reinterpret_cast<unsigned char*>(&_secnum);
	unsigned i = 0, v = 0;

	while (i < 32) {
		v |= *(x + i) << i;
		i++;
	}

	return v;
}

unsigned SecNum::get_valid_bits() {
	unsigned i = 31;
	unsigned char* y = reinterpret_cast<unsigned char*>(&_secnum);
	do {
		if (y[i]) {
			break;
		}
	} while (i--);
	i++;
	
	return i;
}

unsigned SecNum::get_bytes_idx() {
	return _bytes_idx;
}

int SecNum::is_neg() {
	return _secnum.v31;
}

int SecNum::is_zero() {	
	return !memcmp(&_secnum, gZero.get_secint(), sizeof(struct secint));
}

int SecNum::eq(SecNum& v) {
	return !memcmp(&_secnum, v.get_secint(), sizeof(struct secint));
}

int SecNum::gt(SecNum& v) {
	unsigned a = get_valid_bits();
	unsigned b = v.get_valid_bits();
	if (a > b)
		return 1;
	else if (a < b)
		return 0;
	else {
		unsigned char* x = reinterpret_cast<unsigned char*>(&_secnum);
		unsigned char* y = reinterpret_cast<unsigned char*>(v.get_secint());

		for (int i = (int)(a-1); i >= 0; i--) {
			if (x[i] > y[i]) {
				return 1;
			} else if (x[i] < y[i]) {
				return 0;
			}
	    }/* end for */
	}

	return 0;
}

int SecNum::lt(SecNum& v) {
	return !gt(v);
}

int SecNum::shl(unsigned v) {
	unsigned i = 31;
	unsigned char* x = reinterpret_cast<unsigned char*>(&_secnum);

	if (v > 31) v = 31;

	while (v--) {
		i = 31;
		do {
			if (0 == i) {
				x[0] = 0;
			} else {
				x[i] = x[i-1];
			}
		} while (i--);
	}

	return 0;
}


int SecNum::shr(unsigned v) {
	unsigned char* x = reinterpret_cast<unsigned char*>(&_secnum);
	unsigned char y[32];

	for (int i = 0, j = 31; i < 32; i++, j--) {
		y[j] = x[i];
	}

	memcpy(x, &y[0], 32);
	shl(v);

	for (int i = 0, j = 31; i < 32; i++, j--) {
		y[j] = x[i];
	}
	memcpy(x, &y[0], 32);

	return 0;
}


static inline
unsigned add_internal(unsigned char x, unsigned char y, unsigned char* z) {
	*z = (x & 0x01) + (y & 0x01);
	unsigned plus = (*z & 0x02) >> 1;
	*z &= 0x01;

	return plus;
}

int SecNum::add(unsigned v) {
    SecNum n;
    n.set(v);
    return add(n);
}

int SecNum::add(SecNum& v) {
	SecNum result;
	unsigned char* x = reinterpret_cast<unsigned char*>(&_secnum);
	unsigned char* y = reinterpret_cast<unsigned char*>(v.get_secint());
	unsigned char* z = reinterpret_cast<unsigned char*>(result.get_secint());

	unsigned i = 0;
    unsigned char plus = 0, tmp = 0;

	while (i < 32) {
		*(z+i) = plus & 0x01;
		plus = add_internal(*(x+i), *(y+i), &tmp);
		plus |= add_internal(tmp, *(z+i), z+i);
		i++;
	}

	set(result);

    return 0;
}

int SecNum::sub(unsigned v) {
	SecNum n;
    n.set(v);
    return sub(n);
}

static inline
void anticode(unsigned char* v) {
	unsigned i = 0;
	while (i < 31) {
		*(v+i) = ~(*(v+i));
		i++;
	}

	v[31] = 1;   /* 转换成负数 */
}

int SecNum::sub(SecNum& v) {
	SecNum tmp;
	tmp.set(v);

	unsigned char* x = reinterpret_cast<unsigned char*>(tmp.get_secint());
	anticode(x);  	/* 求v的反码 */

	struct secint* y = reinterpret_cast<struct secint*>(x);
	tmp.set(*y);
	tmp.add(1);     /* 求v的补码 */

	return add(tmp);
}

int SecNum::mul(unsigned v) {
	SecNum n;
    n.set(v);
    return mul(n);
}

int SecNum::mul(SecNum& v) {
	if (v.is_zero()) {
		zero();
		return 0;
	}

	unsigned char* y = reinterpret_cast<unsigned char*>(v.get_secint());	
	unsigned i = get_valid_bits();

	unsigned j = 0;
	SecNum tmp, tmp2;
	while (i--) {
		if (y[j]) {
			tmp.set(_secnum);
			tmp.shl(j);
			tmp2.add(tmp);
		}
		j++;
	}

	set(tmp2);

	return 0;
}

int SecNum::div(unsigned v, SecNum& r) {
	SecNum n;
    n.set(v);
    return div(n, r);
}

int SecNum::div(SecNum& v, SecNum& r) {
	if (lt(v)) {
		r.set(_secnum);
		zero();
		return 0;
	}

	unsigned q = 1;
	do {
		sub(v);
		q++;
	} while (gt(v));

	r.set(*this);      /* 余数 */
	set(q);            /* 商 */

	return 0;
}
