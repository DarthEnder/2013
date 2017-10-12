#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned __int128 m_number;
int m_Digits;

int Test4Numbers(char *);

__int128 atoi128(const char *s)
{
	while (*s == ' ' || *s == '\t' || *s == '\n' || *s == '+')
		++s;
	int sign = 1;
	if (*s == '-')
	{
		++s;
		sign = -1;
	}
	size_t digits = 0;
	while (s[digits] >= '0' && s[digits] <= '9')
		++digits;
	char scratch[digits];
	for (size_t i = 0; i < digits; ++i)
		scratch[i] = s[i] - '0';
	size_t scanstart = 0;

	__int128 result = 0;
	__int128 mask = 1;
	while (scanstart < digits)
	{
		if (scratch[digits - 1] & 1)
			result |= mask;
		mask <<= 1;
		for (size_t i = digits - 1; i > scanstart; --i)
		{
			scratch[i] >>= 1;
			if (scratch[i - 1] & 1)
				scratch[i] |= 8;
		}
		scratch[scanstart] >>= 1;
		while (scanstart < digits && !scratch[scanstart])
			++scanstart;
		for (size_t i = scanstart; i < digits; ++i)
		{
			if (scratch[i] > 7)
				scratch[i] -= 3;
		}
	}

	return result * sign;
}

void uint128_to_str_iter(__int128 n, char *out, int firstiter)
{
	static int offset = 0;
	if (firstiter)
	{
		offset = 0;
	}
	if (n == 0)
	{
		return;
	}
	uint128_to_str_iter(n / 10, out, 0);
	out[offset++] = n % 10 + 0x30;
}

char *uint128_to_str(__int128 n)
{
	char *out = calloc(sizeof(char), 40);
	uint128_to_str_iter(n, out, 1);
	return out;
}

void GetNumberOfDigits()
{
	printf("How many digits do you want:");
	scanf("%i", &m_Digits);
	printf("You chose %i digits :)\n", m_Digits);
}

void DoMagic()
{
	char m_string[255];
	char m_char[10];
	int i, j;

	for (i = 0; i < 9; i++)
	{
		strcpy(m_string, "");

		for (j = 0; j < m_Digits; j++)
		{
			sprintf(m_char, "%i", (i + 1));
			strcat(m_string, m_char);

			if (Test4Numbers(m_string) == 0)
			{
				printf("Number found: %s\n", uint128_to_str(m_number));
				return;
			}
		}
	}
	printf("No numbers found :(\n");
}

int Test4Numbers(char *m_numberstring)
{
	m_number = atoi128(m_numberstring);

	printf("%s/2013 -> %s\n", uint128_to_str(m_number), uint128_to_str(m_number % 2013));

	if ((m_number % 2013) == 0)
		return 0;

	return 1;
}

int main()
{
	GetNumberOfDigits();
	DoMagic();

	return 0;
}
