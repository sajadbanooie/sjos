#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void print(const char* data, size_t data_length)
{
	for ( size_t i = 0; i < data_length; i++ )
		putchar((int) ((const unsigned char*) data)[i]);
}
static void print_int(unsigned long a){
	if (a / 10 != 0)
		print_int(a / 10);
	putchar((char) ('0' + (a % 10)));
}
static void print_hex(unsigned long a){
	if (a / 16 != 0)
		print_hex(a / 16);
	if (a % 16 < 10)
		putchar((char) ('0' + (a % 16)));
	else 
		putchar((char) ('A' + (a % 16) - 10));
}
int printf(const char* restrict format, ...)
{
	va_list parameters;
	va_start(parameters, format);

	int written = 0;
	size_t amount;
	bool rejected_bad_specifier = false;

	while ( *format != '\0' )
	{
		if ( *format != '%' )
		{
		print_c:
			amount = 1;
			while ( format[amount] && format[amount] != '%' )
				amount++;
			print(format, amount);
			format += amount;
			written += amount;
			continue;
		}

		const char* format_begun_at = format;

		if ( *(++format) == '%' )
			goto print_c;

		if ( rejected_bad_specifier )
		{
		incomprehensible_conversion:
			rejected_bad_specifier = true;
			format = format_begun_at;
			goto print_c;
		}

		if ( *format == 'c' )
		{
			format++;
			char c = (char) va_arg(parameters, int /* char promotes to int */);
			print(&c, sizeof(c));
		}
		else if ( *format == 'd' )
		{
			format++;
			print_int(va_arg(parameters, unsigned int));
		}
		else if ( *format == 'X' )
		{
			format++;
			print("0x",2);
			print_hex(va_arg(parameters, unsigned int));
		}
		else if ( *format == 's' )
		{
			format++;
			const char* s = va_arg(parameters, const char*);
			print(s, strlen(s));
		}
		else
		{
			goto incomprehensible_conversion;
		}
	}

	va_end(parameters);

	return written;
}
