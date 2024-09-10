/* vi_match():
 *	Vi go to matching () {} or []
 *	[%]
 */
libedit_private el_action_t
/*ARGSUSED*/
vi_match(EditLine *el, wint_t c __attribute__((__unused__)))
{
	const wchar_t match_chars[] = L"()[]{}";
	wchar_t *cp;
	size_t delta, i, count;
	wchar_t o_ch, c_ch;

	*el->el_line.lastchar = '\0';		/* just in case */

	i = wcscspn(el->el_line.cursor, match_chars);
	o_ch = el->el_line.cursor[i];
	if (o_ch == 0)
		return CC_ERROR;
	delta = (size_t)(wcschr(match_chars, o_ch) - match_chars);
	c_ch = match_chars[delta ^ 1];
	count = 1;
	delta = 1 - (delta & 1) * 2;

	for (cp = &el->el_line.cursor[i]; count; ) {
		cp += delta;
		if (cp < el->el_line.buffer || cp >= el->el_line.lastchar)
			return CC_ERROR;
		if (*cp == o_ch)
			count++;
		else if (*cp == c_ch)
			count--;
	}

	el->el_line.cursor = cp;

	if (el->el_chared.c_vcmd.action != NOP) {
		/* NB posix says char under cursor should NOT be deleted
		   for -ve delta - this is different to netbsd vi. */
		if (delta > 0)
			el->el_line.cursor++;
		cv_delfini(el);
		return CC_REFRESH;
	}
	return CC_CURSOR;
}