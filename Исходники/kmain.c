	void DEBUG_printf(const char* Str, ...)
	{
		va_list ap;
		va_start(ap, Str);
		while(*Str) {
			if(*Str == '%') {
				*Str++;
				switch(*Str) {
					/*** characters ***/
					case 'c': {
						const char c = (const char) va_arg (ap, const char);
						DEBUG_putch(c);
						*Str++;
						break;
					}
					/*** integers ***/
					case 'd':
					case 'i':
					{
						uint32_t c = va_arg (ap, uint32_t);
						uint8_t s[32]={0};
						itoa_s (c, 10, s);
						DEBUG_print((const char*) s);
						*Str++;		// go to next character
						break;
					}
					/*** display in hex ***/
					case 'X':
					case 'x':
					{
						uint32_t c = va_arg (ap, uint32_t);
						uint8_t s[32]={0};
						itoa_s (c,16,s);
						DEBUG_print((const char*) s);
						*Str++;		// go to next character
						break;
					}
					/*** strings ***/
					case 's':
					{
						const char *s = va_arg (ap, const char*);
						DEBUG_print((const char*) s);
						*Str++;		// go to next character
						break;
					}
					case '%':
					{
						DEBUG_putch('%');
						*Str++;
						break;
					}
				}
			} else {