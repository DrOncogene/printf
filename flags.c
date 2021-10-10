#include "main.h"
#include <stddef.h>
#include <string.h>

/**
  * render_flags - renders the output of flags
  * @flags: string containing the flags
  * @buff: the buffer to save the output in
  * @base: base of the num being printed
  * @num: 0 if num is pos, -1 if neg, 0 if not a number
  * @str: 1 if a string, 0 otherwise
  * Return: pointer to the last filled location in buff
  */
char *render_flags(char *flags, char *buff, int base, int num, int str)
{
	while (*flags != 0)
	{
		switch (*flags)
		{
			case '+':
				if (num != -1 && str == 0)
					buff = plus_flag(buff);
				else
					buff--;
				break;
			case ' ':
				if (num != -1 && str == 0)
					buff = invisible_plus(buff);
				break;
			case '-':
				break;
			case '0':
				break;
			case '#':
				if (base == 8 || base == 16)
					buff = hash_flag(buff);
				else
					buff--;
				break;
			default:
				break;
		}
		flags++;
		buff++;
	}
	return (buff);
}

/**
  * plus_flag - renders the + flag
  * @buff: buffer
  * Return: pointer to the last occupied location
  */
char *plus_flag(char *buff)
{
	return (memcpy(buff, "+", 1));
}

/**
  * invisible_plus - renders the space flag
  * @buff: buffer
  * Return: the filled location
  */
char *invisible_plus(char *buff)
{
	return (memcpy(buff, " ", 1));
}

/**
  * hash_flag - renders the # flag
  * @buff: the buffer
  * Return: the filled location
  */
char *hash_flag(char *buff)
{
	return ((char *)memcpy(buff, "0x", 2) + 2);
}
