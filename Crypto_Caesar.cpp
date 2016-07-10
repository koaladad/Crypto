// Crypto_Caesar.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "offset.h"
using namespace std;

char Encrypt(char c, int offset);
char Decrypt(char c, int offset);

void ProcessPlaintext(int shift);
void Encryption(int charCount, char textArray[], int shift);

void ProcessCiphertext(int shift);
void Decryption(int charCount, char textArray[], int shift);

void DecryptCiphertext();
char EncryptChar(char c, int shift);
char DecryptChar(char c, int shift);

vector<string> &split(const string &s, char delim, vector<string> &elems);
vector<string> split(const string &s, char delim);


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
			//ProcessCiphertext(0); //load ciphertext to textArray
			DecryptCiphertext();
			//finds most commonly occurring letters, top 10 will be checked top down, assuming 'e' as root offset
			//needs a dictionary.txt to scour through on each word
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

	//char currChar;
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

char EncryptChar(char c, int shift)
{
	// Check if it is within the range of lowercase ASCII (a - z : 97 - 122)
	// if (textArray[i] > 96 && textArray[i] < 123)
	if (islower(c))
	{
		c = (char)(((c - 'a' + shift + 26) % 26) + 'a');
	}
	// Check if it is within the range of uppercase ASCII (A - Z : 65 - 90)
	// else if (encryptedText[i] > 64 && encryptedText[i] < 91)
	else if (isupper(c))
	{
		c = (char)(((c - 'A' + shift + 26) % 26) + 'A');
	}
	return c;
}

char DecryptChar(char c, int shift)
{
	// Check if it is within the range of lowercase ASCII (a - z : 97 - 122)
	// if (textArray[i] > 96 && textArray[i] < 123)
	if (islower(c))
	{
		c = (char)(((c - 'a' - shift + 26) % 26) + 'a');
	}
	// Check if it is within the range of uppercase ASCII (A - Z : 65 - 90)
	// else if (encryptedText[i] > 64 && encryptedText[i] < 91)
	else if (isupper(c))
	{
		c = (char)(((c - 'A' - shift + 26) % 26) + 'A');
	}
	// Characters other than uppercase and lowercase letters stay the same
	return c;
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

	//char currChar;
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

//performs cryptanalysis on ciphertext
void DecryptCiphertext()
{
	//Load textArray with ciphertext.txt
	// global variable??
	const int arraySize = 10000;
	char textArray[arraySize] = { 0 };

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
		//cout << "Cipher Message: " << endl;
		for (int i = 0; i <= charCount; i++)
		{
			//cout << textArray[i];
		}
		//cout << endl << endl;

		//Decryption(charCount, textArray, 0);
	}
	else
	{
		cout << "\nCannot open file!\n";
	}

	//Create an int array and initialize all elements to 0
	int wordCount[26] = { 0 };

	//load dictionary vector
	ifstream dict("dictionary.txt");

	if (!dict) //test the file is open
	{
		cout << "Error opening dictionary text file (""dictionary.txt"")" << endl;
		system("pause");
		return;
	}

	string line;
	vector<string> dictionaryVec;

	cout << "Loading Dictionary..." << endl;
	while (std::getline(dict, line))
	{
		dictionaryVec.push_back(line);
	}
	cout << "Finished Loading Dictionary..." << endl;

	cout << "Searching Each Word in Dictionary..." << endl;
	//iterate through each offset score
	for (int offset = 0; offset < 26; offset++)
	{
		//copy textArray to string
		string str(textArray);

		//break string into space-separated words
		//place each word into a vector
		vector<string> textVec;
		textVec = split(str, ' ');

		cout << "Checking Offset: " << offset;
		//cout << textVec[0] << " " << textVec[1] << endl;
		//check each 'word' for a dictionary match
		//for each match, increment wordCount[offset];
		for (auto word : textVec)
		{
			//encrypt word using EncryptChar function
			string encryptedWord = word;
			
			for (char& c : encryptedWord)
			{
				c = DecryptChar(c, offset);
			}
			
			//cout << "NEW WORD: " << encryptedWord << endl;
			cout << ".";
			//if match found, increment wordCount[offset]
			if (std::find(dictionaryVec.begin(), dictionaryVec.end(),encryptedWord) != dictionaryVec.end())
			{
				wordCount[offset] += 1;
			}
		}
		cout << endl;
		//cout << "Matches found: " << wordCount[offset] << endl;
	}

	//get index of max value in wordCount array. That is the Decrypt Offset
	int number = 0;
	int max = wordCount[0];

	for (int j = 1; j < 26; j++)
	{
		if (max < wordCount[j])
		{
			max = wordCount[j];
			number = j;
		}
	}

	//Display the decrypted message and Decrypted Offset
	cout << "Predicted Decryption Shift is " << number << endl;

	cout << "Decrypted Message Below..." << endl;

	// cout << "\nThe offset is " << shift << endl;
	//ProcessPlaintext(shift);
	ProcessCiphertext(number);


}

vector<string> &split(const string &s, char delim, vector<string> &elems) {
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}


vector<string> split(const string &s, char delim) {
	vector<string> elems;
	split(s, delim, elems);
	return elems;
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

