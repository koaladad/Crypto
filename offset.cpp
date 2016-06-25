#include "offset.h"

Offset::Offset(char buffer[])
{
	char a = buffer[0];
	char b = buffer[1];

	if (isdigit(a) && isdigit(b))
	{
		//2-digit number
		char twodigit[2];
		twodigit[0] = a;
		twodigit[1] = b;
		int number = atoi(twodigit);

		SetOffset(number);
	}
	else if (isdigit(a) && !isdigit(b))
	{
		//1-digit number
		char onedigit[1];
		onedigit[0] = a;
		int number = atoi(onedigit);

		SetOffset(number);
	}
	else if (isalpha(a))
	{
		//alphanumericoffset a-z OR A-Z
		SetOffset(a);
	}
	else
	{
		m_offset = 0;
	}
}

int Offset::GetOffset()
{
	return m_offset;
}

void Offset::SetOffset(char c)
{
	//if upper case, change to lower case
	if (isupper(c)) c = tolower(c);

	int num = c-97;
	
	SetOffset(num);
}

void Offset::SetOffset(int num)
{
	num = num % 26;
	m_offset = num;
}
