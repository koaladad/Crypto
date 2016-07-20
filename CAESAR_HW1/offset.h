#ifndef OFFSET_H
#define OFFSET_H
#include <iostream>
using namespace std;

//Class that manages the offset number
class Offset
{
public:
	Offset(char buffer[]);
	int GetOffset();
	void SetOffset(char c);
	void SetOffset(int num);
private:
	int m_offset;
};

#endif