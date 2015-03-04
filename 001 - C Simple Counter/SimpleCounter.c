// Here I'm including the standard stdio.h header. I need to learn what exactly the different headers are for, but hey, it works for now.
#include <stdio.h>
// stdio.h is a header library that lets you perform input / output ooperations.

// Now we're starting the main function.
int main() {
    // Here I'm defining the five variables, all as integers.
    int v = 0;
    int w = 0;
    int x = 0;
    int y = 0;
    int z = 0;
    
    // I'm also defining the yes/no variable we'll be using later as a character.
    char q;

    // Define your variables here. Here is a good read:
    // http://c2.com/cgi/wiki?GlobalVariablesAreBad
    
    // Also, stay away from using go to. Don't start forming bad habits already.
    // http://stackoverflow.com/questions/18035011/how-to-avoid-goto-in-c
    
    
    
	// This is here just to restart the application when asked to at the end.
	beginning:
	// Firstly, I'm asking what number they're reaching to, and storing that as integer z.
	printf("\nOkay, what number do you want to reach? ");
	scanf("%d", &z);

	// Then, I'm asking how much they want to go up by, and storing that in y.
	printf("\nWhat increment do you want to add by to get there? ");
	scanf("%d", &y);

	// Then I'm giving them a chance to re-read this, and see if anything they'd like to correct.
	printf("\nSo you want to go up by %d to hit %d? (Y/N) ", y, z);
	// Here, there's a label, and q is reset. This is because the other conditions later link back to here.
	question: 
	// This gets the letter that they type, and then it's passed through some logic.
	scanf("%c", &q);

	// If it's a yes, then this happens, and it executes the counting part down below.
	if (q == 'y' || q == 'Y')
	{
		printf("Okay. Let's do this. (Hit Enter)");
		getchar();
		goto counting;
	}
	// If it's a no, then the earlier questions are asked again (with different text), and it loops.
	else if (q == 'n' || q == 'N')
	{
		printf("\nIn that case, what number did you want to count to? ");
		scanf("%d", &z);
		printf("\nAnd what increment do you want to add by to get there? ");
		scanf("%d", &y);
		printf("\nSo you want to go up by %d to hit %d? (Y/N) ", y, z);
		q = "0";
		goto question;
	}
	// If the question hasn't been answered, don't say a different answer has popped up.
	else if (q = "0")
	{	
	goto question;
	}

	// If it's neither, the question is asked again.
	else
	{
		q = "0";
		printf("\nThat wasn't what I was expecting, please type a Y or an N. ");
		goto question;
	}

	// Now we're up to the counting part.
	counting:
	// I'm going to reset the numbers in case you're doing a second operation.
	x = 0;
	w = 0;
	
	// So x is the current number we're up to. While it's less than z, we do the operation.
	while (x < z)
	{
		// So we add our increment.
		x = x + y;
		// We also add one to the number of operations we've done.
		w++;
		// And print this to the user.
		printf("\nI've added %d times, and now I'm up to %d.", w, x);
	}

	// Now we've overshot it, so we just back up a step.
	x = x - y;
	w--;
	// And we tell the person of our results.
	v = z - x;
	printf("\nOkay, I added %d %d times, and got up to %d. That's %d short of %d.", y, w, x, v, z);

	// We finally end with a similar yes/no to what we had before, only now they do different stuff.
	printf("\nWant to do another one? (Y/N) ");

	ending:
	q = 0;
	scanf("%c", &q);

	if (q == 'y' || q == 'Y')
	{
		goto beginning;
	}

	else if (q == 'n' || q == 'N')
	{
		printf("\nThanks for using this. See ya!\n");
	}

	else
	{
		printf("\nI don't know what you meant by that. Type Y or N please. ");
		q = 0;
		goto ending;
	}
}