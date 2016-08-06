#include <iostream>
#include <Windows.h>
#include "RSAKeys.h"
using namespace std;

bool IsPrime(unsigned long num);
unsigned long GetRandomPrime();

int main()
{
	// A - RSA key generation
	// B - Encrypt
	// C - Decrypt

	char choice[255];
	bool run = true;

	while (run)
	{

		cout << "******************************************" << endl
			<< "Please select from the following options: " << endl
			<< "[A]  RSA Key Generation" << endl
			<< "[B]  Encryption" << endl
			<< "[C]  Decryption" << endl
			<< "[D]  Abort" << endl
			<< "******************************************" << endl;
		cin >> choice;
		choice[0] = toupper(choice[0]);
		cout << endl;

		if (choice[0] == 'A')
		{
			cout << "-RSA Key Generation-" << endl 
				 << "Please enter: ";

			unsigned int randPrime = GetRandomPrime();
			cout << "Random Prime is " << randPrime << endl;
			
			int num;
			do {
				cout << "Enter a number (0 to quit): " << endl;
				cin >> num;
				if (num) {
					if (IsPrime(num))
						cout << num << " is a prime number " << endl;
					else
						cout << num << " is NOT a prime number " << endl;
				}
			} while (num > 0);


		}
		else if (choice[0] == 'B')
		{
			cout << "-Encryption-" << endl 
				 << "Please enter: ";

		}
		else if (choice[0] == 'C')
		{
			cout << "-Decryption-" << endl
				<< "Please enter: ";

		}
		else if (choice[0] == 'D')
		{
			cout << "Exiting program. Goodbye!\n";
			Sleep(200);
			run = false;
		}
		else // if input is something else other than the choices above
		{
			cout << "Invalid input! Please try again.\n";
		}
		cout << endl;

		//memset(&key[0], 0, sizeof(key));
		//memset(&key[0], 0, sizeof(choice));
	}

	getchar();
	return 0;
}

bool IsPrime(unsigned long num)
{
	//<2 not prime
	if (num < 2) 
		return false;

	//div by 2 not prime
	if (num > 2 && (num % 2) == 0)
		return false;

	if (num % 3 == 0)
		return false;

	//2 is prime
	if (num == 2)
		return true;

	//check all numbers up to that number to see if prime
	//only need to check up to square root of number for primality
	//only need to check odd numbers
	for (unsigned long i = 3; i < sqrt(num); i+=2)
	{
		//cout << "checking: " << i << endl;		
		if ((num % i) == 0)
		{
			return false;
		}
	}
	//passed through all tests, is prime
	return true; 
}

//gets a random prime between 10k and 100k
unsigned long GetRandomPrime()
{
	unsigned long max = 100000;
	unsigned long min = 10000;
	unsigned long returnVal = rand() % (max - min + 1) + min;
	while (!IsPrime(returnVal))
	{
		returnVal = rand() % (max - min + 1) + min;
	}

	return returnVal;
}
