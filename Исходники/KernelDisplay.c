int kernelPrintf (const char* str, ...) {

	if(!str)
		return 0;

	va_list		args;
	va_start (args, str);

	size_t i=0;
	for (i=0; i<strlen(str);i++) {

		switch (str[i]) {

			case '%':

				switch (str[i+1]) {

					/*** characters ***/
					case 'c': {
						char c =(char) va_arg (args, int);
						kernelPutc (c);
						i++;		// go to next character
						break;
					}

					/*** address of ***/
					case 's': {
						int c = (int)  va_arg (args, char);//(int&) FIXME
						char str[32]={0};
						itoa_s (c, 16, str);
						kernelPuts (str);
						i++;		// go to next character
						break;
					}

					/*** integers ***/
					case 'd':
					case 'i': {
						int c = va_arg (args, int);
						char str[32]={0};
						itoa_s (c, 10, str);
						kernelPuts (str);
						i++;		// go to next character
						break;
					}

					/*** display in hex ***/
					case 'X':
					case 'x': {
						int c = va_arg (args, int);
						char str[32]={0};
						itoa_s (c,16,str);
						kernelPuts (str);
						i++;		// go to next character
						break;
					}

					default:
						va_end (args);
						return 1;
				}

				break;

			default:
				kernelPutc (str[i]);
				break;
		}

	}

	va_end (args);
	return i;
}