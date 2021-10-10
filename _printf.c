#include "main.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
  * _printf - prints any number of args based on a format string
  * @format: the format string
  * Return: the number of characters printed
  */
int _printf(const char *format, ...)
{
	int n_char, *n_flags;
	char *buffer, *buffer_h, *curr_flags, match;
	va_list ap;

	n_char = 0;
	va_start(ap, format);

	if (format == NULL)
		return (n_char);

	buffer = malloc(sizeof(char) * 1024);
	if (buffer != NULL)
	{
		buffer_h = buffer;
		while (*format != 0)
		{
			if (*format == '%')
			{
				n_flags = malloc(sizeof(int) * 1);
				if (n_flags != NULL)
				{
					*n_flags = 0;
					match = get_format(++format, n_flags);
					curr_flags = get_flags(format, *n_flags);
				}
				switch (match)
				{
					case 'c':
						buffer_h = print_char(va_arg(ap, int), buffer_h);
						break;
					case 's':
						buffer_h = print_str(va_arg(ap, char *), buffer_h,
								'0', curr_flags);
						break;
					case 'r':
						buffer_h = print_str(va_arg(ap, char *), buffer_h,
								'r', curr_flags);
						break;
					case 'S':
						buffer_h = print_strcap(va_arg(ap, char *), buffer_h,
								curr_flags) - 1;
						break;
					case 'd': case 'i':
						buffer_h = print_int(va_arg(ap, int), buffer_h,
								curr_flags);
						break;
					case 'u':
						buffer_h = print_uint(va_arg(ap, unsigned int),
								buffer_h, curr_flags);
						break;
					case 'b':
						buffer_h = print_base(va_arg(ap, unsigned int), 2,
								'x', buffer_h, curr_flags);
						break;
					case 'o':
						buffer_h = print_base(va_arg(ap, unsigned int), 8,
								'x', buffer_h, curr_flags);
						break;
					case 'x':
						buffer_h = print_base(va_arg(ap, unsigned int), 16,
								'x', buffer_h, curr_flags);
						break;
					case 'X':
						buffer_h = print_base(va_arg(ap, unsigned int), 16,
								'X', buffer_h, curr_flags);
						break;
					case '%':
						buffer_h = memcpy(buffer_h, "%", 1);
						break;
					case 'p':
						buffer_h = print_p(va_arg(ap, size_t), buffer_h);
						break;
					case '0':
						buffer_h = memcpy(buffer_h, "%", 1);
						format--;
				}
				format += *n_flags;
				free(n_flags);
				free(curr_flags);
			}
			else
				memcpy(buffer_h, format, 1);

			buffer_h++;
			format++;
		}
	}

	*buffer_h = '\0';
	n_char = len(buffer);
	write(1, buffer, n_char);
	free(buffer);
	return (n_char);
}

/**
  * get_format - finds a matching format char and the number of flags preceding
  * @format: pointer the current format char
  * @n_flags: pointer to the number of chars
  * Return: the matching format specifier
  */
char get_format(const char *format, int *n_flags)
{
	char formats[] = "csrSdiuboxXp";
	int i, j;

	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 12; j++)
		{
			if (*(format + i) == 0)
				return ('0');
			if (*format == '%')
				return ('%');
			if (*(format + i) == formats[j])
			{
				*n_flags = i;
				return (formats[j]);
			}
		}
	}
	return ('0');
}

/**
  * get_flags - create a string of flags preceding a format char
  * @format: pointer to the format string
  * @n_flags: number of flags set from get_format()
  * Return: a string of the flags
  */
char *get_flags(const char *format, int n_flags)
{
	int i;
	char *flags;

	flags = malloc(sizeof(char) * (n_flags + 1));
	if (flags != NULL)
		for (i = 0; i < n_flags; i++)
			*(flags + i) = *(format + i);

	*(flags + i) = '\0';

	return (flags);
}
