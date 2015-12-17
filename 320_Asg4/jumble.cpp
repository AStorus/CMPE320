#include "jumble_10103737.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//Assignment 4 andrew storus 

using namespace std;

JumblePuzzle::JumblePuzzle(const string& word, const string& dif)
{
	size = word.length();
	if (size < 3 || size > 10)
		throw BadJumbleException("Word must be between 3 and 10 characters");

	if (dif == "easy")
		size = size * 2;
	else if (dif == "medium")
		size = size * 3;
	else if (dif == "hard")
		size = size * 4;
	else
		throw BadJumbleException("Enter only \"easy\", \"medium\", or \"hard\".");

	jumble = new char*[size];

	//Allocate array on the heap
	for (int i = 0; i < size; i++)
		jumble[i] = new char[size];

	
	srand(time(NULL));
	// Fill 2D array with random lowercase characters
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			jumble[i][j] = (char)(rand() % 25 + 'a');//generating random int in lower case ascii value range

	// generate random row and column for the word
	row = rand() % size;
	col = rand() % size;

	//Length of string
	int wordLength = word.size();
	//Number of Characters placed so far
	direction = rand() % 4;
	
	for (int i = 0; i < wordLength; i++) {
		//Place letters moving up
		if (direction == 0) {
			//If word is too long to be placed from bottom to top, 
			if (wordLength > (row + 1)) {
				//Go to the next direction
				direction += 1;
			}
			else {
				jumble[row - i][col] = word.at(i);
			}
		}
		//Place letters moving left to right
		if (direction == 1) {
			//If word is too long
			if (wordLength > (size - col)) {
				//go to the next direction
				direction += 1;
			}
			else {
				jumble[row][col + i] = word.at(i);
			}
		}
		//place letters top to bottom
		if(direction == 2) {
			//If word is too long
			if (wordLength > (size - row)) {
				//go to next direction
				direction += 1;
			}
			else {
				jumble[row + i][col] = word.at(i);
			}
		}
		//place letters right to left
		if (direction == 3) {
			if (wordLength > (col + 1)) {
				direction = (direction + 1) % 4;
			}
			else {
				jumble[row][col - i] = word.at(i);
			}
		}
	}
}

charArrayPtr* JumblePuzzle::getJumble() const
{
	charArrayPtr* newJumble = new char*[size];

	for (int i = 0; i < size; i++)
		newJumble[i] = new char[size];

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			newJumble[i][j] = jumble[i][j];
	}

	return newJumble;
}

JumblePuzzle& JumblePuzzle::operator=(const JumblePuzzle& other)
{
	if (this != &other) //can't assign to the same object
	{
		row = other.getRowPos();
		col = other.getColPos();
		direction = other.getDirection();
		size = other.getSize();
		//Delete old Jumble
		this->~JumblePuzzle();

		// Copy new jumble over
		jumble = new char*[size];
		// Create individual arrays on the heap
		for (int i = 0; i < size; i++)
			jumble[i] = new char[size];

		charArrayPtr* otherJumble = other.getJumble();
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				jumble[i][j] = otherJumble[i][j];
	}
	return *this;
}

JumblePuzzle::JumblePuzzle(const JumblePuzzle& other)
{
	size = other.getSize();
	row = other.getRowPos();
	col = other.getColPos();
	direction = other.getDirection();

	jumble = new char*[size];

	// Create individual arrays on the heap
	for (int i = 0; i < size; i++)
		jumble[i] = new char[size];

	charArrayPtr* otherJumble = other.getJumble();

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			jumble[i][j] = otherJumble[i][j];
}

JumblePuzzle::~JumblePuzzle()
{
	for (int i = 0; i < size; i++)
		delete jumble[i];
	delete[] jumble;
}

char JumblePuzzle::getDirection() const { 
	return direction; 
}
int JumblePuzzle::getSize() const { 
	return size; 
}
int JumblePuzzle::getColPos() const { 
	return col; 
}
int JumblePuzzle::getRowPos() const { 
	return row; 
}

BadJumbleException::BadJumbleException(const string& m) : message(m) { }
string& BadJumbleException::what() { 
	return message; 
}