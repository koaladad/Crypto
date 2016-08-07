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


bool IsPrime(long long int num);
long long int GetRandomPrime(long long int min, long long int max);
long long int GetZ(long long int p, long long int q);
long long int GetK(long long int magicNumber);
long long int GetN(long long int p, long long int q);
long long int GetJ(long long int z, long long int k, unsigned long iMin, unsigned long iMax);
long long int EncryptionResult(long long int p, long long int k, long long int n);
long long int DecryptionResult(long long int e, long long int j, long long int n);
long long int power(long long int a, long long int b, long long int MOD);
long long int modulo(long long int n, long long int p);
long long int modInverse(long long int n, long long int p);

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
	unsigned long max = 50000;
	//initial vars 
	long long int p = 43;
	long long int q = 47;
	long long int n = 2021;
	long long int z = 1932; //totient
	long long int k = 307; //coprime to z/totient function
	long long int j = 1567; //secret key
	long long int plaintext = 0;
	long long int encryptedtext = 0;

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
				////unsigned long plaintext;
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

				long long int param1 = plaintext;
				long long int param2 = k;
				long long int param3 = n;
				//long long int param1 = 14;
				//long long int param2 = 7;
				//long long int param3 = 33;
				encryptedtext = EncryptionResult(param1,param2,param3);
				std::cout << endl << "*** The resulting encrypted text is ***: " << encryptedtext << std::endl;

			}



		}
		else if (choice[0] == 'C')
		{
			cout << "-Decryption-" << endl
				<< "Please enter: " << endl;

			std::string line;
			//unsigned long encryptedtext;
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
			
			long long int param1 = encryptedtext;
			long long int param2 = j;
			long long int param3 = n;
			plaintext = DecryptionResult(param1,param2,param3);
			std::cout << endl << "*** The resulting decrypted text is ***: " << plaintext << std::endl;

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


bool IsPrime(long long int num)
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
	for (unsigned long i = 3; i < sqrt(num)+1; i+=2)
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
long long int GetRandomPrime(long long int iMin, long long int iMax)
{
	long long int min = iMin;
	long long int max = iMax;
	
	long long int returnVal = rand() % (max - min + 1) + min;
	while (!IsPrime(returnVal))
	{
		returnVal = rand() % (max - min + 1) + min;
	}

	return returnVal;
}

//Gets N = P * Q
long long int GetN(long long int p, long long int q)
{
	return p*q;
}

//Gets the totient, z = (p-1) * (q-1)
long long int GetZ(long long int p, long long int q)
{
	return (p - 1)*(q - 1);
}

//gets a co prime: prime number in a range not divisible by a specific number (totient/z)
long long int GetK(long long int magicNumber)
{
	long long int min = 1;
	long long int max = magicNumber-1;

	long long int returnVal = GetRandomPrime(min, max);

	//co-prime must be prime, and also cannot be divisible by "magic number"
	while ( returnVal % magicNumber == 0 ) //if it is keep going
	{
		returnVal = GetRandomPrime(min, max);
	}

	return returnVal;
}

//gets secret key, J, requires z & k
long long int GetJ(long long int z, long long int k, unsigned long iMin, unsigned long iMax)
{
	unsigned long min = iMin;
	unsigned long max = iMax;

	long long int j = 0;
	//calculate secret key using euclidean algorithm and back substitution
	j = modInverse(k,z);

	return j;
}

//Encryption requires K & N, with input P to produce E
long long int EncryptionResult(long long int p, long long int k, long long int n)
{
	//calculate encrypted text
	//E = p^k - ( n * ( (p^k) / n ) )
	//e = pow(p,k) - ( n * ( (pow(p,k)) / n )

	long long int e = power(p,k,n);

	return e;
}

//Decryption requires J & N, with input E to produce P
long long int DecryptionResult(long long int e, long long int j, long long int n)
{
	//decrypt text
	//P = e^j - ( ( (e^j) / n ) * n)
	//p = power(e, j,n) - (((power(e, j) / n) * n));
	long long int p = power(e, j, n);

	return p;
}

//returns the value modulo
long long int power(long long int a, long long int b, long long int MOD)
{
	long long int ans = 1;

	while (b)
	{
		if (b & 1) ans = (ans*a) % MOD;
		a = (a*a) % MOD;
		b = b / 2;
	}
	return ans;
}

long long int modulo(long long int n, long long int p)
{
	long long int r = n%p;
	if (((p > 0) && (r < 0)) || ((p < 0) && (r > 0)))
		r += p;
	return r;
}

//Finds modular inverse
long long int modInverse(long long int k, long long int z) {
	k = modulo(k, z);
	for (int x = 1; x < z; x++) {
		if (modulo(k*x, z) == 1) return x;
	}
	return 0;
}