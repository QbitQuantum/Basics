/* Parse (scan) a number */
unsigned int parse_num(char *s, unsigned long *val, char **es, char *delim)
{
	unsigned int first = 1;
	int radix = 10;
	char c;
	unsigned long result = 0;
	int digit;

	while(*s == ' ')
		s++;

	while(*s){
		if(first && (s[0] == '0') && (_tolower(s[1]) == 'x')){
			radix = 16;
			s += 2;
		}

		first = 0;
		c = *s++;

		if(_is_hex(c) && ((digit = _from_hex(c)) < radix)){
			/* Valid digit */
			result = (result * radix) + digit;
		} else {
			if(delim != (char *)0){
				/* See if this character is one of the delimiters */
				char *dp = delim;

				while(*dp && (c != *dp))
					dp++;

				/* Found a good delimiter */
				if(*dp)
					break;
			}

			/* Malformatted number */
			return 0;
		}
	}

	*val = result;

	if(es != (char **)0){
		*es = s;
	}

	return 1;
}