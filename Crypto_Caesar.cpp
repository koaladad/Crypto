// Crypto_Caesar.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "offset.h"
using namespace std;

char Encrypt(char c, int offset);
char Decrypt(char c, int offset);

void ProcessPlaintext(int shift);
void Encryption(int charCount, char textArray[], int shift);

void ProcessCiphertext(int shift);
void Decryption(int charCount, char textArray[], int shift);


int main()
{
	char choice;
	char key[255]; //one or two digit key;
	int shift = 0;
	bool run = true;

	while (run)
	{
		// Empty out key arr buffer every loop ? (use memset)
		// http://stackoverflow.com/questions/632846/clearing-a-char-array-c
		// Clear choice buffer

		cout << "Please select from the following options: " << endl
			<< "[A]  Encrypt with a key" << endl
			<< "[B]  Decrypt with a key" << endl
			<< "[C]  Decrypt without a key" << endl
			<< "[D]  Abort" << endl << endl;
		cin >> choice;
		choice = toupper(choice);
		cout << endl;

		if (choice == 'A')
		{
			cout << "-Encryption with a key-" << endl << "Please enter your desired key (0-25): ";
			cin >> key;
			Offset offset = Offset(key);
			shift = offset.GetOffset();
			// cout << "\nThe offset is " << shift << endl;
			ProcessPlaintext(shift);
		}
		else if (choice == 'B')
		{
			cout << "-Decryption with a key-" << endl << "Please enter your key (0-25): ";
			cin >> key;
			Offset offset = Offset(key);
			shift = offset.GetOffset();
			// cout << "\nThe offset is " << shift << endl;
			//ProcessPlaintext(shift);
			ProcessCiphertext(shift);
		}
		else if (choice == 'C')
		{


		}
		else if (choice == 'D')
		{
			cout << "Exiting program. Goodbye!\n";
			run = false;
		}
		else // if input is something else other than the choices above
		{
			cout << "Invalid input! Please try again.\n";
		}
		cout << endl;
	}


	//getchar();
	getchar();
	return 0;
}

void ProcessPlaintext(int shift)
{
	// global variable??
	const int arraySize = 10000;
	char textArray[arraySize] = {0};

	char currChar;
	int charCount = 0; // number of characters in the file
	int i = 0;

	ifstream inFile;
	//string fileName;

	// Prompt for file name (plain text ...) to be (encrypted ...) 
	// Text file name is in (Debug) folder within exe
	//cout << "Please enter the text file name: ";
	//cin >> fileName;
	//inFile.open(fileName.c_str());

	inFile.open("plain.txt", ios::in); // open the file to be read

	if (inFile.is_open())
	{
		//string contents((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
		//contents.c_str();

		// Store the text from the input file to textArray[]
		while (!inFile.eof())
		{
			inFile.get(textArray[i]);
			//cout << textArray[i];
			//textArray[i] = tolower(textArray[i]); //converts all uppercase letters to lowercase
			 charCount = i++;
		}
		inFile.close();

		//cout << charCount << "characters successfully read." << endl;

		// Show the contents of the text to console
		cout << "Plaintext Message: " << endl;
		for (int i = 0; i <= charCount; i++)
		{
			cout << textArray[i];
		}
		cout << endl << endl;

		Encryption(charCount, textArray, shift);
		// void Encryption(int charCounter, int textArray[], int shift)
		//encrypt(charCount, encryptedText, shift, newLetter);
	}
	else
	{
		cout << "\nCannot open file!\n";
	}

	//inFile.close();
}

void Encryption(int charCount, char textArray[], int shift)
//void decipher(int allCharCounter, int encryptedText[], int shift, char newLetter)
{
	//const int arraySize = 10000;
	//int enryptedText[arraySize] = {0};

	// Loop until it reaches the very last character at the end of file
	for (int i = 0; i < charCount; i++)
	{
		// Check if it is within the range of lowercase ASCII (a - z : 97 - 122)
		// if (textArray[i] > 96 && textArray[i] < 123)
		if (islower(textArray[i]))
		{
			textArray[i] = (char)(((textArray[i] - 'a' + shift + 26) % 26) + 'a');
		}
		// Check if it is within the range of uppercase ASCII (A - Z : 65 - 90)
		// else if (encryptedText[i] > 64 && encryptedText[i] < 91)
		else if (isupper(textArray[i]))
		{
			textArray[i] = (char)(((textArray[i] - 'A' + shift + 26) % 26) + 'A');
		}
		// Characters other than uppercase and lowercase letters stay the same
		
		cout << textArray[i]; // Print to the screen the encoded characters
		// put each character to an output text file called encrypted.txt
	}

	// cout << "Encryption successful. File saved as << ??? << "." << "\nReturning to main menu." << endl << endl;

	cout << endl;
}

void ProcessCiphertext(int shift)
{
	// global variable??
	const int arraySize = 10000;
	char textArray[arraySize] = { 0 };

	char currChar;
	int charCount = 0; // number of characters in the file
	int i = 0;

	ifstream inFile; 
	//string fileName;

	// Prompt for file name (cipher text ...) to be (decrypted ...) 
	// Text file name is in (Debug) folder within exe
	//cout << "Please enter the text file name: ";
	//cin >> fileName;
	//inFile.open(fileName.c_str());

	inFile.open("cipher.txt", ios::in); // open the file to be read

	if (inFile.is_open())
	{
		//string contents((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
		//contents.c_str();

		// Store the text from the input file to textArray[]
		while (!inFile.eof())
		{
			inFile.get(textArray[i]);
			//cout << textArray[i];
			//textArray[i] = tolower(textArray[i]); //converts all uppercase letters to lowercase
			charCount = i++;
		}
		inFile.close();

		//cout << charCount << "characters successfully read." << endl;

		// Show the contents of the text to console
		cout << "Cipher Message: " << endl;
		for (int i = 0; i <= charCount; i++)
		{
			cout << textArray[i];
		}
		cout << endl << endl;

		Decryption(charCount, textArray, shift);
	}
	else
	{
		cout << "\nCannot open file!\n";
	}

	//inFile.close();
}

void Decryption(int charCount, char textArray[], int shift)
//void decipher(int allCharCounter, int encryptedText[], int shift, char newLetter)
{
	//const int arraySize = 10000;
	//int enryptedText[arraySize] = {0};

	// Loop until it reaches the very last character at the end of file
	for (int i = 0; i < charCount; i++)
	{
		// Check if it is within the range of lowercase ASCII (a - z : 97 - 122)
		// if (textArray[i] > 96 && textArray[i] < 123)
		if (islower(textArray[i]))
		{
			textArray[i] = (char)(((textArray[i] - 'a' - shift + 26) % 26) + 'a');
		}
		// Check if it is within the range of uppercase ASCII (A - Z : 65 - 90)
		// else if (encryptedText[i] > 64 && encryptedText[i] < 91)
		else if (isupper(textArray[i]))
		{
			textArray[i] = (char)(((textArray[i] - 'A' - shift + 26) % 26) + 'A');
		}
		// Characters other than uppercase and lowercase letters stay the same

		cout << textArray[i]; // Print to the screen the encoded characters
		// put each character to an output text file called encrypted.txt
	}

	// cout << "Decryption successful. File saved as << ??? << "." << "\nReturning to main menu." << endl << endl;

	cout << endl;
}


/*
a-z: 97 to 122
A-Z: 65 to 90
*/

/* //Encryption Algorithm
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
}*/

/* //Decrytion Algorithm
char Decrypt(char c, int offset)
{
	//-65
	if (isupper(c))
	{
		c = c - 65 + ((26 - offset) % 26) + 65;
		//c = c - 65;
		//c = (c - (26 - offset)) % 26;
		//c = c +65;
	}
	//-97
	else if (islower(c))
	{
		c = c - 97 + (26 - offset % 26) + 97;
	}
	else
	{
		cout << "char used in Decrypt method is not a char\n";
		exit(1);
	}

	return c;
}*/

