//-------------------------------------------------------------------------------
int32u_t str2int(int8s_t *str, int32u_t radix)
{
	int32u_t result = 0,value;

	radix = 10;
	if (*str == '0') {
		str++;
		if ((*str == 'x') && isxdigit(str[1])) 
		{
			radix = 16;
			str++;
		}
		else
		{
			radix = 10;
		}
	}

	while ( isxdigit(*str) && (value = isdigit(*str)? *str-'0' : (islower(*str)? Toupper(*str) : *str)-'A'+10) < radix )
   	{
		result = result*radix + value;
		str++;
	}

	return result;
}