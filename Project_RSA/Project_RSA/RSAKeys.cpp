#include "RSAKeys.h"


/*
http://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.186-4.pdf

RSA Public Key pair (N, e)
--used to verify digital signatures
--need to use Hash function during the generation of key pairs and digital signatures
--size of a key pair: length of modulus N in bits (nlen)
	nlen: 1024, 2048, 3072 bits

RSA Private Key Pair (N, d)
--used to generate dignital signatures
--need to use Hash function during the generation of key pairs and digital signatures

Public Key modulus N
--the product of two positive prime integers p and q (i.e., N = pq)


	Prime Numbers (p, q)	<--need to be kept secret
							<--need to be randomly generated using an approved random or pseudorandom number generator
							<--the (pseudo) random number is used as a prime  number generation seed
							<--Prime number generation seeds shall be kept secret or destroyed when the modulus N is computed

								// pLength: desired length of the prime p (in bits) -- like L
								// --need to be greater than 10,000, so length of 5 bits or more: [][][][][] 

								// qLength:	desired length of the prime q (in bits) -- like N
								// --need to be greater than 10,000, so length of 5 bits or more: [][][][][]

	Exponent (d)	<--need to be kept secret



	Modulus (N)		<--may be made known to anyone

	Exponent (e)	<--may be made known to anyone
					<--need to be randomly generated using an approved random or pseudorandom number generator
					<--


*/

RSAKeys::RSAKeys()
{
	// STEP 1:  GENERATE PRIME NUMBERS (p, q)

	// 1.1: GENERATE FIRST LARGE ODD NUMBER -> GENERATE PRIME -> GET PRIME NUM LENGTH
	// firstLargeOdd[2] array returns a pair of {largeOddRandNumber, randNumLength};
	unsigned ll firstLargeOdd[2];
	GenerateLargeOddNumber(firstLargeOdd); // CONVERT ODD NUMBER TO GET FIRST PRIME VIA PRIMALITY TEST
	p = GeneratePrime(firstLargeOdd[0]); // firstLargeOdd[0] is unsigned long long largeOddNumber (first prime candidate)
	// Make a getter function that counts the number of digits after getting the right prime num
	pLength = firstLargeOdd[1]; // firstLargeOdd[1] is length/number of digits of the first prime candidate
	
	// 1.2: GENERATE SECOND LARGE ODD NUMBER -> GENERATE PRIME -> GET PRIME NUM LENGTH
	// secondLargeOdd[2] array returns a pair of {largeOddRandNumber, randNumLength};
	unsigned ll secondLargeOdd[2];
	GenerateLargeOddNumber(secondLargeOdd); // CONVERT ODD NUMBER TO GET FIRST PRIME VIA PRIMALITY TEST
	q = GeneratePrime(secondLargeOdd[0]); // secondLargeOdd[0] is unsigned long long largeOddNumber (second prime candidate)
	// Make a getter function that counts the number of digits after getting the right prime num
	qLength = secondLargeOdd[1]; // secondLargeOdd[1] is length/number of digits of the second prime candidate

	// Check and redo q if it's the same as p
	if (p == q)
	{
		GenerateLargeOddNumber(secondLargeOdd); // CONVERT ODD NUMBER TO GET FIRST PRIME VIA PRIMALITY TEST
		q = secondLargeOdd[0]; // secondLargeOdd[0] is unsigned long long largeOddNumber (second prime candidate)
		qLength = secondLargeOdd[1];
		//unsigned ll secondLargeOddNum = GenerateLargeOddNumber();
		//q = GeneratePrime(secondLargeOddNum);
	}

	// STEP 2: Compute N
	N = p*q;

	// STEP 3:	Compute Euler's Totient Function

	// STEP 4: Randomly generate encryption key e
	// Public Key exponent e

}

void RSAKeys::GenerateLargeOddNumber(unsigned ll * largeOddPair)
{
	// Generate random number from 10,007 to ...
	unsigned ll randNum;
	srand(time(NULL));
	//randNum = rand() % 94723 + 10007;		// Range: 10 007 to 104 729 (5 to 6 digits) 
	randNum = rand() % 982451654 + 10007;	// Range: 10 007 to 982 451 654 (5 to 9 digits) 
	// Can change range up to higher values for more randomization
	// Higher range <-> More difficult to crack
	// unsigned long long max val: up to 18 446 744 073 709 551 615 (up to 20 digits)

	// Convert ll randNum to a char array but in reverse
	char randNumArr[256];
	int randNumLength = 0;
	while (randNum)
	{
		randNumArr[randNumLength++] = randNum % 10;
		randNum /= 10;
	}

	// Replace first digit with any number range 1 to 9 if first digit is 0
	if (randNumArr[0] == 0)
	{
		randNumArr[0] = rand() % 10 + 1; // range 1 to 9
	}

	// Check if last digit is even -> Convert to odd
	int lastDigit = randNumArr[randNumLength - 1];
	if (lastDigit % 2 == 0)
	{
		lastDigit++;
		randNumArr[randNumLength - 1] = lastDigit;
	}

	// After making necessary changes, convert char array of integer elements back to ll
	for (int i = 0; i < randNumLength; i++)
	{
		randNum = randNum * 10 + randNumArr[i];
	}
	// randNum should now be in correct format: large odd number more than 10,000

	largeOddPair[0] = randNum;
	largeOddPair[1] = randNumLength;
}

/* GENERATNG A LARGE ODD NUMBER AS A PRIME CANDIDATE
unsigned ll RSAKeys::GenerateLargeOddNumber()
{
	// Generate random number from 10,007 to ...
	unsigned ll randNum;
	srand(time(NULL));
	//randNum = rand() % 94723 + 10007;		// Range: 10 007 to 104 729 (5 to 6 digits) 
	randNum = rand() % 982451654 + 10007;	// Range: 10 007 to 982 451 654 (5 to 9 digits) 
											// Can change range up to higher values for more randomization
											// Higher range <-> More difficult to crack
											// unsigned long long max val: up to 18 446 744 073 709 551 615 (up to 20 digits)
	
	// Convert ll randNum to a char array but in reverse
	char randNumArr[256];
	int randNumLength = 0;
	while (randNum)
	{
		randNumArr[randNumLength++] = randNum % 10;
		randNum /= 10;
	}

	// Replace first digit with any number range 1 to 9 if first digit is 0
	if (randNumArr[0] == 0)
	{
		randNumArr[0] = rand() % 10 + 1; // range 1 to 9
	}

	// Check if last digit is even -> Convert to odd
	int lastDigit = randNumArr[randNumLength - 1];
	if (lastDigit % 2 == 0)
	{
		lastDigit++;
		randNumArr[randNumLength - 1] = lastDigit;
	}

	// After making necessary changes, convert char array of integer elements back to ll
	for (int i = 0; i < randNumLength; i++)
	{
		randNum = randNum * 10 + randNumArr[i];
	}
	// randNum should now be in correct format: large odd number more than 10,000

	return randNum;
}*/

unsigned ll RSAKeys::GeneratePrime(unsigned ll largeOddNum)
{
	unsigned ll primeNum = largeOddNum;
	bool isPrime = CheckPrimality(largeOddNum);
	
	if (!isPrime) // if not prime
	{
		cout << "not prime" << endl;
		primeNum = GeneratePrime(largeOddNum + 2);
	}
	return primeNum;
}

/* FERMAT PRIMALITY TESTING */
bool RSAKeys::CheckPrimality(unsigned ll randNum)
{
	int iterations = 50; // can change number of times to verify that randNum is truly a prime

	for (int i = 0; i < iterations; i++)
	{
		ll a = rand() % (randNum - 1) + 1; // Range from 1 to (randNum - 1)
		// a^(randNum - 1), mod randNum 
		if (Modulo(a, randNum - 1, randNum) != 1)
		{
			return false;
		}
	}
	return true;

}

unsigned ll RSAKeys::Modulo(ll base, ll exponent, ll mod)
{
	ll x = 1;
	ll y = base;
	while (exponent > 0)
	{
		if (exponent % 2 == 1)
		{
			x = (x * y) % mod;
		}
		y = (y * y) % mod;
		exponent = exponent / 2;
	}
	return x % mod;
}

