#include <iostream>
#include <Windows.h>
#include "RSAKeys.h"
using namespace std;

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


