#include <iostream>
#include <limits>
#include <string>
#include <sstream>
#include <Windows.h>
#include <ctime>
#include <cstdlib>
#include <string>
#include <stdlib.h>
#include <math.h>
#include "RSAKeys.h"
using namespace std;


bool IsPrime(unsigned long num);
unsigned long GetRandomPrime(unsigned long min, unsigned long max);
unsigned long GetZ(unsigned long p, unsigned long q);
unsigned long GetK(unsigned long magicNumber);
unsigned long GetN(unsigned long p, unsigned long q);
unsigned long GetJ(unsigned long z, unsigned long k, unsigned long iMin, unsigned long iMax);
unsigned long EncryptionResult(unsigned long p, unsigned long k, unsigned long n);
unsigned long DecryptionResult(unsigned long e, unsigned long j, unsigned long n);

int main()
{
	// A - RSA key generation
	// B - Encrypt
	// C - Decrypt

	char choice[255];
	bool run = true;
	
	//Grant vars for testing
	bool numbersGenerated = false;
	unsigned long min = 10000;
	unsigned long max = 20000;
	unsigned long p = 0;
	unsigned long q = 0;
	unsigned long n = 0;
	unsigned long z = 0; //totient
	unsigned long k = 0; //coprime to z/totient function
	unsigned long j = 0; //secret key
	unsigned long plaintext = 0;
	unsigned long encryptedtext = 0;

	//Encryption requires K & N, with input P to produce E
	//Decryption requires J & N, with input E to produce P
	//for initial requirements:
		//K requires totient, totient requires P&Q (N)
		//N requires P&Q
		//J requires Z & K, K requires Z, Z requires P&Q(N)
	//

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
				 << "";

			//RSAKeys newkeys = RSAKeys(); // For Testing 

			//1) Get P&Q
			p = GetRandomPrime(min,max);
			cout << "p is " << p << endl;

			q = GetRandomPrime(min, max);
			cout << "q is " << q << endl;

			//2) Get N
			n = GetN(p, q);
			cout << "n is " << n << endl;

			//3) Get Z
			z = GetZ(p, q);
			cout << "z is " << z << endl;

			//4) GetK - co-prime
			k = GetK(z);
			cout << "k is " << k << endl;

			//5) GetJ - **secret key**
			j = GetJ(z, k, min, max);
			cout << "j is " << j << endl;

			numbersGenerated = true;
			

		}
		else if (choice[0] == 'B')
		{
			if (!numbersGenerated)
			{
				//numbers not generated, send message they need to generate numbers before encrypting
				cout << "You will need generate numbers before encrypting, please select option A first.\n";
			}
			else
			{
				cout << "-Encryption-" << endl
					<< "Please enter the plaintext to encrypt: " << endl;

				std::string line;
				unsigned long plaintext;
				while (std::getline(std::cin, line))
				{
					std::stringstream ss(line);
					if (ss >> plaintext)
					{
						if (ss.eof())
						{   // Success
							break;
						}
					}
					std::cout << "Requirements: must be a number (no chars allowed)" << std::endl;
				}

				cout << "plaintext: " << plaintext << endl;
				cout << "k: " << k << endl;
				cout << "n: " << n << endl;

				encryptedtext = EncryptionResult(plaintext, k, n);
				std::cout << endl << "*** The resulting encrypted text is ***: " << encryptedtext << std::endl;

			}



		}
		else if (choice[0] == 'C')
		{
			cout << "-Decryption-" << endl
				<< "Please enter: " << endl;

			std::string line;
			unsigned long encryptedtext;
			while (std::getline(std::cin, line))
			{
				std::stringstream ss(line);
				if (ss >> encryptedtext)
				{
					if (ss.eof())
					{   // Success
						break;
					}
				}
				std::cout << "Requirements: must be a number (no chars allowed)" << std::endl;
			}
			
			plaintext = DecryptionResult(encryptedtext,j,p);
			std::cout << endl << "*** The resulting encrypted text is ***: " << plaintext << std::endl;

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
unsigned long GetRandomPrime(unsigned long iMin, unsigned long iMax)
{
	unsigned long min = iMin;
	unsigned long max = iMax;
	
	unsigned long returnVal = rand() % (max - min + 1) + min;
	while (!IsPrime(returnVal))
	{
		returnVal = rand() % (max - min + 1) + min;
	}

	return returnVal;
}

//Gets N = P * Q
unsigned long GetN(unsigned long p, unsigned long q)
{
	return p*q;
}

//Gets the totient, z = (p-1) * (q-1)
unsigned long GetZ(unsigned long p, unsigned long q)
{
	return (p - 1)*(q - 1);
}

//gets a co prime: prime number in a range not divisible by a specific number (totient/z)
unsigned long GetK(unsigned long magicNumber)
{
	unsigned long min = 1;
	unsigned long max = magicNumber-1;

	unsigned long returnVal = rand() % (max - min + 1) + min;

	//co-prime must be prime, and also cannot be divisible by "magic number"
	while (!IsPrime(returnVal) || (returnVal % magicNumber == 0) )
	{
		returnVal = rand() % (max - min + 1) + min;
	}

	return returnVal;
}

//gets secret key, J, requires z & k
unsigned long GetJ(unsigned long z, unsigned long k, unsigned long iMin, unsigned long iMax)
{
	unsigned long min = iMin;
	unsigned long max = iMax;

	//return value
	unsigned long j = 0;

	do
	{
		//j = rand() % (max - min + 1) + min;
		j = GetRandomPrime(min, max);
	} while ( !( (j*k) % z != 1) );

	return j;
}

//Encryption requires K & N, with input P to produce E
unsigned long EncryptionResult(unsigned long p, unsigned long k, unsigned long n)
{
	unsigned long e= 0;

	//calculate encrypted text
	//E = p^k - ( n * ( (p^k) / n ) )
	//e = pow(p,k) - ( n * ( (pow(p,k)) / n )

	e = 
		(
		pow(p, k) - 
			(
			n * ((pow(p, k)) / n)
			)
		);


	return e;
}

//Decryption requires J & N, with input E to produce P
unsigned long DecryptionResult(unsigned long e, unsigned long j, unsigned long n)
{
	unsigned long p=0;

	//decrypt text
	//P = e^j - ( ( (e^j) / n ) * n)
	p = pow(e, j) - (((pow(e, j) / n) * n));

	return p;
}