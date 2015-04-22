// Thomas Moffet, thomasmoffet, z5061905
// F09C, Joseph Harris
// 13/03/2015
// This program encrypts a message.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "encryptionChar.h"

int main (int argc, char *argv[]) {

	char inputChar;
	char returnChar;
	int encryptionLevel = 0;

	printf("\n");
	printf("This program will encrypt/decrypt a message.\n");
	printf("What level do you want you encryption to be? (between 0 to 25) ");
	scanf("%d", &encryptionLevel);
	printf("Now you will type your message.\n");
	printf("When you're done, type @.\n\n");
	printf("CRYPT | INPUT\n-------------\n");
	
	
	while (inputChar != '@') {
		inputChar = 0;
		gets(&inputChar);
		returnChar = encryptChar (inputChar, encryptionLevel);
		//printf("  IN = %d | OUT = %d", inputChar, returnChar);
		printf("  %c   |   ", returnChar);
	}
	
	printf("\n");
	printf("Share this message with your friends...woooooh...\n");
	
	return EXIT_SUCCESS;
}