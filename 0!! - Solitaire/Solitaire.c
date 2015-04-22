#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION_NUMBER test1

#define NORMAL_GAME 1
#define DEBUG_GAME  2

// These define the cards (0 is blank).

#define  cAS  1
#define  c2S  2
#define  c3S  3
#define  c4S  4
#define  c5S  5
#define  c6S  6
#define  c7S  7
#define  c8S  8
#define  c9S  9
#define c10S 10
#define  cJS 11
#define  cQS 12
#define  cKS 13

#define  cAC 14
#define  c2C 15
#define  c3C 16
#define  c4C 17
#define  c5C 18
#define  c6C 19
#define  c7C 20
#define  c8C 21
#define  c9C 22
#define c10C 23
#define  cJC 24
#define  cQC 25
#define  cKC 26

#define  cAH 27
#define  c2H 28
#define  c3H 29
#define  c4H 30
#define  c5H 31
#define  c6H 32
#define  c7H 33
#define  c8H 34
#define  c9H 35
#define c10H 36
#define  cJH 37
#define  cQH 38
#define  cKH 39

#define  cAD 40
#define  c2D 41
#define  c3D 42
#define  c4D 43
#define  c5D 44
#define  c6D 45
#define  c7D 46
#define  c8D 47
#define  c9D 48
#define c10D 49
#define  cJD 50
#define  cQD 51
#define  cKD 52

typedef struct {
	int size;
	int order[52];
} CardStack;

int startupSplash (void);
void gameTime (int modeControl);
CardStack deckCreate (int modeControl, CardStack deck);
CardStack shuffleDeck (int modeControl, CardStack deck);
CardStack blankRemoval (int modeControl, CardStack pile);
void endingSplash (void);

int main (int argc, char *argv[]) {
	int modeControl;
	//startupSplash ();
	if (modeControl > 0) {
		gameTime (modeControl);
	}
	endingSplash ();
	return EXIT_SUCCESS;
}

int startupSplash (void) {
	int modeControl = 0;
	char inputString[0];
	
	printf("+---------------------+\n");
	printf("|                     |\n");
	printf("|      SOLITAIRE      |\n");
	printf("|                     |\n");
	printf("+---------------------+\n\n");
	printf("Version VERSION_NUMBER\n\n");
	printf("Type START to start. Type DEBUG to use debug features.\n");
	printf("Use lower-case letters only here.\n");
	
	while (modeControl == 0) {
		scanf("%s", &inputString);
		
		if (strcmp(inputString, "start") == 0) {
			modeControl = 1;
		}
		else if (strcmp(inputString, "debug") == 0) {
			modeControl = 2;
		}
		else if (strcmp(inputString, "exit") == 0 || strcmp(inputString, "quit") == 0) {
			modeControl = -1;
		}
		else {
			printf("\nType START or DEBUG.\n");
		}
	}
	
	return modeControl;
}

void gameTime (int modeControl) {
	CardStack deck;
	deck.size = 52;
	deckCreate (modeControl, deck);
	
	shuffleDeck (modeControl, deck);
}

CardStack deckCreate (int modeControl, CardStack deck) {
	int position = 0;
	
	while (position < 52) {
		deck.order[position] = position + 1;
		//if (modeControl == 2) {
			printf("%d\n", deck.order[position]);
		//}
		position++;
	}
	printf("\n");
}

CardStack shuffleDeck (int modeControl, CardStack deck) {
	CardStack shuffledDeck;
	
	int maxRandom = 52;
	int randomStore;
	int cardStore;
	int position = 0;
	
	while (maxRandom > 1) {
		randomStore = (rand() % maxRandom);
		
		//if (modeControl == DEBUG_GAME) {
			printf("randomStore = %d\n", randomStore);
		//}
		
		cardStore = deck.order[randomStore];
		shuffledDeck.order[position] = cardStore;
		deck.order[randomStore] = 0;
		printf("%d\n", cardStore);
		//blankRemoval (modeControl, deck);
		
		maxRandom--;
		position++;
	}
	
	return shuffledDeck;
}

//CardStack blankRemoval (int modeControl, CardStack pile) {
	
//}

void endingSplash (void) {
	printf("+---------------------+\n");
	printf("|                     |\n");
	printf("| Thanks for playing! |\n");
	printf("|                     |\n");
	printf("+---------------------+\n\n");
}