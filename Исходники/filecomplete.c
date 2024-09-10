/*
 * Complete the word at or before point,
 * 'what_to_do' says what to do with the completion.
 * \t   means do standard completion.
 * `?' means list the possible completions.
 * `*' means insert all of the possible completions.
 * `!' means to do standard completion, and list all possible completions if
 * there is more than one.
 *
 * Note: '*' support is not implemented
 *       '!' could never be invoked
 */
int
fn_complete(EditLine *el,
	char *(*complet_func)(const char *, int),
	char **(*attempted_completion_function)(const char *, int, int),
	const Char *word_break, const Char *special_prefixes,
	const char *(*app_func)(const char *), size_t query_items,
	int *completion_type, int *over, int *point, int *end)
{
	const TYPE(LineInfo) *li;
	Char *temp;
        char **matches;
	const Char *ctemp;
	size_t len;
	int what_to_do = '\t';
	int retval = CC_NORM;

	if (el->el_state.lastcmd == el->el_state.thiscmd)
		what_to_do = '?';

	/* readline's rl_complete() has to be told what we did... */
	if (completion_type != NULL)
		*completion_type = what_to_do;

	if (!complet_func)
		complet_func = fn_filename_completion_function;
	if (!app_func)
		app_func = append_char_function;

	/* We now look backwards for the start of a filename/variable word */
	li = FUN(el,line)(el);
	ctemp = li->cursor;
	while (ctemp > li->buffer
	    && !Strchr(word_break, ctemp[-1])
	    && (!special_prefixes || !Strchr(special_prefixes, ctemp[-1]) ) )
		ctemp--;

	len = (size_t)(li->cursor - ctemp);
	temp = el_malloc((len + 1) * sizeof(*temp));
	(void)Strncpy(temp, ctemp, len);
	temp[len] = '\0';

	/* these can be used by function called in completion_matches() */
	/* or (*attempted_completion_function)() */
	if (point != NULL)
		*point = (int)(li->cursor - li->buffer);
	if (end != NULL)
		*end = (int)(li->lastchar - li->buffer);

	if (attempted_completion_function) {
		int cur_off = (int)(li->cursor - li->buffer);
		matches = (*attempted_completion_function)(
		    ct_encode_string(temp, &el->el_scratch),
		    cur_off - (int)len, cur_off);
	} else
		matches = NULL;
	if (!attempted_completion_function || 
	    (over != NULL && !*over && !matches))
		matches = completion_matches(
		    ct_encode_string(temp, &el->el_scratch), complet_func);

	if (over != NULL)
		*over = 0;

	if (matches) {
		int i;
		size_t matches_num, maxlen, match_len, match_display=1;

		retval = CC_REFRESH;
		/*
		 * Only replace the completed string with common part of
		 * possible matches if there is possible completion.
		 */
		if (matches[0][0] != '\0') {
			el_deletestr(el, (int) len);
			FUN(el,insertstr)(el,
			    ct_decode_string(matches[0], &el->el_scratch));
		}

		if (what_to_do == '?')
			goto display_matches;

		if (matches[2] == NULL &&
		    (matches[1] == NULL || strcmp(matches[0], matches[1]) == 0)) {
			/*
			 * We found exact match. Add a space after
			 * it, unless we do filename completion and the
			 * object is a directory.
			 */
			FUN(el,insertstr)(el,
			    ct_decode_string((*app_func)(matches[0]),
			    &el->el_scratch));
		} else if (what_to_do == '!') {
    display_matches:
			/*
			 * More than one match and requested to list possible
			 * matches.
			 */

			for(i = 1, maxlen = 0; matches[i]; i++) {
				match_len = strlen(matches[i]);
				if (match_len > maxlen)
					maxlen = match_len;
			}
			/* matches[1] through matches[i-1] are available */
			matches_num = (size_t)(i - 1);
				
			/* newline to get on next line from command line */
			(void)fprintf(el->el_outfile, "\n");

			/*
			 * If there are too many items, ask user for display
			 * confirmation.
			 */
			if (matches_num > query_items) {
				(void)fprintf(el->el_outfile,
				    "Display all %zu possibilities? (y or n) ",
				    matches_num);
				(void)fflush(el->el_outfile);
				if (getc(stdin) != 'y')
					match_display = 0;
				(void)fprintf(el->el_outfile, "\n");
			}

			if (match_display) {
				/*
				 * Interface of this function requires the
				 * strings be matches[1..num-1] for compat.
				 * We have matches_num strings not counting
				 * the prefix in matches[0], so we need to
				 * add 1 to matches_num for the call.
				 */
				fn_display_match_list(el, matches,
				    matches_num+1, maxlen);
			}
			retval = CC_REDISPLAY;
		} else if (matches[0][0]) {
			/*
			 * There was some common match, but the name was
			 * not complete enough. Next tab will print possible
			 * completions.
			 */
			el_beep(el);
		} else {
			/* lcd is not a valid object - further specification */
			/* is needed */
			el_beep(el);
			retval = CC_NORM;
		}

		/* free elements of array and the array itself */
		for (i = 0; matches[i]; i++)
			el_free(matches[i]);
		el_free(matches);
		matches = NULL;
	}
	el_free(temp);
	return retval;
}