#include "main.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/**
  * _printf - prints any number of args based on a format string
  * @format: the format string
  * Return: the number of characters printed
  */
int _printf(const char *format, ...)
{
	int n_char;
	char *buffer, *buffer_h;
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
				format++;
				switch (*format)
				{
					case 'c':
						buffer_h = print_char(va_arg(ap, int), buffer_h);
						break;
					case 's':
						buffer_h = print_str(va_arg(ap, char *), buffer_h, '0');
						break;
					case 'r':
						buffer_h = print_str(va_arg(ap, char *), buffer_h, 'r');
						break;
					case 'S':
						buffer_h = print_strcap(va_arg(ap, char *), buffer_h) - 1;
						break;
					case 'd': case 'i':
						buffer_h = print_int(va_arg(ap, int), buffer_h);
						break;
					case 'u':
						buffer_h = print_uint(va_arg(ap, unsigned int), buffer_h);
						break;
					case 'b':
						buffer_h += print_base(va_arg(ap, unsigned int), 2,
								'0', buffer_h, 0) - 1;
						break;
					case 'o':
						buffer_h += print_base(va_arg(ap, unsigned int), 8,
								'0', buffer_h, 0) - 1;
						break;
					case 'x':
						buffer_h += print_base(va_arg(ap, unsigned int), 16,
								'x', buffer_h, 0) - 1;
						break;
					case 'X':
						buffer_h += print_base(va_arg(ap, unsigned int), 16,
								'X', buffer_h, 0) - 1;
						break;
					case '%':
						buffer_h = memcpy(buffer_h, "%", 1);
						break;
					case 'p':
						buffer_h = print_p(va_arg(ap, size_t), buffer_h);
						break;
					default:
						buffer_h = memcpy(buffer_h, "%", 1);
						format--;
				}
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
