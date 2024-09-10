/* em_capitol_case():
 *	Capitalize the characters from cursor to end of current word
 *	[M-c]
 */
libedit_private el_action_t
/*ARGSUSED*/
em_capitol_case(EditLine *el, wint_t c __attribute__((__unused__)))
{
	wchar_t *cp, *ep;

	ep = c__next_word(el->el_line.cursor, el->el_line.lastchar,
	    el->el_state.argument, ce__isword);

	for (cp = el->el_line.cursor; cp < ep; cp++) {
		if (iswalpha(*cp)) {
			if (iswlower(*cp))
				*cp = towupper(*cp);
			cp++;
			break;
		}
	}
	for (; cp < ep; cp++)
		if (iswupper(*cp))
			*cp = towlower(*cp);

	el->el_line.cursor = ep;
	if (el->el_line.cursor > el->el_line.lastchar)
		el->el_line.cursor = el->el_line.lastchar;
	return CC_REFRESH;
}