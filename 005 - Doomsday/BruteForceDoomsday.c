// Thomas Moffet, thomasmoffet, z5061905
// F09C, Joeseph Harris
// 11/03/2015
// This was an attempt to make the Doomsday program in the most
// impractical way possible.

#include <stdio.h>
#include <stdlib.h>

#define SUNDAY 0
#define MONDAY 1
#define TUESDAY 2
#define WEDNESDAY 3
#define THURSDAY 4
#define FRIDAY 5
#define SATURDAY 6

#define START_DAY 1
#define START_MONTH 1
#define START_YEAR 1582
#define START_WEEKDAY FRIDAY

#define TRUE 1
#define FALSE 0

int calculationStage (int, int, int, int, int, int, int, int, int, int);
int leapYearChecker (int, int);

int main(int argc, char *argv[]) {
	
	int inputDay;
	int inputMonth;
	int inputYear;
	
	// I don't know why, but the compiler wants me to give inputWeekday
	// a value.
	
	int inputWeekday = 0;
	
	int purposeVar = 0;
	
	printf("What day do you want to find out? ");
	scanf("%d", &inputDay);
	printf("How about the month? ");
	scanf("%d", &inputMonth);
	printf("And the year? ");
	scanf("%d", &inputYear);
	
	inputWeekday = calculationStage (inputDay, inputMonth, inputYear, inputWeekday, purposeVar, START_DAY, START_MONTH, START_YEAR, START_WEEKDAY, FALSE);
	
	if (inputWeekday == SUNDAY) {
		printf("That day is a Sunday.\n");
	}
	if (inputWeekday == MONDAY) {
		printf("That day is a Monday.\n");
	}
	if (inputWeekday == TUESDAY) {
		printf("That day is a Tuesday.\n");
	}
	if (inputWeekday == WEDNESDAY) {
		printf("That day is a Wednesday.\n");
	}
	if (inputWeekday == THURSDAY) {
		printf("That day is a Thursday.\n");
	}
	if (inputWeekday == FRIDAY) {
		printf("That day is a Friday.\n");
	}
	if (inputWeekday == SATURDAY) {
		printf("That day is a Saturday.\n");
	}
	
	return EXIT_SUCCESS;
}

// I need to figure out how to get it so that I don't have to return
// every single iteration of the calulationStage function.

int calculationStage (int inputDay, int inputMonth, int inputYear, int inputWeekday, int purposeVar, int currentDay, int currentMonth, int currentYear, int currentWeekday, int isItLeapYear) {
	
	if (purposeVar == 0) {
		
		while (currentDay != inputDay || currentMonth != inputMonth || currentYear != inputYear) {
			
			// If it's the 32nd of a month, reset the day.
			
			if (currentDay == 32 && currentMonth < 12) {
				currentDay = 1;
				currentMonth++;
			}
			
			// If it's the 29th of February, and it's not a leap year,
			// reset the day.
			
			if (currentDay == 29 && currentMonth == 2 && isItLeapYear == FALSE) {
				currentDay = 1;
				currentMonth++;
			}
			
			// If it's the 30th of February, reset the day.
			
			if (currentDay == 30 && currentMonth == 2) {
				currentDay = 1;
				currentMonth++;
			}
			
			// If it's the 31st of April, June, September, or November,
			// reset the day.
			
			if (currentDay == 31 && (currentMonth == 4 || currentMonth == 6 || currentMonth == 9 || currentMonth == 11)) {
				currentDay = 1;
				currentMonth++;
			}
			
			// If it's the 32nd of December, reset the day and month.
			
			if (currentDay == 32 && currentMonth == 12) {
				currentDay = 1;
				currentMonth = 1;
				currentYear++;
			}
			
			// If it's the first day of the year, check if it's leap.
			
			if (currentDay == 1 && currentMonth == 1) {
				isItLeapYear = leapYearChecker (currentYear, isItLeapYear);
			}
			
			// If you want to see what day the program has reached.
			// printf("%d/%d/%d is %d\n", currentDay, currentMonth, currentYear, currentWeekday);
			
			currentDay++;
			currentWeekday++;

			// If the weekday has passed over, reset it.
			
			if (currentWeekday == 7) {
				currentWeekday = 0;
			}
			
		}
		
		purposeVar = 1;
		return currentWeekday;
	}
	
	return 0;
}

int leapYearChecker (int currentYear, int isItLeapYear) {
	if ((currentYear % 4) == 0) {
		if ((currentYear % 100) == 0) {
			if ((currentYear % 400) == 0) {
				return TRUE;
			}
			else {
				return FALSE;
			}	
		}
		else {
			return TRUE;
		}	
	}
	else {
		return FALSE;
	}
	return 0;
}