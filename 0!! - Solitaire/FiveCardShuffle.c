// Thomas Moffet, thomasmoffet, z5061905
// F09C, Joseph Harris
// 31/03/2015
// This was an attempt to call arrays into other functions.

// Firstly, some headers.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// This is the other function (I think that I'm using the wrong syntax).
int handShuffler (int *givenHand[5]);

int main (int argc, char *argv[]) {
	
	// Initialising and assigning the array (giving it 5 values).
	int givenHand[5] = {1, 2, 3, 4, 5};
	
	// Then we call the function, passing where givenHand is.
	handShuffler (&givenHand);
	
	// Printing the results back in the main function.
	printf("givenHand[0] = %d\n", givenHand[0]);
	printf("givenHand[1] = %d\n", givenHand[1]);
	printf("givenHand[2] = %d\n", givenHand[2]);
	printf("givenHand[3] = %d\n", givenHand[3]);
	printf("givenHand[4] = %d\n", givenHand[4]);
	
	return EXIT_SUCCESS;
}

int handShuffler (int *givenHand[5]) {
	
	// Printing the initial values passed in.
	printf("givenHand[0] = %d\n", givenHand[0]);
	printf("givenHand[1] = %d\n", givenHand[1]);
	printf("givenHand[2] = %d\n", givenHand[2]);
	printf("givenHand[3] = %d\n", givenHand[3]);
	printf("givenHand[4] = %d\n", givenHand[4]);
	
	// Defining some variables.
	// This will be the ending state.
	int shuffledHand[5];
	// This one stores the value of each cell.
	int value;
	// This one stores the position of each cell.
	int selection;
	// This one notes how many iterations have happened.
	int position = 0;
	// This one is used for removing blanks.
	int blankPosition;
	
	// This determines a random seed (so the numbers are random each time).
	srand(time(NULL));
	
	// The while loop ends when it has run out of numbers to sort.
	while (position < 5) {
		// Firstly, it selects a cell based on a random number between
		// 0 and 4. Then 0 and 3 the next time, and so on.
		selection = (rand() % (5 - position));
		
		// This variable then stores what was at the spot.
		value = givenHand[selection];
		// Then that value is passed on to the ending spot.
		shuffledHand[position] = value;
		
		// This then removes the value from the old hand.
		givenHand[selection] = 0;
		// This then tells where the blank is (right where it was removed).
		blankPosition = selection;
		
		// Then, each cell is passed left until the blank is at the end
		// of the array.
		while (blankPosition < 5) {
			givenHand[blankPosition] = givenHand[blankPosition + 1];
			blankPosition++;
		}
		
		// The next position of the ending array is selected, and the
		// process repeats.
		position++;
	}
	
	// These print the values determined at the end.
	printf("givenHand[0] = %d\n", givenHand[0]);
	printf("givenHand[1] = %d\n", givenHand[1]);
	printf("givenHand[2] = %d\n", givenHand[2]);
	printf("givenHand[3] = %d\n", givenHand[3]);
	printf("givenHand[4] = %d\n", givenHand[4]);
	
	printf("shuffledHand[0] = %d\n", shuffledHand[0]);
	printf("shuffledHand[1] = %d\n", shuffledHand[1]);
	printf("shuffledHand[2] = %d\n", shuffledHand[2]);
	printf("shuffledHand[3] = %d\n", shuffledHand[3]);
	printf("shuffledHand[4] = %d\n", shuffledHand[4]);
	
	// And this copies all the values back to the original cell.
	givenHand[0] = shuffledHand[0];
	givenHand[1] = shuffledHand[1];
	givenHand[2] = shuffledHand[2];
	givenHand[3] = shuffledHand[3];
	givenHand[4] = shuffledHand[4];
	
	return EXIT_SUCCESS;
}