// The header that does IO. I need to check up what this does as well as cin and cout.
#include <iostream>

// I've got a function to do the counting.
unsigned int countingStage(unsigned int numGoal, unsigned int numStep);

// Firstly, we start with the main.
int main(int argc, char *argv[]) {
	// We're going to be dealing with positive integers, so unsigned is the way to go.
	unsigned int numGoal = 0;
	unsigned int numStep = 0;

	// We ask the user for input, and then we use cin to do that. The arrows are important in direction here.
	std::cout << "Please enter what number you would like to count to. ";
	std::cin >> numGoal;

	// I'm always cautious about this, so I flush the input.
	fflush(stdin);

	// Repeat for this step.
	std::cout << "Now what number would you like to step to get there? ";
	std::cin >> numStep;

	fflush(stdin);

	// Then, we run the function, passing the inputs into it.
	countingStage(numGoal, numStep);

	return 0;
}

unsigned int countingStage(unsigned int numGoal, unsigned int numStep) {
	// We count the number of iterations, and what progress we're up to.
	unsigned int iterations = 0;
	unsigned int currentProgress = 0;

	// While we haven't hit the goal, increment by the step, and count the number of iterations.
	// This will end when it exceeds or equals it.
	while (currentProgress < numGoal) {
		currentProgress += numStep;
		iterations++;
	}

	// We need two cases for what to display.
	if (currentProgress == numGoal) {
		// If it landed perfectly, then everything is pretty simple.
		std::cout << numGoal << " is " << iterations << " times " << numStep << " with no remainder." << std::endl;
	} else if (currentProgress > numGoal) {
		// Otherwise, we overshot it by one, and we need to list the remainder.
		std::cout << numGoal << " is " << iterations - 1 << " times " << numStep << " with " << numGoal + numStep - currentProgress << " remainder." << std::endl;
	}

	// Then we return to the main function and end the program. Nothing uses this return specifically, but it's always nice to return something relevant.
	return iterations;
}