/*							HTCleanTelnetString()
 *	Make sure that the given string doesn't contain characters that
 *	could cause security holes, such as newlines in ftp, gopher,
 *	news or telnet URLs; more specifically: allows everything between
 *	ASCII 20-7E, and also A0-FE, inclusive. Also TAB ('\t') allowed!
 *
 * On entry,
 *	str	the string that is *modified* if necessary.  The
 *		string will be truncated at the first illegal
 *		character that is encountered.
 * On exit,
 *	returns	YES, if the string was modified.
 *		NO, otherwise.
 */
PUBLIC BOOL HTCleanTelnetString (char * str)
{
    char * cur = str;

    if (!str) return NO;

    while (*cur) {
	int a = TOASCII((unsigned char) *cur);
	if (a != 0x9 && (a < 0x20 || (a > 0x7E && a < 0xA0) ||  a > 0xFE)) {
	    HTTRACE(URI_TRACE, "Illegal..... character in URL: \"%s\"\n" _ str);
	    *cur = 0;
	    HTTRACE(URI_TRACE, "Truncated... \"%s\"\n" _ str);
	    return YES;
	}
	cur++;
    }
    return NO;
}