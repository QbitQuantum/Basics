static void ttyin(char buf[], register int nmax, char pchar)
{
	char *sp;
	int c;
	int slash = 0;
	int maxlen;

	sp = buf;
	maxlen = 0;
	while (sp - buf < nmax) {
		if (promptlen > maxlen)
			maxlen = promptlen;
		c = readch();
		if (c == '\\') {
			slash++;
		} else if (((cc_t) c == otty.c_cc[VERASE]) && !slash) {
			if (sp > buf) {
#ifdef HAVE_WIDECHAR
				if (MB_CUR_MAX > 1) {
					wchar_t wc;
					size_t pos = 0, mblength;
					mbstate_t state, state_bak;

					memset(&state, '\0', sizeof(mbstate_t));

					while (1) {
						state_bak = state;
						mblength =
						    mbrtowc(&wc, buf + pos,
							    sp - buf, &state);

						state = (mblength == (size_t)-2
							 || mblength ==
							 (size_t)-1) ? state_bak
						    : state;
						mblength =
						    (mblength == (size_t)-2
						     || mblength == (size_t)-1
						     || mblength ==
						     0) ? 1 : mblength;

						if (buf + pos + mblength >= sp)
							break;

						pos += mblength;
					}

					if (mblength == 1) {
						ERASEONECOLUMN(docrterase);
					} else {
						int wc_width;
						wc_width = wcwidth(wc);
						wc_width =
						    (wc_width <
						     1) ? 1 : wc_width;
						while (wc_width--) {
							ERASEONECOLUMN(docrterase);
						}
					}

					while (mblength--) {
						--promptlen;
						--sp;
					}
				} else
#endif	/* HAVE_WIDECHAR */
				{
					--promptlen;
					ERASEONECOLUMN(docrterase);
					--sp;
				}

				if ((*sp < ' ' && *sp != '\n') || *sp == RUBOUT) {
					--promptlen;
					ERASEONECOLUMN(docrterase);
				}
				continue;
			} else {
				if (!eraseln)
					promptlen = maxlen;
				siglongjmp(restore, 1);
			}
		} else if (((cc_t) c == otty.c_cc[VKILL]) && !slash) {
			if (hard) {
				show(c);
				putchar('\n');
				putchar(pchar);
			} else {
				putchar('\r');
				putchar(pchar);
				if (eraseln)
					erasep(1);
				else if (docrtkill)
					while (promptlen-- > 1)
						putserr(BSB);
				promptlen = 1;
			}
			sp = buf;
			fflush(stdout);
			continue;
		}
		if (slash && ((cc_t) c == otty.c_cc[VKILL]
			      || (cc_t) c == otty.c_cc[VERASE])) {
			ERASEONECOLUMN(docrterase);
			--sp;
		}
		if (c != '\\')
			slash = 0;
		*sp++ = c;
		if ((c < ' ' && c != '\n' && c != ESC) || c == RUBOUT) {
			c += (c == RUBOUT) ? -0100 : 0100;
			putserr(CARAT);
			promptlen++;
		}
		if (c != '\n' && c != ESC) {
			putcerr(c);
			promptlen++;
		} else
			break;
	}
	*--sp = '\0';
	if (!eraseln)
		promptlen = maxlen;
	if (sp - buf >= nmax - 1)
		more_error(_("Line too long"));
}