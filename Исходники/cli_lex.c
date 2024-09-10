/*
 * -------------------------------------------------------
 * Check if string is a Hex number
 *
 * Return:
 *	TRUE	- identifier
 *	FALSE	- otherwise
 * -------------------------------------------------------
 */
int cli_is_hex(char *p)
{
	if (('+' == *p) || ('-' == *p))
		p++;

	if (('0' == *p) && ('X' == toupper(*(p + 1))))
        {
                p = p + 2;
        }

	while (*p && ISXDIGIT(*p))
		p++;

	return ((*p) ? FALSE : TRUE);
}