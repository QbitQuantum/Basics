char *itoa(unsigned n)
{
	int sign = 0;
	int i = -1;
	char *p = NULL;
	p = malloc(CHAR_BUF);

	if ((sign = n) < 0) {
		p[0] = '-';
		sign = -1;
		i = 0;
		n = -n;
	}

	do {
		p[++i] = ITOA(n%10);
	} while (n = n/10);
	p[++i] = '\0';

	if (sign == -1) {
		reverse(p, 1, i-1);
		return p;
	} 
	reverse(p, 0, i-1);

	return p;
}