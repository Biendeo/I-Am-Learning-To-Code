/*
 * A C++ calculator by Thomas Moffet
 * Started on 23/07/2015
 * 
 * The goal of this is to:
 * 1. Make a working calculator that computes several basic functions.
 * 2. Experiment using C++ classes in a proper context.
 * 3. Look good for uni points. :)
 * 
 * There is more info in the Plan.txt file provided.
 *
 * You can freely use this for whatever you want. :)
 *
 */

#include <iostream>
#include <cstdlib>
#include <cmath>

// This is the main calculator class. You only need to pass a pointer of this
// around to the different functions. It possesses all the memory for the
// program, and all the various classes used in its operation.
class calc {

    // This defines the types of operators that the program can use. They are
    // all case checked for what they all do.
    enum operatorType {
        null,
        add,
        subtract,
        multiply,
        divide,
        exponent,
        modulus
    };

    // This defines the types of objects that are stored. These are the
    // different categories of mathematical terms that can be used in the
    // program.
    enum objectType {
        typeNull,
        typeNumber,
        typeOperator,
        typeConstant,
        typeVariable,
        typeEnd
    };



    // This defines the section that stores variables and the history.
    class memory {

        // This defines a constant as a usable name in the program, and a value
        // associated with it. It has a boolean to determine whether it is a
        // constant or not, which allows it to be modified.
        class variable {
            bool isConstant;
            char *name;
            double value;

            public:
            // This is the default constructor. It doesn't have any particular
            // properties to use. Since all the variables are created at launch,
            // there is no constructor explicitly for giving properties.
            variable() {
                isConstant = true;
                name = "null";
                value = 0;
            };

            // The properties are determined after the variable is created, so
            // this function allows the program to set those.
            int setVariable(char *givenName, double givenValue, bool givenConstant) {
                isConstant = givenConstant;
                name = givenName;
                value = givenValue;
            };

            // This function returns whether the variable is a constant;
            bool getIsConstant() {
                return isConstant;
            };

            // This function returns the variable's name.
            char *getName() {
                return name;
            };

            // This function returns the variable's value.
            double getValue() {
                return value;
            }
        };

        // TODO: Should this be inside the memory class, or should it be outside the whole thing?
        class history {

        };


        // This is the maximum number of variables that the program can store.
        // This includes constants, so be sure to increase/decrease this
        // number accordingly. You don't want too many constants to fill up.
        static const unsigned int MAX_VARIABLES = 250;

        variable variables[MAX_VARIABLES];
        int totalVariables;

        // This function is where constants can be added to the program.
        void intialiseConstants() {
            addVar("e", 2.71, true);
            addVar("pi", 3.14, true);
        };

        // This function returns the name of a stored variable given the ID. It
        // returns "null" if there's one not stored there.
        char *getVarNameFromIndex(unsigned int index) {
            if (index >= MAX_VARIABLES) {
                return "null";
            } else {
                return variables[index].getName();
            }
        };

        // This function gets the index of a variable from its name.
        int getVarIndex(char *name) {
            int i = 0;
            while ((i < MAX_VARIABLES) && (getVarNameFromIndex(i) != name)) {
                i++;
            }

            if (i == MAX_VARIABLES) {
                return -1; // TODO: Enum this error code.
            } else {
                return i;
            }
        }

        // This function gets the value of a variable from its index.
        double getVarValueFromIndex(unsigned int index) {
            if (index >= MAX_VARIABLES) {
                return 0; // Hopefully this never occurs.
            } else {
                return variables[index].getValue();
            }
        }

        public:
        memory() {
            totalVariables = 0;
            intialiseConstants();
        };

        // This function adds a variable to the stored array. It returns an
        // error if it's full, or if there's another variable by that name.
        int addVar(char *name, double value, bool isConstant) {
            // TODO: Replace this with a switch/case for the name.
            if (name == "null") {
                return -3; // TODO: Enum this error code.
            } else if (name == "var") {
                return -2; // TODO: Enum this error code.
            } else if (totalVariables == MAX_VARIABLES) {
                return -1; // TODO: Enum this error code.
            } else {
                int i = 0;
                // I feel as if something can go wrong here. If i reaches
                // MAX_VARIABLES, then there's no fall protection. However, I
                // feel as if the previous else if solves that. It seems odd.
                while ((i < MAX_VARIABLES) && (getVarNameFromIndex(i) == "null")) {
                    i++;
                }

                variables[i].setVariable(name, value, isConstant);
                totalVariables++;
                return 0; // TODO: Enum this error code.
            }
        };

        // This function gets the value of a stored variable based on its name.
        double getVarValue(char *name) {
            int i = getVarIndex(name);
            
            if (i < 0) {
                return -1; // TODO: Enum this error.
            } else {
                return getVarValueFromIndex(i);
            }
        };

        // This function gets the total number of variables that are stored.
        // This includes constants.
        int getTotalVariables() {
            return totalVariables;
        }
    };

    // TODO: The equation class.
    class equation {
        char *originalEquation;

    };

    // This defines a mathematical object as a type and a value of some kind.
    // type == typeNumber,   value == double
    // type == typeOperator, value == operatorType
    // type == typeConstant, value == variable
    // type == typeVariable, value == variable
    // type == typeEnd,      value == NULL
    class object {
        objectType type;
        void *value;          // This void * means that it's not type dependent.
        object *next;

        public:
        // TODO: Create a constructor. It'll probably input the properties. The
        // string will be handled externally. Next will need to be a null
        // pointer temporarily, as there will not be a value for it right away.
        object(objectType givenType) {

        };

        // This function returns the type of this object. It should be called to
        // check which of the next functions to call.
        objectType getType() {
            return type;
        };

        double getDoubleValue() {
            // This causes an error because *value is technically void.
            // TODO: Figure out how to do this.
            double x = *value;

            if (type == typeNumber) {
                return x;
            } else {
                return 0; // TODO: Error?
            }
        }
    };

    public:
    calc() {
        memory mem;
    };
};

int main(int argc, char *argv[]) {

    calc *calculator = new calc;

    // TODO: The program should run some tests before it can be used.
    // TODO: Also make a program.

    delete calculator;

    return EXIT_SUCCESS;
}