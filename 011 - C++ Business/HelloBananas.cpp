// This lets you use std::cout and std::cin, which are the C++ equivalents of printf and scanf.
#include <iostream>

// Main function as always.
int main(int argc, char *argv[]) {

	// This is cout, or "character output". It uses a fancy operator, and then takes a string.
	// I think the std is a class (correct me on this), and it calls the cout function from that class.
	// You can also use "endl" extra at the end of a line, which is basically '\n' but also does fflush.
	std::cout << "Hello bananas!\n";

	// I dunno if I can use stdlib.h's EXIT_SUCCESS (probably, but I'll just leave it like this for now).
	return 0;
}