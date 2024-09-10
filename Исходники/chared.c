/* cv__isword():
 *	Return if p is part of a word according to vi
 */
libedit_private int
cv__isword(wint_t p)
{
	if (iswalnum(p) || p == L'_')
		return 1;
	if (iswgraph(p))
		return 2;
	return 0;
}