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
        null,
        number,
        operatortype,
        constant,
        variable
    };

    // This defines a constant as a usable name in the program, and a value
    // associated with it. It has a boolean to determine whether it is a
    // constant or not, which allows it to be modified.
    class variable {
        bool isConstant;

        public:
        char *name;
        double value;
    };

    class memory {

    };

    class history {

    };

    class equation {

    };

    // This defines a mathematical object as a type and a value of some kind.
    // type == number,       value == double
    // type == operatortype, value == operatorType
    // type == constant,     value == variable
    // type == variable,     value == variable
    class object {
        objectType type;
        void *value;          // This void * means that it's not type dependent.
    };
};

int main(int argc, char *argv[]) {

    return EXIT_SUCCESS;
}