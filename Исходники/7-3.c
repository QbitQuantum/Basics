int doprint(char *fmt, va_list ap)
{
	int ret = 0;
	int code;
	int value = 0;
	char *p = NULL;
	char string[24] = { 0 };

	for (; ; ) {
		while (((code = *fmt) != '\0') && (code != '%')) {
			PUTC(code);
			fmt++;
			ret++;
		}
		if (code == '\0')
			goto out;

		switch (code = *++fmt) {
			case 'd':
				value = va_arg(ap, int);
				p = itoa(string, value, 24);
				break;
			case 'o':
				value = va_arg(ap, int);
				p = otoa(string, value, 24);
				break;
			case 'x':
				value = va_arg(ap, int);
				p = xtoa(string, value, 24);
				break;
			case 's':
				p = va_arg(ap, char *);
				break;
			case 'c':
				value = va_arg(ap, int);
				string[0] = (char )value;
				string[1] = '\0';
				p = string;
				break;
			default:
				p = NULL;
				break;
		}
		while (p && (*p != '\0')) {
			PUTC(*p);
			p++, ret++;
		}
		fmt++;
	}

out:
	return ret;
}