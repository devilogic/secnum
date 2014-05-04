#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "secnum.h"

#define UNUSED __attribute__((unused))

//#ifdef APP

int main(int argc UNUSED, char* argv[] UNUSED) {
	SecNum x;
	SecNum y;
	x.set(0x12345);
	y.set(0x12345);
	//SecNum z = x / 1;


   	// x.add(1);
	// x.sub(0x12345);
	printf("0x%4x\n", z.get());
	return 0;
} 

//#endif
