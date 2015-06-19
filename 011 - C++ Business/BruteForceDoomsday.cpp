#include <iostream>

// I'm going to start using const int instead of #define purely because they're type specific, and I can control their scope.
const int SUNDAY = 0;
const int MONDAY = 1;
const int TUESDAY = 2;
const int WEDNESDAY = 3;
const int THURSDAY = 4;
const int FRIDAY = 5;
const int SATURDAY = 6;

const int START_DAY = 1;
const int START_MONTH = 1;
const int START_YEAR = 1582;
const int START_WEEKDAY = FRIDAY;

int calculationStage(int inputDay, int inputMonth, int inputYear);
bool leapYearChecker(int year);

int main(int argc, char *argv[]) {

	int inputDay = 0;
	int inputMonth = 0;
	int inputYear = 0;

	std::cout << "What day do you want to find out? " << std::endl;
	std::cin >> inputDay;
	std::cout << "How about the month? " << std::endl;
	std::cin >> inputMonth;
	std::cout << "And the year? " << std::endl;
	std::cin >> inputYear;

	int returnWeekday = calculationStage(inputDay, inputMonth, inputYear);

	// This basically checks what is returnWeekday with the cases. It's in C, but this is my first time using them.
	switch (returnWeekday) {
		case SUNDAY:
			std::cout << "That day is a Sunday." << std::endl;
			break;
		case MONDAY:
			std::cout << "That day is a Monday." << std::endl;
			break;
		case TUESDAY:
			std::cout << "That day is a Tuesday." << std::endl;
			break;
		case WEDNESDAY:
			std::cout << "That day is a Wednesday." << std::endl;
			break;
		case THURSDAY:
			std::cout << "That day is a Thursday." << std::endl;
			break;
		case FRIDAY:
			std::cout << "That day is a Friday." << std::endl;
			break;
		case SATURDAY:
			std::cout << "That day is a Saturday." << std::endl;
			break;
	}

	return 0;
}

int calculationStage(int inputDay, int inputMonth, int inputYear) {

	int currentWeekday = START_WEEKDAY;
	int currentDay = START_DAY;
	int currentMonth = START_MONTH;
	int currentYear = START_YEAR;
	bool bIsLeapYear = false;

	while (currentDay != inputDay || currentMonth != inputMonth || currentYear != inputYear) {

			// If it's the 32nd of a month, reset the day.
			if (currentDay == 32 && currentMonth < 12) {
				currentDay = 1;
				currentMonth++;
			}

			// If it's the 29th of February, and it's not a leap year, reset the day.
			if (currentDay == 29 && currentMonth == 2 && bIsLeapYear == false) {
				currentDay = 1;
				currentMonth++;
			}

			// If it's the 30th of February, reset the day.
			if (currentDay == 30 && currentMonth == 2) {
				currentDay = 1;
				currentMonth++;
			}

			// If it's the 31st of April, June, September, or November, reset the day.
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
				bIsLeapYear = leapYearChecker(currentYear);
			}

			// If you want to see what day the program has reached.
			// std::cout << currentDay << "/" << currentMonth << "/" << currentYear << " is a " << currentWeekday << " day.\n";

			currentDay++;
			currentWeekday++;

			// If the weekday has passed over, reset it.
			if (currentWeekday == 7) {
				currentWeekday = 0;
			}
		}

	return currentWeekday;
}

bool leapYearChecker(int year) {

	// I've seen people call their bools starting with a b, so I'll do that here.
	bool bIsLeapYear = false;

	if      ((year % 400) == 0) bIsLeapYear = true;
	else if ((year % 100) == 0) bIsLeapYear = false;
	else if ((year % 4) == 0)   bIsLeapYear = true;
	else                        bIsLeapYear = false;

	return bIsLeapYear;
}