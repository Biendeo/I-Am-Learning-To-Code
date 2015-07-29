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
#include <string>
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
        modulus,
        leftBracket,
        rightBracket
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
                return EXIT_SUCCESS;
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

    // This holds the data for what a math object will track. Depending on its
    // type, it'll hold one of these.
    union valueOnion {
        double number;
        operatorType opType;
        unsigned int var;
    };

    // This defines a mathematical object as a type and a value of some kind.
    // type == typeNumber,   value == double
    // type == typeOperator, value == operatorType
    // type == typeConstant, value == variable
    // type == typeVariable, value == variable
    // type == typeEnd,      value == NULL
    class object {
        objectType type;
        valueOnion value;

        public:

        // This is the default
        object() {
            setType(typeNull);
            setDoubleValue(0);
        }

        int setType(objectType givenType) {
            type = givenType;
            return EXIT_SUCCESS;
        };

        int setDoubleValue(double givenValue) {
            value.number = givenValue;
            return EXIT_SUCCESS;
        };

        int setOperatorTypeValue(operatorType givenOpType) {
            value.opType = givenOpType;
            return EXIT_SUCCESS;
        };

        int setVariableIndex(unsigned int givenVar) {
            value.var = givenVar;
            return EXIT_SUCCESS;
        }

        // This function returns the  type of this object. It should be called to
        // check which of the next functions to call.
        objectType getType() {
            return type;
        };

        // If getType() returns typeNumber, then call this to get the value.
        double getDoubleValue() {
            return value.number;
        };

        // If getType() returns typeOperator, then call this to get the value.
        operatorType getOperatorType() {
            return value.opType;
        };

        // If getType() returns typeConstant or typeVariable, then call this to
        // get the value.
        unsigned int getVariableIndex() {
            return value.var;
        };
    };

    public:
    calc() {
        memory mem;
    };

    // TODO: The equation class.
    class equation {
        // This is the maximum number of objects that can be in an equation
        // if needed change this value.
        static const unsigned int MAX_OBJECTS = 250;

        // This is the maximum number of digits a number can occupy.
        static const unsigned int NUM_LENGTH = 30;

        std::string originalEquation;
        object objects[MAX_OBJECTS];
        double result;

        public:
        equation(std::string givenEquation) {
            originalEquation = givenEquation;
            result = 0;
        };

        // This function converts the string of the original equation into an
        // array of math objects. You only need to ever run this once per
        // equation.
        void convertEquation() {
            int currentObj = 0;
            for (int i = 0; originalEquation[i] != 'EOF'; i++) {
                // TODO: Add in decimal functionality. Check to see if the user
                // puts two decimals in a number as well.
                if (originalEquation[i] >= '0' && originalEquation[i] <= '9') {

                    int pos = 0;
                    // TODO: Test if this works properly.
                    std::string numberString = "";

                    while ((originalEquation[i] >= '0' && originalEquation[i] <= '9') && (pos < NUM_LENGTH)) {
                        numberString[pos] = originalEquation[i];
                        i++;
                    }

                    // This will overshoot the next character, so we move back
                    // one.
                    i--;


                    // TODO: Convert the string to a double.
                    double convertedNumber = atof(numberString.c_str());
                    objects[currentObj].setType(typeNumber);
                    objects[currentObj].setDoubleValue(convertedNumber);
                    currentObj++;
                } else if (originalEquation[i] >= 'a' && originalEquation[i] <= 'z') {
                    // TODO: Expect variables, but add exceptions for trig
                    // functions.
                } else {
                    // For this, we assume the type has to be an operator. If
                    // it isn't, the default type will pick it up
                    objects[currentObj].setType(typeOperator);
                    switch (originalEquation[i]) {
                        case '+':
                            objects[currentObj].setOperatorTypeValue(add);
                            break;
                        case '-':
                            objects[currentObj].setOperatorTypeValue(subtract);
                            break;
                        case '*':
                            objects[currentObj].setOperatorTypeValue(multiply);
                            break;
                        case '/':
                            objects[currentObj].setOperatorTypeValue(divide);
                            break;
                        case '%':
                            objects[currentObj].setOperatorTypeValue(modulus);
                            break;
                        case '^':
                            objects[currentObj].setOperatorTypeValue(exponent);
                            break;
                        case '(':
                            objects[currentObj].setOperatorTypeValue(leftBracket);
                            break;
                        case ')':
                            objects[currentObj].setOperatorTypeValue(rightBracket);
                            break;
                        default:
                            objects[currentObj].setType(typeNull);
                            currentObj--;
                            break;
                    }
                    currentObj++;
                }
            }

            objects[currentObj].setType(typeEnd);
        };

        double getResult() {
            return result;
        };

        unsigned int getTotalObjects() {
            unsigned int i = 0;
            while (i < MAX_OBJECTS) {
                switch (objects[i].getType()) {
                    case typeNumber:
                        i++;
                        break;
                    case typeOperator:
                        i++;
                        break;
                    case typeConstant:
                        i++;
                        break;
                    case typeVariable:
                        i++;
                        break;
                    default:
                        break;
                }
            }

            return i;
        };

        void deleteObject(unsigned int index) {
            while (index < MAX_OBJECTS - 1) {
                objects[index].setType(objects[index + 1].getType());
                switch (objects[index].getType()) {
                    case typeNumber:
                        objects[index].setDoubleValue(objects[index + 1].getDoubleValue());
                        break;
                    case typeOperator:
                        objects[index].setOperatorTypeValue(objects[index + 1].getOperatorType());
                        break;
                    case typeVariable:
                        objects[index].setVariableIndex(objects[index + 1].getVariableIndex());
                        break;;
                    default:
                        objects[index].setDoubleValue(0);
                        break;
                }
                index++;
            }
            objects[index].setType(typeNull);
            objects[index].setDoubleValue(0);
        }

        void evaluateEquation() {
            while (getTotalObjects() > 1) {
                bool operationPerformed = false;
                int highestBracketOrder = 0;
                int currentBracketOrder = 0;

                while (highestBracketOrder > 0) {
                    highestBracketOrder = 0;
                    currentBracketOrder = 0;

                    // Firstly, it scans the equation to find the most inner
                    // bracket to evaluate.
                    for (int i = 0; objects[i].getType() != typeEnd; i++) {
                        if (objects[i].getType() == typeOperator) {
                            if (objects[i].getOperatorType() == leftBracket) {
                                currentBracketOrder++;
                            } else if (objects[i].getOperatorType() == rightBracket) {
                                currentBracketOrder--;
                            }
                        }

                        if (currentBracketOrder > highestBracketOrder) {
                            highestBracketOrder = currentBracketOrder;
                        }
                    }

                    if (currentBracketOrder != 0) {
                        // TODO: Do an error here.
                        currentBracketOrder = 0;
                    }

                    // Now we stop when we reach a highest bracket.
                    int pos = 0;
                    while (currentBracketOrder != highestBracketOrder) {
                        if (objects[pos].getType() == typeOperator) {
                            if (objects[pos].getOperatorType() == leftBracket) {
                                currentBracketOrder++;
                            } else if (objects[pos].getOperatorType() == rightBracket) {
                                currentBracketOrder--;
                            }
                        }
                        pos++;
                    }

                    // We've overshot it, so we back up one.
                    pos--;

                    // If we're sitting on a left bracket, we check to see if
                    // there's a right bracket either right after, or the one
                    // after that.
                    if (operationPerformed == false) {
                        if (objects[pos].getType() == typeOperator) {
                            if (objects[pos].getOperatorType() == leftBracket) {
                                if (objects[pos + 1].getType() == typeOperator) {
                                    if (objects[pos + 2].getOperatorType() == rightBracket) {
                                        deleteObject(pos);
                                        deleteObject(pos);
                                        operationPerformed = true;
                                    }
                                } else if (objects[pos + 2].getType() == typeOperator) {
                                    if (objects[pos + 2].getOperatorType() == rightBracket) {
                                        deleteObject(pos);
                                        deleteObject(pos + 1);
                                        operationPerformed = true;
                                    }
                                }
                            }
                        }
                    }

                    // Next, we try to get rid of unary - symbols by merging
                    // them with any doubles.

                    currentBracketOrder = 0;

                    // TODO: Make this part a function, I call it a lot.
                    pos = 0;
                    while (currentBracketOrder != highestBracketOrder) {
                        if (objects[pos].getType() == typeOperator) {
                            if (objects[pos].getOperatorType() == leftBracket) {
                                currentBracketOrder++;
                            } else if (objects[pos].getOperatorType() == rightBracket) {
                                currentBracketOrder--;
                            }
                        }
                        pos++;
                    }

                    if (operationPerformed == false) {
                        while ((pos < MAX_OBJECTS) && (objects[pos].getType() != rightBracket)) {
                            if (objects[pos].getType() == typeOperator) {
                                if (objects[pos].getOperatorType() == subtract) {
                                    if (objects[pos + 1].getType() == typeNumber) {
                                        if (pos == 0) {
                                            deleteObject(pos);
                                            objects[pos].setDoubleValue(evaluateMultiplication(objects[pos].getDoubleValue(), -1));
                                            operationPerformed = true;
                                        } else if (objects[pos - 1].getType() == typeOperator) {
                                            deleteObject(pos);
                                            objects[pos].setDoubleValue(evaluateMultiplication(objects[pos].getDoubleValue(), -1));
                                            operationPerformed = true;
                                        }
                                    }
                                }
                            }
                            pos++;
                        }
                    }

                    // Finally, we do operations based on two numbers and an
                    // operator.

                    currentBracketOrder = 0;

                    // TODO: Make this part a function, I call it a lot.
                    pos = 0;
                    while (currentBracketOrder != highestBracketOrder) {
                        if (objects[pos].getType() == typeOperator) {
                            if (objects[pos].getOperatorType() == leftBracket) {
                                currentBracketOrder++;
                            } else if (objects[pos].getOperatorType() == rightBracket) {
                                currentBracketOrder--;
                            }
                        }
                        pos++;
                    }

                    if (operationPerformed == false) {
                        while ((pos < MAX_OBJECTS) && (objects[pos].getType() != rightBracket)) {
                            if (objects[pos].getType() == typeOperator) {
                                if (objects[pos - 1].getType() == typeNumber && objects[pos + 1].getType() == typeNumber) {
                                    objects[pos - 1].setDoubleValue(evaluateExpression(objects[pos - 1].getDoubleValue(), objects[pos + 1].getDoubleValue(), objects[pos].getOperatorType()));
                                    deleteObject(pos);
                                    deleteObject(pos);
                                    operationPerformed = true;
                                }
                            }
                            pos++;
                        }
                    }
                }
            }
        };

        double evaluateExpression(double a, double b, operatorType opType) {
            switch (opType) {
                case add:
                    return evaluateAddition(a, b);
                case subtract:
                    return evaluateSubtraction(a, b);
            }
        };

        double evaluateAddition(double a, double b) {
            return a + b;
        };

        double evaluateSubtraction(double a, double b) {
            return a - b;
        };

        double evaluateMultiplication(double a, double b) {
            return a * b;
        };

        double evaluateDivision(double a, double b) {
            if (b == 0) {
                return 0;
            } else {
                return a / b;
            }
        };

        double evaluateExponent(double a, double b) {
            return pow(a, b);
        };

        double evaluateModulus(double a, double b) {
            if (isItAnInteger(a) == true && isItAnInteger(b) == true) {
                return (int)a % (int)b;
            } else {
                return 0;
            }
        };

        bool isItAnInteger(double a) {

            // This variable is the degree of error that a double has.
            static const double epsilon = 0.00002;
            if (a > 0) {
                if ((a - epsilon < roundl(a)) && (a + epsilon > round(a))) {
                    return true;
                } else {
                    return false;
                }
            }
            return true;
        }
    };
};

void testProgram(calc *calculator, std::string testString);

int main(int argc, char *argv[]) {

    calc *calculator = new calc;

    // TODO: The program should run some tests before it can be used.
    // TODO: Also make a program.
    std::string testString = "";
    std::cout << "Type an equation!" << std::endl;
    std::cin >> testString;
    testProgram(calculator, testString);

    delete calculator;

    return EXIT_SUCCESS;
}

void testProgram(calc *calculator, std::string testString) {
    calc::equation testEquation(testString);
    testEquation.evaluateEquation();
    std::cout << testString << " = " << testEquation.getResult() << std::endl;
}