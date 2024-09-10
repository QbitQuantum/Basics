int fprintf(FILE* f, const char* fmt, ...){
	va_list params;
	va_start(params, fmt);
	
	int arg = 0;
	while(*fmt != '\0'){
		if(*fmt == '%'){
			fmt++;
			char op = *fmt;

			switch(op){
				case 'd':
				case 'i':
					print_decimal(f, va_arg(params, int));
					break;

				case 'x':
				case 'X':
					print_hex(f, va_arg(params, int));
					break;

				case 'c':
					fputchar(f, va_arg(params, int));
					break;

				case 's':
					fprint(f, va_arg(params, char*));
					break;

				default:
					return -1;
			}
		}

		else
			fputchar(f, *fmt);

		fmt++;
	}

	return 0;
}