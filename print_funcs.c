#include "main.h"
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>

/**
  * print_char - copies a char to a buffer
  * @c: the char
  * @buff: the buffer
  * Return: number of char printed = 1
  */
char *print_char(char c, char *buff)
{
	return (memcpy(buff, &c, 1));
}

/**
  * print_str - copies a string to a buffer
  * @s: the string
  * @buff: the buffer
  * @flag: 'r' to print the string in reverse
  * @flags: associated printf flags
  * Return: the number of chars written
  */
char *print_str(char *s, char *buff, char flag, char *flags)
{
	int i;

	buff = render_flags(flags, buff, 0);
	if (s == NULL)
	{
		memcpy(buff, "(null)", 6);
		return (buff + 5);
	}
	if (*s == 0)
		return (buff);
	if (flag == 'r')
	{
		buff += (len(s) - 1);
		for (i = 0; i < len(s); i++)
		{
			memcpy(buff, (s + i), 1);
			buff--;
		}
		buff++;
	}
	else
		memcpy(buff, s, len(s));
	return (buff + len(s) - 1);
}

/**
  * print_strcap - prints a string, with non-printables as \x+hex value
  * @s: string
  * @buff: buffer save to
  * @flags: associated flags
  * Return: pointer to buffer
  */
char *print_strcap(char *s, char *buff, char *flags)
{
	int i;

	if (s == NULL || *s == 0)
		return (buff + 1);
	for (i = 0; i < len(s); i++)
	{
		if (*(s + i) > 0 && (*(s + i) < 32 || *(s + i) >= 127))
		{
			memcpy(buff, "\\x", 2);
			if (*(s + i) >= 1 && *(s + i) <= 15)
			{
				memcpy(buff + 2, "0", 1);
				buff++;
			}
			buff = print_base(*(s + i), 16, 'X', (buff + 2), flags);
		}
		else
			memcpy(buff, s + i, 1);
		buff++;
	}

	return (buff);
}

/**
  * print_int - copies an integer to a buffer
  * @num: the integer
  * @buff: the buffer
  * @flags: associated flags
  * Return: number of digits written
  */
char *print_int(int num, char *buff, char *flags)
{
	unsigned int len_s;

	buff = render_flags(flags, buff, 10);

	if (num < 0)
		len_s = len_int(num * -1) + 1;
	else
		len_s = len_int(num);

	return (save_int(buff, num, len_s));
}

/**
  * print_uint - prints unsigned ints to a buffer
  * @num: the number
  * @buff: the buffer for saving
  * Return: pointer to the start of the strings
  */
char *print_uint(int num, char *buff)
{
	unsigned int len_s, u_num;

	if (num < 0)
	{
		u_num = UINT_MAX + 1 + num;
		len_s = len_int(u_num);
		return (save_uint(buff, u_num, len_s));
	}
	else
		len_s = len_int(num);

	return (save_int(buff, num, len_s));
}

/**
  * print_base - converts a decimal to a base and save in a buffer
  * @num: the integer passed
  * @base: the base to be converted to
  * @f: a flag to specify upper or lower case letter in base 16 (x or X)
  * @buff: the buffer
  * @flags: associated flags(usually '#')
  * Return: number of digits printed
  */
char *print_base(unsigned long int num, unsigned int base, char f,
		char *buff, char *flags)
{
	char Char_repr[] = "0123456789ABCDEF";
	char Char_repr_lower[] = "0123456789abcdef";
	char buffer[50];
	char *ptr;

	buffer[0] = '\0';
	ptr = &buffer[0];
	if (*flags != 0)
		buff = render_flags(flags, buff, base);

	do {
		if (f == 'X')
			*++ptr = Char_repr[num % base];
		else
			*++ptr = Char_repr_lower[num % base];
		num /= base;
	} while (num != 0);

	while (*ptr != 0)
	{
		buff = memcpy(buff, ptr, 1);
		ptr--;
		buff++;
	}

	return (--buff);
}

/**
  * print_p - prints a pointer to buff
  * @p: the pointer
  * @buff: the buffer
  * Return: pointer to buffer
  */
char *print_p(size_t p, char *buff)
{
	if (!p)
	{
		memcpy(buff, "(nil)", 5);
		return (buff + 4);
	}
	memcpy(buff, "0x", 2);
	buff = print_base(p, 16, 'x', (buff + 2), "");
	return (buff);
}
