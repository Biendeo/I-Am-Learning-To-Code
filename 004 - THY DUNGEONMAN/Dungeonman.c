// Thomas Moffet, thomasmoffet, z5061905
// F09C, Joeseph Harris
// 6/03/2015
// This was an attempt to play around with multiple functions

// Thy Dungeonman is a free flash parody of old '80s adventure games.
// http://homestarrunner.com/dungeonman.html
// This program is an attempt to recreate this entirely in C.
// All of this was done by scratch, recreating the game's features.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char inputText[] = "0";
int gotFlask = 0;
int gotScroll = 0;
int gotTrinket = 0;
int currentRoom = 0;
int score = 0;
int debugMode = 0;

int debugProgram();
int enterString();
int debugString();
int room1();
int room2();
int room3();
int room4();
int gettingFlask();
int gettingScroll();
int gettingDagger();
int alreadyGotScroll();
int gettingTrinket();
int alreadyGotTrinket();
int givingDennisNot();
int lookFlask();
int lookScroll();
int lookRope();
int lookParapets();
int lookTrinketFar();
int lookTrinketClose();
int lookDennis();
int talkDennis();
int getNone();
int lookNone();
int goNone();
int talkNone();
int giveNone();
int smellNone();
int danceNone();
int endingDeath();
int endingFlask();
int endingRope();
int endingWin();
int playAgain();
int restartGame();

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
	printf("\n~~~~~\n\n");
	
	if (debugMode == 1) {
		debugProgram();
	}
	
	printf("\n\n");
	printf("THY DUNGEONMAN\n\n");
	printf("YOU ARE THY DUNGEONMAN!\n\n\n");
	room1();
	return EXIT_SUCCESS;
}

int debugProgram() {
	printf("There are currently a few things that are not implemented.\n - Only use lower-case letters right now.\n - The GO, TALK and GIVE commands don\'t get the item listed yet.\n - The score isn\'t 100 percent perfect.\n - Some of the text needs to be re-aligned.\n - The TRINKET does not disappear.\n - The game crashes if you win and don't want to play again.\n\n~~~~~");
	return EXIT_SUCCESS;
}

int enterString(){
	printf("\nWhat wouldst thou deau?\n\n");
	inputText[0] = '\0';
	gets(inputText);
	
	if (debugMode == 1) {
		debugString();	
	}
	
	printf("\n\n~~~~~\n\n");
	
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
	
	else if (strcmp(inputText, "get dagger") == 0){
		gettingDagger();
	}
	else if (strcmp(inputText, "get flask") == 0 && currentRoom == 1 && gotFlask <= 1){
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
	else if ((strcmp(inputText, "give trinket") == 0 || strcmp(inputText, "give trinket to dennis") == 0) && currentRoom == 4 && gotTrinket == 0){
		givingDennisNot();
	}
	
	// These are the ending conditions.
	
	else if ((strcmp(inputText, "give trinket") == 0 || strcmp(inputText, "give trinket to dennis") == 0) && currentRoom == 4 && gotTrinket == 1){
		endingWin();
	}
	else if (strcmp(inputText, "die") == 0){
		endingDeath();
	}
	else if (strcmp(inputText, "get flask") == 0 && currentRoom == 1 && gotFlask == 2){
		endingFlask();
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
	else if (strcmp(inputText, "dance") == 0){
		danceNone();
	}
	else if (strcmp(inputText, "talk") == 0){
		talkNone();
	}
	else if (strcmp(inputText, "give") == 0){
		giveNone();
	}
	else if (strcmp(inputText, "smell") == 0 || strcmp(inputText, "sniff") == 0){
		smellNone();
	}
	else if (strcmp(inputText, "go") == 0){
		goNone();
	}
	
	// This is for enabling the debug mode.
	else if (strcmp(inputText, "debug") == 0 && debugMode == 0){
		debugMode = 1;
		main();
	}
	
	else if (strcmp(inputText, "debug") == 0 && debugMode == 1){
		debugMode = 0;
		main();
	}
	
	else {
		printf("That does not computeth. Type HELP is thou needs of it.\n");
		enterString();
	}
	return EXIT_SUCCESS;
}

// In case I want to see what the string gets.

int debugString() {
	printf("\n\n~~~~~\n\nFor debugging reasons, you entered: ");
	puts(inputText);
	printf("\ngotFlask = %d", gotFlask);
	printf("\ngotScroll = %d", gotScroll);
	printf("\ngotTrinket = %d", gotTrinket);
	printf("\ncurrentRoom = %d", currentRoom);
	printf("\nscore = %d", score);
	return EXIT_SUCCESS;
}

int room1() {
	
	currentRoom = 1;
	
	printf("Ye find yeself in yon dungeon. ");
	if (gotScroll == 0) {
		printf("Ye see a SCROLL. Behind ye SCROLL is a FLASK.\n");
	}
	else if (gotScroll == 1) {
		printf("Back yonder there is a FLASK.\n");
	}
	printf("Obvious exits are NORTH, SOUTH, and DENNIS.\n");
	enterString();
	return EXIT_SUCCESS;
}

int room2() {
	
	currentRoom = 2;
	
	printf("You go NORTH through yon corridor. You arrive at parapets.\nYe see a ROPE. Obvious exits are SOUTH.\n");
	enterString();
	return EXIT_SUCCESS;
}

int room3() {
	
	currentRoom = 3;
	
	printf("You head south to an embankment. Or maybe a chasm. You can\'t\ndecide which. Anyway, ye spies a TRINKET. Obvious exits are NORTH.\n");
	enterString();
	return EXIT_SUCCESS;
}

int room4() {
	
	currentRoom = 4;
	
	printf("Ye arrive at Dennis. He wears a sporty frock coat and a long\njimberjam. He paces about nervously. Obvious exits are NOT DENNIS.\n");
	enterString();
	return EXIT_SUCCESS;
}

int gettingFlask() {
	printf("Ye cannot get the FLASK. It is firmly bolted to a wall which is bolted\nto the rest of the dungeon which is probably bolted to a castle.\nNever you mind.\n");
	gotFlask++;
	enterString();
	return EXIT_SUCCESS;
}

int gettingScroll() {
	printf("Ye takes the SCROLL and reads of it. It doth say:\n\nBEWARE, READER OF YE SCROLL, DANGERS AWAIT TO THE -\n\nThe SCROLL disappears in thy hands with ye olde ZAP!\n");
	gotScroll = 1;
	score += 2;
	enterString();
	return EXIT_SUCCESS;
}

int gettingDagger() {
	printf("Yeah, okay.\n");
	score += 25;
	// You are supposed to get this over and over.
	enterString();
	return EXIT_SUCCESS;
}

int alreadyGotScroll() {
	printf("Ye doth suffer from memory loss. YE SCROLL is no more. Honestly.\n");
	enterString();
	return EXIT_SUCCESS;
}

int gettingTrinket() {
	printf("Ye getsts yon TRINKET and discover it to be a bauble.\nYou rejoice at your good fortune. You shove the TRINKET in your pouchel.\nIt kinda hurts.\n");
	gotTrinket = 1;
	enterString();
	return EXIT_SUCCESS;
}

int alreadyGotTrinket() {
	printf("Sigh. The trinket is in thou pouchel. Recallest thou?\n");
	enterString();
	return EXIT_SUCCESS;
}

int givingDennisNot() {
	printf("Thou don'tst have a trinket to give. Go back to your tiny life.\n");
	enterString();
	return EXIT_SUCCESS;
}

int lookFlask() {
	printf("Looks like you could quaff some serious mead out of that thing.\n");
	enterString();
	return EXIT_SUCCESS;
}

int lookScroll() {
	printf("Parchment, definitely parchment. I\'d recognize it anywhere.\n");
	enterString();
	return EXIT_SUCCESS;
}

int lookRope() {
	printf("It looks okay. You\'ve seen better.\n");
	enterString();
	return EXIT_SUCCESS;
}

int lookParapets() {
	printf("Well, they\'re parapets. This much we know for sure.\n");
	enterString();
	return EXIT_SUCCESS;
}

int lookTrinketFar() {
	printf("Quit looking! Just get it already.\n");
	enterString();
	return EXIT_SUCCESS;
}

int lookTrinketClose() {
	printf("Just a bulge in thou pouchel at thist point.\n");
	enterString();
	return EXIT_SUCCESS;
}

int lookDennis() {
	printf("That jimberjam really makes the outfit.\n");
	enterString();
	return EXIT_SUCCESS;
}

int talkDennis() {
	printf("You engage Dennis in lesiurely discussion. Ye learns that his\njimberham was purchased on sale at a discount market and that he\nenjoys pacing about nervously.\nYou become bored and begin thinking about parapets.\n");
	enterString();
	return EXIT_SUCCESS;
}

int getNone() {
	printf("Thou cannotst get that. Quit making stuffeth up!\n");
	enterString();
	return EXIT_SUCCESS;
}

int lookNone() {
	printf("It looketh pretty awesome.\n");
	enterString();
	return EXIT_SUCCESS;
}

int goNone() {
	printf("Thou cannotst go there. Who do you think thou art? A magistrate?!\n");
	enterString();
	return EXIT_SUCCESS;
}

int talkNone () {
	printf("Who is <NAME>? Your new boyfriend?\nSomebody from work you don't want me to meeteth?\n");
	enterString();
	return EXIT_SUCCESS;
}

int giveNone () {
	printf("Thou don'tst have a <ITEM> to give.\nGo back to your tiny life.\n");
	enterString();
	return EXIT_SUCCESS;
}

int smellNone () {
	printf("You smell a Wumpus.\n");
	enterString();
	return EXIT_SUCCESS;
}

int danceNone () {
	printf("Thou shaketh it a little, and it feeleth all right.\n");
	enterString();
	return EXIT_SUCCESS;
}

int endingDeath() {
	score -= 100;
	printf("That wasn\'t very smart.\nYour score was: %d", score);
	playAgain();
	return EXIT_SUCCESS;
}

int endingFlask() {
	score -= 1000;
	printf("Okay, okay. You unbolt yon FLASK and hold it aloft. A great\nshaking begins. The dungeon ceiling collapses down on you, crushing you in twain.\nApparently, this was a load-bearing FLASK.\nYour score was: %d", score);
	playAgain();
	return EXIT_SUCCESS;
}

int endingRope() {
	printf("\n\nThat wasn\'t very smart.\nYour score was: %d", score);
	playAgain();
	return EXIT_SUCCESS;
}

int endingWin() {
	printf("A novel idea! You givst the TRINKET to Dennis and he happily\nagrees to tell you what parapets are. With this new\nknowledge, ye escapes from yon dungeon in order to search for new dungeons and\nto remain...\n\n");
	printf("THY DUNGEONMAN!!\nYou hath won! Congraturation!\n");
	printf("Your score was: %d", score);
	playAgain();
	return EXIT_SUCCESS;
}

int playAgain(){
	printf("\n\nPlay again? [Y/N] ");
	char exitChar = 0;
	scanf("%c", &exitChar);
	if (exitChar == 'y' || exitChar == 'Y'){
		restartGame();
	}
	else if (exitChar == 'n' || exitChar == 'N'){
		return EXIT_SUCCESS;
	}
	else {
		playAgain();
	}
	return EXIT_SUCCESS;
}

int restartGame(){
	gotFlask = 0;
	gotScroll = 0;
	gotTrinket = 0;
	currentRoom = 0;
	score = 0;
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	main();
	return EXIT_SUCCESS;
}