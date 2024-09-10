/* Match pattern "p" against the a virtually-joined string consisting
 * of "text" and any strings in array "a". */
static int dowild(const uchar *p, const uchar *text, const uchar*const *a)
{
	uchar p_ch;

#ifdef WILD_TEST_ITERATIONS
	wildmatch_iteration_count++;
#endif

	for ( ; (p_ch = *p) != '\0'; text++, p++) {
		int matched, special;
		uchar t_ch, prev_ch;
		while ((t_ch = *text) == '\0') {
			if (*a == NULL) {
				if (p_ch != '*')
					return ABORT_ALL;
				break;
			}
			text = *a++;
		}
		if (force_lower_case && ISUPPER(t_ch))
			t_ch = tolower(t_ch);
		switch (p_ch) {
			case '\\':
				/* Literal match with following character.  Note that the test
				 * in "default" handles the p[1] == '\0' failure case. */
				p_ch = *++p;
				/* FALLTHROUGH */
			default:
				if (t_ch != p_ch)
					return FALSE;
				continue;
			case '?':
				/* Match anything but '/'. */
				if (t_ch == '/')
					return FALSE;
				continue;
			case '*':
				if (*++p == '*') {
					while (*++p == '*') {}
					special = TRUE;
				} else
					special = FALSE;
				if (*p == '\0') {
					/* Trailing "**" matches everything.  Trailing "*" matches
					 * only if there are no more slash characters. */
					if (!special) {
						do {
							if (strchr((char*)text, '/') != NULL)
								return FALSE;
						} while ((text = *a++) != NULL);
					}
					return TRUE;
				}
				while (1) {
					if (t_ch == '\0') {
						if ((text = *a++) == NULL)
							break;
						t_ch = *text;
						continue;
					}
					if ((matched = dowild(p, text, a)) != FALSE) {
						if (!special || matched != ABORT_TO_STARSTAR)
							return matched;
					} else if (!special && t_ch == '/')
						return ABORT_TO_STARSTAR;
					t_ch = *++text;
				}
				return ABORT_ALL;
			case '[':
				p_ch = *++p;
#ifdef NEGATE_CLASS2
				if (p_ch == NEGATE_CLASS2)
					p_ch = NEGATE_CLASS;
#endif
				/* Assign literal TRUE/FALSE because of "matched" comparison. */
				special = p_ch == NEGATE_CLASS? TRUE : FALSE;
				if (special) {
					/* Inverted character class. */
					p_ch = *++p;
				}
				prev_ch = 0;
				matched = FALSE;
				do {
					if (!p_ch)
						return ABORT_ALL;
					if (p_ch == '\\') {
						p_ch = *++p;
						if (!p_ch)
							return ABORT_ALL;
						if (t_ch == p_ch)
							matched = TRUE;
					} else if (p_ch == '-' && prev_ch && p[1] && p[1] != ']') {
						p_ch = *++p;
						if (p_ch == '\\') {
							p_ch = *++p;
							if (!p_ch)
								return ABORT_ALL;
						}
						if (t_ch <= p_ch && t_ch >= prev_ch)
							matched = TRUE;
						p_ch = 0; /* This makes "prev_ch" get set to 0. */
					} else if (p_ch == '[' && p[1] == ':') {
						const uchar *s;
						int i;
						for (s = p += 2; (p_ch = *p) && p_ch != ']'; p++) {}
						if (!p_ch)
							return ABORT_ALL;
						i = p - s - 1;
						if (i < 0 || p[-1] != ':') {
							/* Didn't find ":]", so treat like a normal set. */
							p = s - 2;
							p_ch = '[';
							if (t_ch == p_ch)
								matched = TRUE;
							continue;
						}
						if (CC_EQ(s,i, "alnum")) {
							if (ISALNUM(t_ch))
								matched = TRUE;
						} else if (CC_EQ(s,i, "alpha")) {
							if (ISALPHA(t_ch))
								matched = TRUE;
						} else if (CC_EQ(s,i, "blank")) {
							if (ISBLANK(t_ch))
								matched = TRUE;
						} else if (CC_EQ(s,i, "cntrl")) {
							if (ISCNTRL(t_ch))
								matched = TRUE;
						} else if (CC_EQ(s,i, "digit")) {
							if (ISDIGIT(t_ch))
								matched = TRUE;
						} else if (CC_EQ(s,i, "graph")) {
							if (ISGRAPH(t_ch))
								matched = TRUE;
						} else if (CC_EQ(s,i, "lower")) {
							if (ISLOWER(t_ch))
								matched = TRUE;
						} else if (CC_EQ(s,i, "print")) {
							if (ISPRINT(t_ch))
								matched = TRUE;
						} else if (CC_EQ(s,i, "punct")) {
							if (ISPUNCT(t_ch))
								matched = TRUE;
						} else if (CC_EQ(s,i, "space")) {
							if (ISSPACE(t_ch))
								matched = TRUE;
						} else if (CC_EQ(s,i, "upper")) {
							if (ISUPPER(t_ch))
								matched = TRUE;
						} else if (CC_EQ(s,i, "xdigit")) {
							if (ISXDIGIT(t_ch))
								matched = TRUE;
						} else /* malformed [:class:] string */
							return ABORT_ALL;
						p_ch = 0; /* This makes "prev_ch" get set to 0. */
					} else if (t_ch == p_ch)
						matched = TRUE;
				} while (prev_ch = p_ch, (p_ch = *++p) != ']');
				if (matched == special || t_ch == '/')
					return FALSE;
				continue;
		}
	}

	do {
		if (*text)
			return FALSE;
	} while ((text = *a++) != NULL);

	return TRUE;
}