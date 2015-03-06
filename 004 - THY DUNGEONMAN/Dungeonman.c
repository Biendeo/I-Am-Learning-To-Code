// Thomas Moffet, thomasmoffet, z5061905
// F09C, Joeseph Harris
// 6/03/2015
// This was an attempt to play around with multiple functions

// Thy Dungeonman is a free flash parody of old '80s adventure games.
// http://homestarrunner.com/dungeonman.html
// This program is an attempt to recreate this entirely in C.
// Most of this was
// There's a few things that need to be done to make it perfect.
// Currently right now the general look and get commands don't work.
// Also the thing "crashes" when you try to exit it.
// Finally, scores aren't fully implemented.
// However, it mostly works right now, so that's good. :)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char inputText[] = "0";
int gotScroll = 0;
int gotTrinket = 0;
int currentRoom = 0;
int score = 0;

int main () {
	printf("\n    Thy Dungeonman\n");
	printf("\n /\\      /\\     /\\");
	printf("\n ||/----\\||     ||");
	printf("\n \\_------_/     ||");
	printf("\n  / o  o \\      ||");
	printf("\n  /  ||  \\   o__||__o");
	printf("\n  / ---- \\    \\----/");
	printf("\n  /\\/\\/\\/\\      ||");
	printf("\n                oo\n");
	printf("\nHit Enter to enter yon dungeon.");
	getchar();
	
	printf("\n\n\n\n");
	printf("THY DUNGEONMAN\n\n");
	printf("YOU ARE THY DUNGEONMAN!\n\n\n");
	room1();
}

int enterString(){
	printf("\nWhat wouldst thou deau?\n\n");
	inputText[0] = '\0';
	gets(inputText);
	
	// If I want to debug the string, I remove the comment bit here.
	// debugString();
	
	printf("\n\n\n\n");
	
	// These are for moving between the rooms.
	
	if (strcmp(inputText, "north") == 0 && currentRoom == 1) {
		room2();
	}
	else if (strcmp(inputText, "south") == 0 && currentRoom == 2){
		room1();
	}
	else if (strcmp(inputText, "south") == 0 && currentRoom == 1){
		room3();
	}
	else if (strcmp(inputText, "north") == 0 && currentRoom == 3){
		room1();
	}
	else if (strcmp(inputText, "dennis") == 0 && currentRoom == 1){
		room4();
	}
	else if (strcmp(inputText, "not dennis") == 0 && currentRoom == 4){
		room1();
	}
	
	// These are for picking up items.
	
	else if (strcmp(inputText, "get flask") == 0 && currentRoom == 1){
		gettingFlask();
	}
	else if (strcmp(inputText, "get scroll") == 0 && currentRoom == 1 && gotScroll == 0){
		gettingScroll();
	}
	else if (strcmp(inputText, "get scroll") == 0 && currentRoom == 1 && gotScroll == 1){
		alreadyGotScroll();
	}
	else if (strcmp(inputText, "get trinket") == 0 && currentRoom == 3 && gotTrinket == 0){
		gettingTrinket();
	}
	else if (strcmp(inputText, "get trinket") == 0 && currentRoom == 3 && gotTrinket == 1){
		alreadyGotTrinket();
	}
	
	// These are for looking at items.
	
	else if (strcmp(inputText, "look flask") == 0 && currentRoom == 1){
		lookFlask();
	}	
	else if (strcmp(inputText, "look scroll") == 0 && currentRoom == 1 && gotScroll == 0){
		lookScroll();
	}
	else if (strcmp(inputText, "look rope") == 0 && currentRoom == 2){
		lookRope();
	}
	else if (strcmp(inputText, "look parapets") == 0 && currentRoom == 2){
		lookParapets();
	}
	else if (strcmp(inputText, "look trinket") == 0 && currentRoom == 3 && gotTrinket == 0){
		lookTrinketFar();
	}
	else if (strcmp(inputText, "look trinket") == 0 && gotTrinket == 1){
		lookTrinketClose();
	}
	else if (strcmp(inputText, "look dennis") == 0 && currentRoom == 4){
		lookDennis();
	}
	
	// This one is for talking to Dennis.
	
	else if (strcmp(inputText, "talk dennis") == 0 && currentRoom == 4){
		talkDennis();
	}
	
	// These are the ending conditions.
	
	else if (strcmp(inputText, "give trinket") == 0 && currentRoom == 4 && gotTrinket == 1){
		endingWin();
	}
	else if (strcmp(inputText, "die") == 0){
		endingDeath();
	}
	else if (strcmp(inputText, "get rope") == 0 && currentRoom == 2){
		endingRope();
	}
	
	// These are the null commands.
	
	else if (strcmp(inputText, "get") == 0){
		getNone();
	}
	else if (strcmp(inputText, "look") == 0){
		lookNone();
	}
	else {
		printf("That does not computeth. Type HELP is thou needs of it.\n");
		enterString();
	}
}

// In case I want to see what the string gets.

int debugString() {
	printf("\nFor debugging reasons, you entered: ");
	puts(inputText);
}

int room1() {
	
	currentRoom = 1;
	
	printf("Ye find yeself in yon dungeon. ");
	if (gotScroll = 0)
	{
		printf("Ye see a SCROLL. Behind ye SCROLL is a FLASK.\n");
	}
	else if (gotScroll = 1)
	{
		printf("Back yonder there is a FLASK.\n");
	}
	printf("Obvious exits are NORTH, SOUTH, and DENNIS.\n");
	enterString();
}

int room2() {
	
	currentRoom = 2;
	
	printf("You go NORTH through yon corridor. You arrive at parapets.\nYe see a ROPE. Obvious exits are SOUTH.\n");
	enterString();
}

int room3() {
	
	currentRoom = 3;
	
	printf("You head south to an embankment. Or maybe a chasm. You can't\ndecide which. Anyway, ye spies a TRINKET. Obvious exits are NORTH.\n");
	enterString();
}

int room4() {
	
	currentRoom = 4;
	
	printf("Ye arrive at Dennis. He wears a sporty frock coat and a long\njimberjam. He paces about nervously. Obvious exits are NOT DENNIS.\n");
	enterString();
}

int gettingFlask() {
	printf("Ye cannot get the FLASK. It is firmly bolted to a wall which is bolted\nto the rest of the dungeon which is probably bolted to a castle.\nNever you mind.\n");
	enterString();
}

int gettingScroll() {
	printf("Ye takes the SCROLL and reads of it. It doth say:\n\nBEWARE, READER OF YE SCROLL, DANGERS AWAIT TO THE -\n\nThe SCROLL disappears in thy hands with ye olde ZAP!\n");
	gotScroll = 1;
	enterString();
}

int alreadyGotScroll() {
	printf("Ye doth suffer from memory loss. YE SCROLL is no more. Honestly.\n");
	enterString();
}

int gettingTrinket() {
	printf("Ye getsts yon TRINKET and discover it to be a bauble.\nYou rejoice at your good fortune. You shove the TRINKET in your pouchel.\nIt kinda hurts.\n");
	gotTrinket = 1;
	enterString();
}

int gettingTrinketLooked() {
	printf("Ye getsts yon TRINKET and discover it to be a bauble.\nYou rejoice at your good fortune. You shove the TRINKET in your pouchel.\nIt kinda hurts.\n");
	gotTrinket = 1;
	enterString();
}

int alreadyGotTrinket() {
	printf("Sigh. The trinket is in thou pouchel. Recallest thou?\n");
	enterString();
}

int lookFlask() {
	printf("Looks like you could quaff some serious mead out of that thing.\n");
	enterString();
}

int lookScroll() {
	printf("Parchment, definitely parchment. I'd recognize it anywhere.\n");
	enterString();
}

int lookRope() {
	printf("It looks okay. You've seen better.\n");
	enterString();
}

int lookParapets() {
	printf("Well, they're parapets. This much we know for sure.\n");
	enterString();
}

int lookTrinketFar() {
	printf("Quit looking! Just get it already.\n");
	enterString();
}

int lookTrinketClose() {
	printf("Just a bulge in thou pouchel at thist point.\n");
	enterString();
}

int lookDennis() {
	printf("That jimberjam really makes the outfit.\n");
	enterString();
}

int talkDennis() {
	printf("You engage Dennis in lesiurely discussion. Ye learns that his\njimberham was purchased on sale at a discount market and that he\nenjoys pacing about nervously.\nYou become bored and begin thinking about parapets.\n");
	enterString();
}

int getNone() {
	printf("Thou cannotst get that. Quit making stuffeth up!\n");
	enterString();
}

int lookNone() {
	printf("It looketh pretty awesome.\n");
	enterString();
}

int endingDeath() {
	score = score - 100;
	printf("\n\nThat wasn't very smart.\nYour score was: %d", score);
	playAgain();
}

int endingRope() {
	printf("\n\nThat wasn't very smart.\nYour score was: %d", score);
	playAgain();
}

int endingWin() {
	printf("A novel idea! You givst the TRINKET to Dennis and he happily\nagrees to tell you what parapets are. With this new\nknowledge, ye escapes from yon dungeon in order to search for new dungeons and\nto remain...\n\n");
	printf("THY DUNGEONMAN!!\nYou hath won! Congraturation!\n");
	printf("Your score was: %d", score);
	playAgain();
}

int playAgain(){
	printf("\n\nPlay again? [Y/N] ");
	char exitChar = 0;
	scanf("%c", &exitChar);
	if (exitChar == 'y' || exitChar == 'Y'){
		restartGame();
	}
	else if (exitChar == 'n' || exitChar == 'N'){
		return 0;
		exit(0);
	}
	else {
		playAgain();
	}
}

int restartGame(){
	int gotScroll = 0;
	int gotTrinket = 0;
	int currentRoom = 0;
	int score = 0;
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	main();
}