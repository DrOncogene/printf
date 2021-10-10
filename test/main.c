#include "../main.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

int main(void)
{
	int len1, len2, len3, len4;

	len1 = _printf("%+d + % i = %d\n", 5, 5, (55 + 5));
	len2 = _printf("%d + %i = %d\n", -605, 434, (-605 + 434));
	len3 = _printf("98(2): %#b, 98(8): %o, %S\n", 98, 98, "Best\n\aSchool");
	_printf("len1: %i, len2: %p, len3: %u\n", len1, &len2, -10);
	printf("Len: %u 12: %#x 250(8): %#x %+5d %k\n", -10, 12, 250, len3);
	len4 = _printf("Pointer: %p, %p, %r %z\n", (void *)0x6fff5100b608, NULL, "Nasir");
	_printf("%d\n", len4);

	return (0);
}
