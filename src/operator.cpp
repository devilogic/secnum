#include "secnum.h"

SecNum SecNum::operator=(SecNum v) {
	memcpy(&this->_secnum, v.get_secint(), sizeof (struct secint));
	return *this;
}

SecNum SecNum::operator=(unsigned v) {
	this->set(v);
	return *this;
}

// SecNum SecNum::operator<<(SecNum& v) {
// 	return xshl(v);
// }

SecNum SecNum::operator<<(unsigned v) {
	return xshl(v);
}

// SecNum SecNum::operator>>(SecNum& v) {
// 	return xshr(v);
// }

SecNum SecNum::operator>>(unsigned v) {
	return xshl(v);
}

SecNum SecNum::operator+(SecNum& v) {
	return xadd(v);
}

SecNum SecNum::operator+(unsigned v) {
	return xadd(v);
}

SecNum SecNum::operator-(SecNum& v) {
	return xsub(v);
}

SecNum SecNum::operator-(unsigned v) {
	return xsub(v);
}

SecNum SecNum::operator*(SecNum& v) {
	return xmul(v);
}

SecNum SecNum::operator*(unsigned v) {
	return xmul(v);
}

SecNum SecNum::operator/(SecNum& v) {
	SecNum r;
	return xdiv(v, r);
}

SecNum SecNum::operator/(unsigned v) {
	SecNum r;
	return xdiv(v, r);
}

SecNum SecNum::operator%(SecNum& v) {
	SecNum r;
	xdiv(v, r);
	return r;
}

SecNum SecNum::operator%(unsigned v) {
	SecNum r;
	xdiv(v, r);
	return r;
}
    
bool SecNum::operator==(SecNum& v) {
	return eq(v);
}

bool SecNum::operator==(unsigned v) {
	SecNum tmp;
	tmp.set(v);
	return eq(tmp);
}

bool SecNum::operator!=(unsigned v) {
	SecNum tmp;
	tmp.set(v);
	return !eq(tmp);
}

bool SecNum::operator!=(SecNum& v) {
	return !eq(v);
}

bool SecNum::operator>(unsigned v) {
	SecNum tmp;
	tmp.set(v);
	return gt(tmp);
}

bool SecNum::operator>(SecNum& v) {
	return gt(v);
}

bool SecNum::operator<(unsigned v) {
	SecNum tmp;
	tmp.set(v);
	return lt(tmp);
}

bool SecNum::operator<(SecNum& v) {
	return lt(v);
}

bool SecNum::operator>=(unsigned v) {
	SecNum tmp;
	tmp.set(v);
	return (gt(tmp) || eq(tmp));
}

bool SecNum::operator>=(SecNum& v) {
	return (gt(v) || eq(v));
}

bool SecNum::operator<=(unsigned v) {
	SecNum tmp;
	tmp.set(v);
	return (lt(tmp) || eq(tmp));
}

bool SecNum::operator<=(SecNum& v) {
	return (lt(v) || eq(v));
}
