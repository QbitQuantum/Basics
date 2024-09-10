int DebugPrintf (const char* str, ...) {
	
	if(!str)
		return 0;
	va_list		args;
	size_t i;
	va_start (args, str);
	for (i=0; i<strlen(str);i++) {
		switch (str[i]) {
			case '%':
				switch (str[i+1]) {
					case 'c': {
						char c = va_arg (args, char);
						DebugPutc (c);
						i++;		
						break;
					}
					case 's': {
						int c = (int) va_arg (args, char);
						char str[32]={0};
						itoa_s (c, 16, str);
						DebugPuts (str);
						i++;		
						break;
					}

					case 'd':

					case 'i': {

						int c = va_arg (args, int);

						char str[32]={0};

						itoa_s (c, 10, str);

						DebugPuts (str);

						i++;		

						break;

					}




					case 'X':

					case 'x': {

						int c = va_arg (args, int);

						char str[32]={0};

						itoa_s (c,16,str);

						DebugPuts (str);

						i++;		

						break;

					}



					default:

						va_end (args);

						return 1;

				}



				break;



			default:

				DebugPutc (str[i]);

				break;

		}



	}
	va_end (args);
}