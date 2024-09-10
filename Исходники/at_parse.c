	return -1;
}

#/* */
EXPORT_DEF int at_parse_ccwa(char* str, unsigned * class)
{
	/* 
	 * CCWA may be in form:
	 *	in response of AT+CCWA=?
	 *		+CCWA: (0,1)
	 *	in response of AT+CCWA=?
	 *		+CCWA: <n>
	 *	in response of "AT+CCWA=[<n>[,<mode>[,<class>]]]"
	 *		+CCWA: <status>,<class1>
	 *
	 *	unsolicited result code
	 *		+CCWA: <number>,<type>,<class>,[<alpha>][,<CLI validity>[,<subaddr>,<satype>[,<priority>]]]
	 */
	char delimiters[] = ":,,";
	char * marks[STRLEN(delimiters)];

	/* parse URC only here */
	if(mark_line(str, delimiters, marks) == ITEMS_OF(marks))
	{
		if(sscanf(marks[2] + 1, "%u", class) == 1)
			return 0;
	}

	return -1;
}
