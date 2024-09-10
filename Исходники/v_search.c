/*
 * is_especial --
 *	Test if the character is special in an extended RE.
 */
static int
is_especial(CHAR_T c)
{
	/*
	 * !!!
	 * Right-brace is not an ERE special according to IEEE 1003.1-2001.
	 * Right-parenthesis is a special character (so quoting doesn't hurt),
	 * though it has no special meaning in this context, viz. at the
	 * beginning of the string.  So we need not quote it.  Then again,
	 * see the BUGS section in regex/re_format.7.
	 * The tilde is vi-specific, of course.
	 */
	return (STRCHR(L(".[\\()*+?{|^$~"), c) && c);
}