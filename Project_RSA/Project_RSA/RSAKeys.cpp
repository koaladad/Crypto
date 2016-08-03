#include "RSAKeys.h"

RSAKeys::RSAKeys()
{
	// GeneratePrimeKeys();
	//p = 10007;
	//q = 10009;


	// Compute N
	N = p*q;

	// Compute Euler's Totient Function

	// Randomly generate encryption key e
	//e = 10000;

}

void RSAKeys::GeneratePrimeKeys()
{
	// http://crypto.stackexchange.com/questions/71/how-can-i-generate-large-prime-numbers-for-rsa

}
