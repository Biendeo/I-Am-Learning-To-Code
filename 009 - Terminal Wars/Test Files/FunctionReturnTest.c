#include <stdio.h>
#include <stdlib.h>

int numberRumber (int numberman);

int main(int argc, char *argv[]) {
	int numberman = atoi(argv[1]);
	printf("numberman = %d\n", numberman);
	printf("numberman becomes %d", numberman * numberRumber(numberman));
	return EXIT_SUCCESS;
}

int numberRumber (int numberman) {
	int returnNum = numberman + 5;
	return returnNum;
}