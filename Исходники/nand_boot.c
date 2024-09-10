void puts(const char *str)
{
	while (*str)
		putc(*str++);
}