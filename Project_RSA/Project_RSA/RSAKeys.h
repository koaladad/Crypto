#ifndef RSAKEYS_H
#define RSAKEYS_H
#include <iostream>
using namespace std;

class RSAKeys
{
public:
	RSAKeys(); // default constructor; set private data members to default values
	void GenerateProbablePrimes();
	bool ValidateProbablePrimes();

private:
	int p, q; // randomly? generated prime numbers greater than 10 000
	int e;	// randomly generated encrypt key greater than 10 000
			// Public key -- publish
	int N;	// N = p*q; Public key -- publish

};

#endif