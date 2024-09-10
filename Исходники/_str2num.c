unsigned long long _str2num(const char *string, unsigned base, int sign)
{
	unsigned long long result = 0;
	int length = 0;
	int negative = 0;
	int count = 0;

	if (!string)
	{
		errno = ERR_NULLPARAMETER;
		return (0);
	}

	// Get the length of the string
	length = strlen(string);

	if (sign && (string[0] == '-'))
	{
		negative = 1;
		count += 1;
	}

	// Do a loop to iteratively add to the value of 'result'.
	for ( ; count < length; count ++)
	{
		switch (base)
		{
			case 10:
				if (!isdigit(string[count]))
				{
					errno = ERR_INVALID;
					goto out;
				}
				result *= base;
				result += (string[count] - '0');
				break;

			case 16:
				if (!isxdigit(string[count]))
				{
					errno = ERR_INVALID;
					goto out;
				}
				result *= base;
				if ((string[count] >= '0') && (string[count] <= '9'))
					result += (string[count] - '0');
				else if ((string[count] >= 'a') && (string[count] <= 'f'))
					result += ((string[count] - 'a') + 10);
				else
					result += ((string[count] - 'A') + 10);
				break;

			default:
				errno = ERR_NOTIMPLEMENTED;
				goto out;
		}
	}

out:
	if (negative)
		result = ((long long) result * -1);

	return (result);
}