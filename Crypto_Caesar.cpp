// Crypto_Caesar.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <fstream>
#include <vector>
#include "offset.h"
using namespace std;

char Encrypt(char c, int offset);
char Decrypt(char c, int offset);

int main()
{
	char buffer[255];
	cout << "Enter offset:";
	cin >> buffer;
	Offset offset = Offset(buffer);

	cout << "offset is " << offset.GetOffset() << endl;

	char letter = 'a';
	cout << "letter is " << letter << endl;
	cout << "encrypted letter is " << Encrypt(letter, offset.GetOffset()) << endl;
	cout << "decrypted letter is " << Decrypt(letter, offset.GetOffset()) << endl;

	letter = 'A';
	cout << "letter is " << letter << endl;
	cout << "encrypted letter is " << Encrypt(letter, offset.GetOffset()) << endl;
	cout << "decrypted letter is " << Decrypt(letter, offset.GetOffset()) << endl;

	letter = 'b';
	cout << "letter is " << letter << endl;
	cout << "encrypted letter is " << Encrypt(letter, offset.GetOffset()) << endl;
	cout << "decrypted letter is " << Decrypt(letter, offset.GetOffset()) << endl;

	letter = 'B';
	cout << "letter is " << letter << endl;
	cout << "encrypted letter is " << Encrypt(letter, offset.GetOffset()) << endl;
	cout << "decrypted letter is " << Decrypt(letter, offset.GetOffset()) << endl;

	//cout << "{ is " << (int)'{' << endl; //123
	//cout << ") is " << (int)')'; //41

	//test input
	/*
	const int MYSTRINGLEN = 20;
	char * ptr = "this is a test\n";
	char input[MYSTRINGLEN] = "this is a test\n";

	for (int i = 0; i < MYSTRINGLEN; ++i)
	{
		cout << input[i];
	}*/	

    return 0;
}
/*
a-z: 97 to 122
A-Z: 65 to 90
*/
char Encrypt(char c, int offset)
{
	//if upper-case, handle 65-90 range
	//subtract 65 and re-insert
	if (isupper(c))
	{
		c = (c - 65 + offset) % 26 + 65;
	}
	//if lower-case, handle 97-122 range
	//subtract 97 and re-insert
	else if (islower(c))
	{
		c = ((c - 97) + offset % 26) + 97;
	}
	else
	{
		cout << "char used in Encrypt method is not a char\n";
		exit(1);
	}
	
	return c;
}

char Decrypt(char c, int offset)
{
	//-65
	if (isupper(c))
	{
		c = c-65 + ((26-offset) % 26) + 65;
		//c = c - 65;
		//c = (c - (26 - offset)) % 26;
		//c = c +65;
	}
	//-97
	else if (islower(c))
	{
		c = c - 97 + (26 -offset % 26) + 97;
	}
	else
	{
		cout << "char used in Decrypt method is not a char\n";
		exit(1);
	}

	return c;
}