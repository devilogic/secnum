#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "secnum.h"

#define UNUSED __attribute__((unused))

//#ifdef APP

int main(int argc UNUSED, char* argv[] UNUSED) {
	SecNum x;
	SecNum r;
	x.set(0x124fff);
	x.div(0x124, r);
   	// x.add(1);
	// x.sub(0x12345);
	printf("0x%4x, 0x%4x\n", x.get(), r.get());
	return 0;
} 

//#endif
