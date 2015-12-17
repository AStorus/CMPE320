#pragma once

#include <string>

using namespace std;

//assignment 4 andrew storus

typedef char* charArrayPtr;

class JumblePuzzle
{
public:
	// Constructors
	JumblePuzzle(const string&, const string&);
	JumblePuzzle(const JumblePuzzle&);
	// Destructor
	~JumblePuzzle();
	// Overloaded Assignment Operator
	JumblePuzzle& operator=(const JumblePuzzle&);
	// Accessors
	charArrayPtr* getJumble() const;
	int getSize() const;
	int getRowPos() const;
	int getColPos() const;
	char getDirection() const;

private:
	int size;
	int row;
	int col;
	int direction;
	charArrayPtr* jumble;
};

class BadJumbleException
{
public:
	BadJumbleException(const string&); 							
	string& what();						
private:
	string message;
};
