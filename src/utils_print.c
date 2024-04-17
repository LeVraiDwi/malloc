#include "ft_malloc_include.h"

void writeStr(char str[200]) {
    if (!str)
        return;
    write(1, str, ft_strlen(str));
}

unsigned int		sizeOfNum(unsigned long int n)
{
	int l;

	l = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		l++;
	}
	return (l);
}

void    printUint(unsigned long int n)
{
	unsigned long int	l;
	char			str[200];

	l = sizeOfNum(n);
    if (l >= 200) {
        writeStr("To Large to be print\n");
	}
	str[l] = '\0';
	str[l - 1] = ((n % 10) + '0');
	n = n / 10;
    l = l - 2;
	while (n)
	{
		str[l--] = (n % 10) + '0';
		n = n / 10;
	}
	writeStr(str);
	return;
}

unsigned long int	sizeHexa(unsigned long int n)
{
	int	l;

	l = 1;
	while ((n / 16) != 0)
	{
		n = n / 16;
		l++;
	}
	return (l);
}

void    WriteHexa(unsigned long int n, int precision)
{
	int		l;
	int		size;
	char	str[200];
	char	*hexa;

	hexa = "0123456789ABCDEF";

	l = sizeHexa(n);
	size = l;
    if (l >= 200) {
        writeStr("To Large to be print\n");
	}
	str[l] = 0;
    str[l - 1] = hexa[n % 16];
	n = n / 16;
    l = l - 2;
    while(n) {
        str[l--] = hexa[n % 16];
	    n = n / 16;
    }

	if (precision && size < precision) {
		str[precision--] = '\0';
		while(precision >= size) {
			str[precision--] = '0';
		}
	}
	writeStr(str);
	return;
}