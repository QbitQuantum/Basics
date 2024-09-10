int cli_parse_two_numbers(char *qual_name, const char delimiter, uint4 *first_num, uint4 *second_num)
{ /* Parse two unsigned base 10 numbers separated by the given delimiter. Eg. -LOG_INTERVAL=10,20 (on VMS, -LOG_INTERVAL="10,20").
   * Both Unix and VMS accept the qualifier as a string. NOTE: On VMS, such qualifiers are quoted strings.
   * Both numbers are optional (eg. -LOG_INTERVAL=10, or -LOG_INTERVAL=",20", or -LOG_INTERVAL=,).
   * Return values:
   * 		     CLI_2NUM_FIRST_SPECIFIED  (binary 10), first number specified, second not
   * 		     CLI_2NUM_SECOND_SPECIFIED (binary 01), first number not specified, second is
   * 		     CLI_2NUM_BOTH_SPECIFIED   (binary 11) (CLI_2NUM_FIRST_SPECIFIED | CLI_2NUM_SECOND_SPECIFIED), both specified
   * 		     0 (binary 00), error in parsing either number
   */
	char		*first_num_str, *second_num_str, *two_num_str_top, *num_endptr;
	char		two_num_qual_str[128];
	unsigned short	two_num_qual_len;
	uint4		num;
	int		retval = 0;

	two_num_qual_len = sizeof(two_num_qual_str);
	if (!cli_get_str(qual_name, two_num_qual_str, &two_num_qual_len))
	{
		util_out_print("Error parsing !AZ qualifier", TRUE, qual_name);
		return 0;
	}
#ifdef VMS
	/* DCL does not strip quotes included in the command line. However, the DEFAULT value (see mupip_cmd.cld) is stripped
	 * of quotes. */
	if ('"' == two_num_qual_str[0])
	{
		assert('"' == two_num_qual_str[two_num_qual_len - 1]); /* end quote should exist */
		first_num_str = &two_num_qual_str[1]; /* Skip begin quote */
		two_num_qual_str[two_num_qual_len - 1] = '\0'; /* Zap end quote */
		two_num_qual_len -= 2; /* Quotes gone */
	} else
#endif
		first_num_str = two_num_qual_str;
	for (second_num_str = first_num_str, two_num_str_top = first_num_str + two_num_qual_len;
		second_num_str < two_num_str_top && delimiter != *second_num_str;
		second_num_str++)
		;
	if (delimiter == *second_num_str)
		*second_num_str++ = '\0';
	if (*first_num_str != '\0') /* VMS issues EINVAL if strtoul is passed null string */
	{
		errno = 0;
		num = (uint4)STRTOUL(first_num_str, &num_endptr, 10);
		if ((0 == num && (0 != errno || (num_endptr == first_num_str && *first_num_str != '\0'))) ||
		    (0 != errno && GTM64_ONLY(UINT_MAX == num) NON_GTM64_ONLY(ULONG_MAX == num)))
		{
			util_out_print("Error parsing or invalid parameter for !AZ", TRUE, qual_name);
			return 0;
		}
		*first_num = num;
		retval |= CLI_2NUM_FIRST_SPECIFIED;
	} /* else, first number not specified */
	if (second_num_str < two_num_str_top && *second_num_str != '\0')
	{
		errno = 0;
		num = (uint4)STRTOUL(second_num_str, &num_endptr, 10);
		if ((0 == num && (0 != errno || (num_endptr == second_num_str && *second_num_str != '\0'))) ||
		    (0 != errno && GTM64_ONLY(UINT_MAX == num) NON_GTM64_ONLY(ULONG_MAX == num)))
		{
			util_out_print("Error parsing or invalid parameter for LOG_INTERVAL", TRUE);
			return 0;
		}
		*second_num = num;
		retval |= CLI_2NUM_SECOND_SPECIFIED;
	} /* else, second number not specified */
	return retval;
}