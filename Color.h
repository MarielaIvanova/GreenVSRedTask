#pragma once
#include<string>


//Here is initialized the class Color which cotains the color of each box. 
//The class is initialized with one variable of type int which represent the color 0-red, 1-green
//From the class we can get the color of each box either as a number 1 for green and 0 for red or as a string with the function whatIsTheCOlor
class Color
{
public:
	Color(int c = -1) : color(c) {}
	~Color() {}

	Color& operator=(Color const &col) {
		if (this != &col) {
			this->color = col.color;
		}
		return *this;
	}

	void set_Color(int col) { if (col==1 || col ==0) color = col; } //changes the color with a new given value of type int
	int get_Color() { return color; }  //returns intiger- the type of the color

	std::string whatIsTheColor();

private:
	int color;
};

//returns the value of color as a string
std::string Color::whatIsTheColor() {
	if (get_Color() == 1) { return "green"; }
	else if (get_Color() == 0) { return "red"; }
	else { return "error"; }
}