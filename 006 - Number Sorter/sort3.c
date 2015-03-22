// Thomas Moffet, thomasmoffet, z5061905
// F09C, Joseph Harris
// 13/03/2015
// This program sorts three numbers.

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {

	int num1;
	int num2;
	int num3;
	
	int numRegister;

	/*
		THE LOGIC
	
		If num1 is greater than num2,
			copy num2 to numRegister, copy num1 to num2,
			and copy numRegister to num1.
			
		If num2 is greater than num3,
			copy num3 to numRegister, copy num2 to num3,
			and copy numRegister to num2.
			
		If num1 is greater than num2,
			copy num2 to numRegister, copy num1 to num2,
			and copy numRegister to num1.
			
		If num1 is greater than num3,
			copy num3 to numRegister, copy num1 to num3,
			and copy numRegister to num1.
	*/
	
	scanf("%d %d %d", &num1, &num2, &num3);
	
	if (num1 > num2) {
		numRegister = num2;
		num2 = num1;
		num1 = numRegister;
	}
	
	if (num2 > num3) {
		numRegister = num3;
		num3 = num2;
		num2 = numRegister;
	}
	
	if (num1 > num2) {
		numRegister = num2;
		num2 = num1;
		num1 = numRegister;
	}
	
	if (num1 > num3) {
		numRegister = num3;
		num3 = num1;
		num1 = numRegister;
	}
	
	printf("%d\n%d\n%d\n", num1, num2, num3);
	return EXIT_SUCCESS;
}