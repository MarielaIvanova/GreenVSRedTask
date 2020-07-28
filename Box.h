#pragma once
#include"Color.h"

//The class Box inherites the class color, which is the main quality that each object of type box should contain
class Box: public virtual Color {
	Color color;

public:
	Box(int colour = -1):Color(colour) {}
	~Box() {}
	
	//assigns the values from right side operand (object of type Box) to the left side operand (again object of type Box)
	Box& operator=(Box const &b) {
		if (this != &b) {
			this->color = b.color;
		}
		return *this;
	}

	void setColor(Color& col) { color=col; }  //changes the color of the box with a given object of type Color
	Color& getColor() { return color; }  //returns the color of the object of the type Box(the returned object id from type Color)
	
};