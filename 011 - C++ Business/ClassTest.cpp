#include <iostream>

// This class basically defines a rectange.
class Rectangle {
	// It has two private properties.
	// You could also use private: on these, but it's that by default.
	double width;
	double height;

	// These are accessible outside of the class itself.
	public:
	
	// This is a constructor. It basically lets you quickly assign the properties (it kind-of is a function).
	Rectangle(double inputWidth, double inputHeight) {
		width = inputWidth;
		height = inputHeight;
	}

	// These functions return the values stored in the object.
	double getWidth();
	double getHeight();

	// These calculate things and return that.
	double getArea();
	double getPerimeter();
};

int main(int argc, char *argv[]) {
	// This is how we initialise classes. I put a space after the name just to make it not look exactly like a function.
	Rectangle rectA (5, 7);
	Rectangle rectB (5.9, 4.3);

	// And this is how you do class functions.
	// Basically, it's the object's name, then the function. Since you can't access private data, the functions will do that for you.
	std::cout << "rectA has width " << rectA.getWidth() << " and a height " << rectA.getHeight() << ".\n";
	std::cout << "rectB has width " << rectB.getWidth() << " and a height " << rectB.getHeight() << ".\n";
	std::cout << "rectA has perimeter " << rectA.getWidth() << " and area " << rectA.getArea() << ".\n";
	std::cout << "rectB has perimeter " << rectB.getWidth() << " and area " << rectB.getArea() << ".\n";

	return 0;
}

double Rectangle::getWidth() {
	return width;
}

double Rectangle::getHeight() {
	return height;
}

double Rectangle::getArea() {
	return (width * height);
}

double Rectangle::getPerimeter() {
	return (2 * (width + height));
}