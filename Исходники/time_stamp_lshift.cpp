emstream& operator<< (emstream& serial, time_stamp& stamp)
{
	char dig_buffer[7];						// Holds digits we compute
	ldiv_t div_result;						// Holds results of long integer division

	// First write the seconds in the time stamp, then a decimal
	serial << stamp.get_seconds ();
	serial.putchar ('.');

	// Now get the microseconds; these will be written with leading zeros as needed
	div_result.quot = stamp.get_microsec ();
	for (int8_t index = 5; index >= 0; index--)
	{
		div_result = ldiv (div_result.quot, 10);
		dig_buffer[index] = div_result.rem + '0';
	}

	// The last item in the string must be a '\0' null character
	dig_buffer[6] = '\0';

	// Write the buffer, which now contains microsecond digits
	serial << dig_buffer;

	return (serial);
}