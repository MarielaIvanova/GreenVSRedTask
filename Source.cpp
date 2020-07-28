#include<iostream>
#include<string>
#include"Game.h"

int main() {
	unsigned int x, y; //sizes of the table
	unsigned int coordinateX, coordinateY, N;
	std::string line;
	std::vector<std::vector<Box>> vec;
	std::vector<Box> v;

	Color green(1);
	Color red(0);
	Box b1(0);
	vec.clear();
	v.clear();

	std::cin >> x; //takes the number of columns
	std::cin >> y; //takes the number of rows
	std::cin.ignore();
	for (unsigned int i = 0; i < y; i++) {
		std::getline(std::cin, line);
		for (unsigned int j = 0; j < x; j++) { //for each intiger (1 or 0) we create an object of type box which contains the color
			if (line[j]) {
				if (line[j] == '1') b1.setColor(green);
				else b1.setColor(red);

				v.push_back(b1);
			}
		}
		vec.push_back(v);
		v.clear();
	}

	//coordinates of the box, we will count in how many of the generations that box was green
	std::cin >> coordinateX; 
	std::cin >> coordinateY; 
	std::cin >> N;

	Game game(vec, y, x, N); //crates a game with table(vec), sizes of the table(x and y) and number of Generations(N)
	std::cout << "result: "<< game.countGreens(coordinateY, coordinateX);//prints the result on the console withe the function countGreens(which counts in how many of the generations certain box was green)


	system("pause");
	return 0;
}