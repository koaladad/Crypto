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
	// Step 1: A.1.1.2 Generation of the Probable Primes p and q Using an Approved Hash Function 
	// GenerateProbablePrimes();


	// Compute N
	N = p*q;

	// Compute Euler's Totient Function

	// Randomly generate encryption key e
	// Public Key exponent e


}

/*
	Step 1: A.1.1.2 Generation of the Probable Primes p and q Using an Approved Hash Function 
*/
void RSAKeys::GenerateProbablePrimes()
{
	// http://crypto.stackexchange.com/questions/71/how-can-i-generate-large-prime-numbers-for-rsa

	// INPUT
	// pLength: desired length of the prime p (in bits)
	// --need to be greater than 10,000, so length of 5 bits or more: [][][][][] 

	// qLength:	desired length of the prime q (in bits) 
	// --need to be greater than 10,000, so length of 5 bits or more: [][][][][]

	// seedlen: desired length of the domain parameter seed
	// --need to be greater than or equal to qLength, so length of 5 bits or more: [][][][][]
	// seedlen = len (domain_parameter_seed); 
					// domain_parameter_seed: an arbitrary seed that was used to generate p and q
					// --could be anything, e.g., a user’s favorite number or a random or pseudorando number output by a random number generator(see SP 800 - 90)
					// --determines a sequence of candidates for p and q in the required intervals that are then tested for primality using a probabilistic primality test(see Appendix C.3)
	
	// Prompt user for desired bit length for primes p and q (5 or more)
	int pLength = 5; 
	int qLength = 5;



	// OUTPUT
	// bool status: true if valid; false if invalid
	// --in main caller, if true is returned, get values of p and q
	// --				 if false is returned, assign p = q = 0;

	// p, q: generated primes p and q

	// domain_parameter_seed: seed used to generate p and q (optional)

	// counter: count value determined during generation
}

/*
	Step 2: Validation of the Probable Primes p and q that were Generated Using an Approved Hash Function
*/
bool RSAKeys::ValidateProbablePrimes()
{

	return true;
}