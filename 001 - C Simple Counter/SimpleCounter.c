// Here I'm including the standard stdio.h header. I need to learn what exactly the different headers are for, but hey, it works for now.
#include <stdio.h>
// stdio.h is a header library that lets you perform input / output operations.

// Here I'm defining the two variables that will be used in all the functions, all as integers.
int numberIncrement = 0;
int numberGoal = 0;

// I'm also defining the yes/no variable we'll be using later as a character.
char characterGet = "0";
 
// Now we're starting the main function.
int main() {

    // Define your variables here. Here is a good read:
    // http://c2.com/cgi/wiki?GlobalVariablesAreBad
    
    // Also, stay away from using go to. Don't start forming bad habits already.
    // http://stackoverflow.com/questions/18035011/how-to-avoid-goto-in-c
    
	// Firstly, I'm asking what number they're reaching to, and storing that as integer numberGoal.
	printf("\nOkay, what number do you want to reach? ");
	scanf("%d", &numberGoal);
	
	// Then I'm checking to see if it actually is an integer.
	while (numberGoal < 1){
		printf("I can't add letters! Type a number this time! ");
		scanf("%d", &numberGoal);

	// Then, I'm asking how much they want to go up by, and storing that in y.
	printf("What increment do you want to add by to get there? ");
	scanf("%d", &numberIncrement);

	// Then I'm giving them a chance to re-read this, and see if anything they'd like to correct.
	printf("So you want to go up by %d to hit %d? (Y/N) ", numberIncrement, numberGoal);
	// Here, there's a label, and characterGet is reset. This is because the other conditions later link back to here.
	question: 
	// This gets the letter that they type, and then it's passed through some logic.
	scanf("%c", &characterGet);

	// If it's a yes, then this happens, and it executes the counting part down below.
	if (characterGet == 'y' || characterGet == 'Y')
	{
		printf("Okay. Let's do this.\n");
		calcOperation(numberIncrement, numberGoal);
		repeat();
	}
	// If it's a no, then the earlier questions are asked again (with different text), and it loops.
	else if (characterGet == 'n' || characterGet == 'N')
	{
		printf("In that case, what number did you want to count to? ");
		scanf("%d", &numberGoal);
		printf("And what increment do you want to add by to get there? ");
		scanf("%d", &numberIncrement);
		printf("So you want to go up by %d to hit %d? (Y/N) ", numberIncrement, numberGoal);
		characterGet = "0";
		goto question;
	}
}

int calcOperation (int numberIncrement, int numberGoal){
	
	// I'm defining three integers that will be used during the calculation stage.
    int numberShort = 0;
    int numberOperation = 0;
    int numberCurrent = 0;
	
	// Now we're up to the counting part.
	counting:
	
	// So numberCurrent is the current number we're up to. While it's less than numberGoal, we do the operation.
	while (numberCurrent <= numberGoal)
	{
		// So we add our increment.
		numberCurrent = numberCurrent + numberIncrement;
		// We also add one to the number of operations we've done.
		numberOperation++;
		// And print this to the user.
		printf("\nI've added %d times, and now I'm up to %d.", numberOperation, numberCurrent);
	}

	// Now we've overshot it, so we just back up a step.
	numberCurrent = numberCurrent - numberIncrement;
	numberOperation--;
	
	// And we tell the person of our results.
	numberShort = numberGoal - numberCurrent;
	printf("\nOkay, I added %d %d times, and got up to %d. That's %d short of %d.\n", numberIncrement, numberOperation, numberCurrent, numberShort, numberGoal);
}
	
int repeat (){
	
	// We finally end with a similar yes/no to what we had before, only now they do different stuff.
	printf("\nWant to do another one? (Y/N) ");
	characterGet = 0;
	scanf("%c", &characterGet);

	if (characterGet == 'y' || characterGet == 'Y')
	{
		main();
	}

	else if (characterGet == 'n' || characterGet == 'N')
	{
		printf("\nThanks for using this. See ya!\n");
	}

	else
	{
		characterGet = 0;
		
		// This currently ends the function. I need it to loop.
		
	}
}
	
// TO DO: replace the goto labels, figure out how to get negative numbers to work (probably do a division and a negative check), fix the getchar stuff.