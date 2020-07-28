#pragma once
#include<iostream>
#include"Table.h"


//This class represents the whole game as a Table and how many moves will be made through the game
class Game :virtual public Table {
	Table table;
	int moves;

public:
	std::vector<std::vector<Box>> v1;

	Game(): table(v1, 0,0), moves(0) {}
	Game(std::vector<std::vector<Box>> t, int sizeX = 0, int sizeY = 0, int m = 0): table(t, sizeX, sizeY), moves(m) {}
	~Game() {}
	//assigns the values from right side operand(object of type Game) to the left side operand(again object of type Game)
	Game& operator=(Game const &g) { 
		if (this != &g) {
			table = g.table;  //assigns to the table the value of the table of the other game
			moves = g.moves;  //assigns to the moves the value of the moves of the moves of the other game
		}
		return *this;
	}
	

	void setTable(Table& t) { table = t; }  //changes the values of object of type Table with those of another object from the same type
	Table& getTable() { return table; }     //returns an object from type Table

	void setMoves(int m) { moves = m; }  //changes the value of the moves of the current game with a new given value
	int getMoves() { return moves; }     //returns the number of the moves of the current game

	int countGreens(unsigned int x,unsigned int y);  //The function counts in how many of the game ganeretaion a given box is green

private:
	int checkTheColor(int currColor, int greenNeighboursCounter); //checks the color of a box based on the number of green neighbours it has
	int recalculateTheColor(Box b, Box s1, Box s2, Box s3, Box s4, Box s5, Box s6, Box s7, Box s8); //returns the color of a box in the inner part of the table depending on its neigbours
	int recalculateTheColorCase2(Box b, Box s1, Box s2, Box s3, Box s4, Box s5); //returns the color of a box from the outer part of the table (the boxes from the first and last column, and first and last row except the boxes from the edges)
	int recalculateTheColorCase3(Box b, Box s1, Box s2, Box s3); //returns the color of the boxes from the edges
	void calculateOneGeneration(Game& newGame); //changes all the boxes in the table that should be changed after one generation of the game
	
};

//the function takes as arguments intiger representing the color of a box and the number of green neighbors of the box
//the function check if the box remains still the same color or it changes its color
//the function returns the color of the box after the check
//the returned value is of type int: 0 for red and 1 for green
int Game::checkTheColor(int currColor, int greenCount) {

	if (currColor == 0 && (greenCount == 3 || greenCount == 6)) return 1; //check if the box is red of it is if 6 or 3 of it neighbours are green then the function returns 1 which means that we have to change the color of the box to green
	else if (currColor == 0)return 0; //if the box is green but its neighbours are not 6 or 3 it stays green- the function returns 0
	else if (currColor == 1 && (greenCount == 0 || greenCount == 1 || greenCount == 4 || greenCount == 5 || greenCount == 7 || greenCount == 8))return 0; //check if the box is green of it is if 0, 1, 4, 5 ,7 or 8 of it neighbours are green then the function returns 0 which means that we have to change the color of the box to red
	else return 1; //if we have not entered any of the the cases before that one then the color of the box is red and it should remains red
}

//The function recalcuates the color of a certain box that is in the inner part of the table
//The function takes first the box- the one that will be calculated(current) and all the eight boxes surrounding it(s1-s8)
//The function returns the the color of the box as an intiger (0 for red and 1 for green) 
int Game:: recalculateTheColor(Box current, Box s1, Box s2, Box s3, Box s4, Box s5, Box s6, Box s7, Box s8) {
	int greenCount = 0; //counts how many of the boxes surounding current box are green 

	if (s1.getColor().get_Color() == 1) greenCount += 1;
	if (s2.getColor().get_Color() == 1) greenCount += 1;
	if (s3.getColor().get_Color() == 1) greenCount += 1;
	if (s4.getColor().get_Color() == 1) greenCount += 1;
	if (s5.getColor().get_Color() == 1) greenCount += 1;
	if (s6.getColor().get_Color() == 1) greenCount += 1;
	if (s7.getColor().get_Color() == 1) greenCount += 1;
	if (s8.getColor().get_Color() == 1) greenCount += 1;

	return checkTheColor(current.getColor().get_Color(), greenCount); 
}

//The function is the same as the upper one but is used for the boxes on the sides of the table who has only 5 neighbours(except those in the edjes)
int Game::recalculateTheColorCase2(Box current, Box s1, Box s2, Box s3, Box s4, Box s5) {
	int greenCount = 0; //counts how many of the boxes surounding current box are green 

	if (s1.getColor().get_Color() == 1) greenCount += 1;
	if (s2.getColor().get_Color() == 1) greenCount += 1;
	if (s3.getColor().get_Color() == 1) greenCount += 1;
	if (s4.getColor().get_Color() == 1) greenCount += 1;
	if (s5.getColor().get_Color() == 1) greenCount += 1;

	return checkTheColor(current.getColor().get_Color(), greenCount);
}

//The function is the same as the upper two but is used to calculate the color of the 4 boxes in the 4 edges of the table who has only 3 neighbours
int Game::recalculateTheColorCase3(Box current, Box s1, Box s2, Box s3) {
	int greenCount = 0; //counts how many of the boxes surounding current box are green 

	if (s1.getColor().get_Color() == 1) greenCount += 1;
	if (s2.getColor().get_Color() == 1) greenCount += 1;
	if (s3.getColor().get_Color() == 1) greenCount += 1;

	return checkTheColor(current.getColor().get_Color(), greenCount);
}

//the function takes as a argument the game in it current state
//for each box in the table we check if it should be red or green on the next generation and we change its color depending on its neighbours according to the rules of the game
//the functio is of type void but the argument it takes is a refference so tha all the changes that we made in variable newGame will stay and after the execution 
//of the function the game will change its state and the boxes will change their colors
void Game::calculateOneGeneration(Game& newGame) {

	Color red(0);
	Color green(1);
	Game currGame = newGame; //we crate a a new game- currGame in which we be the same as the the game before the changes, we will use it while we making changes so that we can see how the game was looking before those changes 

	//calculates the color of the last left box
	if (1 == recalculateTheColorCase3(currGame.getTable().get_Table().at(currGame.getTable().getX() - 1).at(0), currGame.getTable().get_Table().at(currGame.getTable().getX() - 2).at(0), currGame.getTable().get_Table().at(currGame.getTable().getX() - 2).at(1), currGame.getTable().get_Table().at(currGame.getTable().getX() - 1).at(1))) {
		newGame.getTable().get_Table().at(currGame.getTable().getX() - 1).at(0).setColor(green); std::cout << "green" << std::endl;
	}
	else newGame.getTable().get_Table().at(currGame.getTable().getX() - 1).at(0).setColor(red);
	
	//calculates the color of the last right box
	if (1 == recalculateTheColorCase3(currGame.getTable().get_Table()[currGame.getTable().getX() - 1][currGame.getTable().getY() - 1], currGame.getTable().get_Table()[currGame.getTable().getX() - 2][currGame.getTable().getY() - 2], currGame.getTable().get_Table()[currGame.getTable().getX() - 1][currGame.getTable().getY() - 2], currGame.getTable().get_Table()[currGame.getTable().getX() - 2][currGame.getTable().getY() - 1])) {
		newGame.getTable().get_Table()[currGame.getTable().getX() - 1][currGame.getTable().getY() - 1].setColor(green);
	}
	else newGame.getTable().get_Table()[currGame.getTable().getX() - 1][currGame.getTable().getY() - 1].setColor(red);
	
	//calculates the color of the upper right box
	if (1 == recalculateTheColorCase3(currGame.getTable().get_Table()[0][currGame.getTable().getY() - 1], currGame.getTable().get_Table()[0][currGame.getTable().getY() - 2], currGame.getTable().get_Table()[1][currGame.getTable().getY() - 2], currGame.getTable().get_Table()[1][currGame.getTable().getY() - 1])) {
		newGame.getTable().get_Table()[0][currGame.getTable().getY() - 1].setColor(green);
	}
	else newGame.getTable().get_Table()[0][getTable().getY() - 1].setColor(red);

	//calculates the color of the upper left box
	if (1 == recalculateTheColorCase3(currGame.getTable().get_Table()[0][0], currGame.getTable().get_Table()[0][1], currGame.getTable().get_Table()[1][1], currGame.getTable().get_Table()[1][0])) {
		newGame.getTable().get_Table()[0][0].setColor(green);
	}
	else newGame.getTable().get_Table()[0][0].setColor(red);

	//calculates the color of each box from the first row except the edges
	for (int j = 1; j <= currGame.getTable().getY() - 2; j++) {

		if (1 == recalculateTheColorCase2(currGame.getTable().get_Table()[0][j],
			currGame.getTable().get_Table()[0][j - 1], currGame.getTable().get_Table()[0][j + 1],
			currGame.getTable().get_Table()[1][j - 1], currGame.getTable().get_Table()[1][j], currGame.getTable().get_Table()[1][j + 1]))
		{
			newGame.getTable().get_Table()[0][j].setColor(green);
		}
		else newGame.getTable().get_Table()[0][j].setColor(red);
	}

	//calculates the color of each box from the last row except the edges
	for (int j = 1; j <= getTable().getY() - 2; j++) {

		if (1 == recalculateTheColorCase2(currGame.getTable().get_Table()[currGame.getTable().getX() - 1][j],
			currGame.getTable().get_Table()[currGame.getTable().getX() - 2][j - 1], currGame.getTable().get_Table()[currGame.getTable().getX() - 2][j], currGame.getTable().get_Table()[currGame.getTable().getX() - 2][j + 1],
			currGame.getTable().get_Table()[currGame.getTable().getX() - 1][j - 1], currGame.getTable().get_Table()[currGame.getTable().getX() - 1][j + 1])) 
		{
			newGame.getTable().get_Table()[currGame.getTable().getX() - 1][j].setColor(green);
		}
		else newGame.getTable().get_Table()[currGame.getTable().getX() - 1][j].setColor(red);
	}

	//calculates the color of each box from the last column except the edges
	for (int i = 1; i <= currGame.getTable().getX() - 2; i++) {

		if (1 == recalculateTheColorCase2(currGame.getTable().get_Table()[i][currGame.getTable().getX() - 1],
			currGame.getTable().get_Table()[i - 1][currGame.getTable().getY() - 2], currGame.getTable().get_Table()[i - 1][currGame.getTable().getY() - 1],
			currGame.getTable().get_Table()[i][currGame.getTable().getY() - 2],
			currGame.getTable().get_Table()[i + 1][currGame.getTable().getY() - 2], currGame.getTable().get_Table()[i + 1][currGame.getTable().getY() - 1])) 
		{
			newGame.getTable().get_Table()[i][currGame.getTable().getX() - 1].setColor(green);
		}
		else newGame.getTable().get_Table()[i][currGame.getTable().getX()- 1].setColor(red);
	}

	//calculates the color of each box from the first column except the edges
	for (int i = 1; i <= currGame.getTable().getX() - 2; i++) {

		if (1 == recalculateTheColorCase2(currGame.getTable().get_Table()[i][0],
			currGame.getTable().get_Table()[i - 1][0], currGame.getTable().get_Table()[i - 1][1],
													   currGame.getTable().get_Table()[i][1],
			currGame.getTable().get_Table()[i + 1][0], currGame.getTable().get_Table()[i + 1][1])) 
		{
			newGame.getTable().get_Table()[i][0].setColor(green);
		}
		else newGame.getTable().get_Table()[i][0].setColor(red);
	}

	//calculates the color of each box from the whole inner part of the table
	for (int i = 1; i <= currGame.getTable().getX()-2; i++) {

		for (int j = 1; j <= getTable().getY()-2; j++) {

			if (1 == recalculateTheColor(currGame.getTable().get_Table()[i][j],
				currGame.getTable().get_Table()[i - 1][j - 1], currGame.getTable().get_Table()[i - 1][j], currGame.getTable().get_Table()[i - 1][j + 1],
				currGame.getTable().get_Table()[i][j - 1],												  currGame.getTable().get_Table()[i][j + 1],
				currGame.getTable().get_Table()[i + 1][j - 1], currGame.getTable().get_Table()[i + 1][j], currGame.getTable().get_Table()[i + 1][j + 1]))
			{
				newGame.getTable().get_Table()[i][j].setColor(green);
			}
			else newGame.getTable().get_Table()[i][j].setColor(red);
		}
	}

}

//the fuction takes as arguments the positions of a box(its coordinates)
//the function is executed over a game and for the numbers of the moves/generations it check in how many of them certain box is green
//the function return the number of the times the box has been green
int Game::countGreens(unsigned int x,unsigned int y) {

	int after=0, cnt=0; //in tha variable after we save the color of the box after every generation, cnt is counter
	Game currGame = *this;

	for (int i = 0; i < getMoves(); i++) {

		if (x < currGame.getTable().get_Table().size() && y < currGame.getTable().get_Table().at(x).size()){
			calculateOneGeneration(currGame); //changes the colors of the boxes of the game once
			after = currGame.getTable().get_Table()[x][y].getColor().get_Color(); //saves the color of the box after the change
		}

		if (after==1) cnt += 1;	 //checks if the box is green in the new generation if it is then we increase the counter with 1
	}

	return cnt;//returns the value of the counter- in how many of the generations the box has been green
}


/*
POSITION OF THE NEIGHBOURS OF A BOX

     s1  s2  s3
	 s4  ct  s5
	 s6  s7  s8
*/