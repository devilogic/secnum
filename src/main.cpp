#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "secnum.h"

#define UNUSED __attribute__((unused))

//#ifdef APP

int main(int argc UNUSED, char* argv[] UNUSED) {
	SecNum x;
	SecNum y;
	x = 100;
	y = 3000000;
	SecNum z = x * y;


   	// x.add(1);
	// x.sub(0x12345);
	printf("0x%x\n", z.get());
	return 0;
} 

//#endif
