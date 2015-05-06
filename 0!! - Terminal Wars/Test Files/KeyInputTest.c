#include <stdio.h>
#include <stdlib.h>
#include "rlutil.h"

int main (int argc, char *argv[]) {
	char star = 1;
	int keyPress = 0;
	while (star == 1) {
		printf("keyPress = %d\n", keyPress);
		keyPress = getkey();
	}
	return EXIT_SUCCESS;
} 