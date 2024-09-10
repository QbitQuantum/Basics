uint16 str_to_hex_uint16(uint8 *str)
{
	uint8 high_byte_high_4bits, high_byte_low_4bits, low_byte_high_4bits, low_byte_low_4bits;

	if(IsDigit(*str))
	{
		high_byte_high_4bits = *str - '0';
	}
	else if(IsLower(*str))
	{
		high_byte_high_4bits = *str - 'a' + 10;
	}
	else // upper character
	{
		high_byte_high_4bits = *str - 'A' + 10;
	}

	str++;

	if(IsDigit(*str))
	{
		high_byte_low_4bits = *str - '0';
	}
	else if(IsLower(*str))
	{
		high_byte_low_4bits = *str - 'a' + 10;
	}
	else // upper character
	{
		high_byte_low_4bits = *str - 'A' + 10;
	}

	str++;

	if(IsDigit(*str))
	{
		low_byte_high_4bits = *str - '0';
	}
	else if(IsLower(*str))
	{
		low_byte_high_4bits = *str - 'a' + 10;
	}
	else // upper character
	{
		low_byte_high_4bits = *str - 'A' + 10;
	}

	str++;

	if(IsDigit(*str))
	{
		low_byte_low_4bits = *str - '0';
	}
	else if(IsLower(*str))
	{
		low_byte_low_4bits = *str - 'a' + 10;
	}
	else // upper character
	{
		low_byte_low_4bits = *str - 'A' + 10;
	}

	return 	(((uint16)high_byte_high_4bits << 12) | ((uint16)high_byte_low_4bits << 8) | (low_byte_high_4bits << 4) | low_byte_low_4bits);
}