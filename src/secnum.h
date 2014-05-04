#ifndef _SEC_NUM_H
#define _SEC_NUM_H

#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct secint {
    unsigned char v0;
    unsigned char v1;
    unsigned char v2;
    unsigned char v3;
    unsigned char v4;
    unsigned char v5;
    unsigned char v6;
    unsigned char v7;
    unsigned char v8;
    unsigned char v9;
    unsigned char v10;
    unsigned char v11;
    unsigned char v12;
    unsigned char v13;
    unsigned char v14;
    unsigned char v15;
    unsigned char v16;
    unsigned char v17;
    unsigned char v18;
    unsigned char v19;
    unsigned char v20;
    unsigned char v21;
    unsigned char v22;
    unsigned char v23;
    unsigned char v24;
    unsigned char v25;
    unsigned char v26;
    unsigned char v27;
    unsigned char v28;
    unsigned char v29;
    unsigned char v30;
    unsigned char v31;
};

class SecNum {
public:
    SecNum();
    virtual ~SecNum();
    
public:
	SecNum operator=(SecNum& v);
	SecNum operator=(unsigned v);

	//SecNum operator<<(SecNum& v);
	SecNum operator<<(unsigned v);

	//SecNum operator>>(SecNum& v);
	SecNum operator>>(unsigned v);

	SecNum operator+(SecNum& v);
	SecNum operator+(unsigned v);

	SecNum operator-(SecNum& v);
	SecNum operator-(unsigned v);

	SecNum operator*(SecNum& v);
	SecNum operator*(unsigned v);

	SecNum operator/(SecNum& v);
	SecNum operator/(unsigned v);

	SecNum operator%(SecNum& v);
	SecNum operator%(unsigned v);

	bool operator==(SecNum& v);
	bool operator==(unsigned v);

	bool operator!=(SecNum& v);
	bool operator!=(unsigned v);

	bool operator>(SecNum& v);
	bool operator>(unsigned v);

	bool operator<(SecNum& v);
	bool operator<(unsigned v);

	bool operator>=(SecNum& v);
	bool operator>=(unsigned v);

	bool operator<=(SecNum& v);
	bool operator<=(unsigned v);
    
public:
    int get_max_bits();
    struct secint* get_secint();
    void zero();

    int set(unsigned v);
    int set(struct secint& v);
    int set(SecNum& v);

    unsigned get();
    unsigned get_valid_bits();
    unsigned get_bytes_idx();
    int is_neg();
    int is_zero();

    int eq(SecNum& v);
    int gt(SecNum& v);
    int lt(SecNum& v);

    int shl(unsigned v);
	SecNum xshl(unsigned v);

    int shr(unsigned v);
	SecNum xshr(unsigned v);

    int add(unsigned v);
	SecNum xadd(unsigned v);
 
    int add(SecNum& v);
	SecNum xadd(SecNum& v);

    /* 在求减法的时候，注意传入的v值的范围只能在[0, 0x7FFFFFFF]之间
     * 因为最高位为符号位。这里的数值运算将直接把减数换算成补码来进行
     * 加法运算，注意v传入的范围。
     */
    int sub(unsigned v);
	SecNum xsub(unsigned v);

    int sub(SecNum& v);
	SecNum xsub(SecNum& v);

    int mul(unsigned v);
	SecNum xmul(unsigned v);

    int mul(SecNum& v);
	SecNum xmul(SecNum& v);

    /* 这里不模拟浮点运算，所有导致精度不够，如果出现小数时，按照完全进位来算 */
    int div(unsigned v, SecNum& r);
	SecNum xdiv(unsigned v, SecNum& r);

    int div(SecNum& v, SecNum& r);
	SecNum xdiv(SecNum& v, SecNum& r);

private:
    void set_internal(unsigned v);
    unsigned add_internal(unsigned char x, unsigned char y, unsigned char* z);
	void anticode(unsigned char* v);

private:
    struct secint _secnum;
    int _bytes_idx;
};

extern SecNum gZero;

#endif
