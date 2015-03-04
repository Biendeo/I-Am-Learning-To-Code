// Start by including this classic header.
#include <stdio.h>

// This is the main function, it starts normally.
int main () {
	
	// This prints stuff on the screen with a new line on the end.
	printf("Bananas!\n");
	
	// This wants the user to hit Enter before it finishes.
	getchar();
	
	// Sometimes C compilers don't know what to do if they don't get at least some return. This is just here in case.
	return 0;
}
