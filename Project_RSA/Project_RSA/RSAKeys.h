#ifndef RSAKEYS_H
#define RSAKEYS_H
#define ll long long
#include <iostream>
#include <ctime>
#include <cstring>
#include <cstdlib>
//#include <boost/array.hpp>
using namespace std;

class RSAKeys
{
public:
	RSAKeys(); // default constructor; set private data members to default values
	//unsigned ll GenerateLargeOddNumber();
	void GenerateLargeOddNumber(unsigned ll * largeOddPair);
	unsigned ll GeneratePrime(unsigned ll largeOddNum); 

	
	bool CheckPrimality(unsigned ll randNum);
	unsigned ll Modulo(ll base, ll exponent, ll mod);

private:
	unsigned ll p, q; // Randomly generated prime numbers greater than 10 000
	int pLength, qLength; // Length (number of digits) of primes p and q respectively

	int e;	// Randomly generated encrypt key greater than 10 000
			// Public key -- publish
	unsigned ll N;	// Public key -- publish

};

#endif