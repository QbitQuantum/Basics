int
main(int argc, char *argv[])
{
	mbstate_t state;
	wchar_t wc;
	size_t ret;
	int mode;

	/* configure should already have checked that the locale is supported.  */
	if (setlocale(LC_ALL, "") == NULL) {
		fprintf(stderr, "unable to set standard locale\n");
		return 1;
	}

	/* Test NUL byte input.  */
	{
		const char *src;

		memset(&state, '\0', sizeof(mbstate_t));

		src = "";
		ret = mbsnrtowcs(NULL, &src, 1, 0, &state);
		assert(ret == 0);
		assert(mbsinit (&state));

		src = "";
		ret = mbsnrtowcs(NULL, &src, 1, 1, &state);
		assert(ret == 0);
		assert(mbsinit (&state));

		wc = (wchar_t) 0xBADFACE;
		src = "";
		ret = mbsnrtowcs(&wc, &src, 1, 0, &state);
		assert(ret == 0);
		assert(wc == (wchar_t) 0xBADFACE);
		assert(mbsinit (&state));

		wc = (wchar_t) 0xBADFACE;
		src = "";
		ret = mbsnrtowcs(&wc, &src, 1, 1, &state);
		assert(ret == 0);
		assert(wc == 0);
		assert(mbsinit (&state));
	}

	for (mode = '1'; mode <= '4'; ++mode) {
		int unlimited;
		for (unlimited = 0; unlimited < 2; unlimited++) {
			wchar_t buf[BUFSIZE];
			const char *src;
			mbstate_t temp_state;

			{
				size_t i;
				for (i = 0; i < BUFSIZE; i++)
					buf[i] = (wchar_t) 0xBADFACE;
			}

			switch (mode) {
				case '1':
					/* Locale encoding is ISO-8859-1 or ISO-8859-15.  */
		    	printf("ISO8859-1 ...\n");
				{
					char input[] = "B\374\337er"; /* "Büßer" */
					memset(&state, '\0', sizeof(mbstate_t));

					if (setlocale (LC_ALL, "en_US.ISO8859-1") == NULL) {
						fprintf(stderr,
							"unable to set ISO8859-1 locale, skipping\n");
						break;
					}

					wc = (wchar_t) 0xBADFACE;
					ret = mbrtowc(&wc, input, 1, &state);
					assert(ret == 1);
					assert(wc == 'B');
					assert(mbsinit (&state));
					input[0] = '\0';

					wc = (wchar_t) 0xBADFACE;
					ret = mbrtowc(&wc, input + 1, 1, &state);
					assert(ret == 1);
					assert(wctob (wc) == (unsigned char) '\374');
					assert(mbsinit (&state));
					input[1] = '\0';

					src = input + 2;
					temp_state = state;
					ret = mbsnrtowcs(NULL, &src, 4, unlimited ? BUFSIZE : 1,
						&temp_state);
					assert(ret == 3);
					assert(src == input + 2);
					assert(mbsinit (&state));

					src = input + 2;
					ret = mbsnrtowcs(buf, &src, 4, unlimited ? BUFSIZE : 1,
						&state);
					assert(ret == (unlimited ? 3 : 1));
					assert(src == (unlimited ? NULL : input + 3));
					assert(wctob (buf[0]) == (unsigned char) '\337');
					if (unlimited) {
						assert(buf[1] == 'e');
						assert(buf[2] == 'r');
						assert(buf[3] == 0);
						assert(buf[4] == (wchar_t) 0xBADFACE);
					} else
						assert(buf[1] == (wchar_t) 0xBADFACE);
					assert(mbsinit (&state));
				}
					break;

				case '2':
					/* Locale encoding is UTF-8.  */
		    	printf("UTF-8 ...\n");
				{
					char input[] = "B\303\274\303\237er"; /* "Büßer" */
					memset(&state, '\0', sizeof(mbstate_t));

					if (setlocale (LC_ALL, "en_US.UTF-8") == NULL) {
						fprintf(stderr,
							"unable to set UTF-8 locale, skipping\n");
						break;
					}

					wc = (wchar_t) 0xBADFACE;
					ret = mbrtowc(&wc, input, 1, &state);
					assert(ret == 1);
					assert(wc == 'B');
					assert(mbsinit (&state));
					input[0] = '\0';

					wc = (wchar_t) 0xBADFACE;
					ret = mbrtowc(&wc, input + 1, 1, &state);
					assert(ret == (size_t)(-2));
					assert(wc == (wchar_t) 0xBADFACE);
					assert(!mbsinit (&state));
					input[1] = '\0';

// Copying mbstate_t doesn't really copy the ICU-converter's state, so this
// doesn't work on Haiku.
#ifndef __HAIKU__
					src = input + 2;
					temp_state = state;
					ret = mbsnrtowcs(NULL, &src, 6, unlimited ? BUFSIZE : 2,
						&temp_state);
					assert(ret == 4);
					assert(src == input + 2);
					assert(!mbsinit (&state));
#endif

					src = input + 2;
					ret = mbsnrtowcs(buf, &src, 6, unlimited ? BUFSIZE : 2,
						&state);
					assert(ret == (unlimited ? 4 : 2));
					assert(src == (unlimited ? NULL : input + 5));
					assert(wctob (buf[0]) == EOF);
					assert(wctob (buf[1]) == EOF);
					if (unlimited) {
						assert(buf[2] == 'e');
						assert(buf[3] == 'r');
						assert(buf[4] == 0);
						assert(buf[5] == (wchar_t) 0xBADFACE);
					} else
						assert(buf[2] == (wchar_t) 0xBADFACE);
					assert(mbsinit (&state));
				}
					break;

				case '3':
					/* Locale encoding is EUC-JP.  */
		    	printf("EUC-JP ...\n");
				{
					char input[] = "<\306\374\313\334\270\354>"; /* "<日本語>" */
					memset(&state, '\0', sizeof(mbstate_t));

					if (setlocale (LC_ALL, "en_US.EUC-JP") == NULL) {
						fprintf(stderr,
							"unable to set EUC-JP locale, skipping\n");
						break;
					}

					wc = (wchar_t) 0xBADFACE;
					ret = mbrtowc(&wc, input, 1, &state);
					assert(ret == 1);
					assert(wc == '<');
					assert(mbsinit (&state));
					input[0] = '\0';

					wc = (wchar_t) 0xBADFACE;
					ret = mbrtowc(&wc, input + 1, 2, &state);
					assert(ret == 2);
					assert(wctob (wc) == EOF);
					assert(mbsinit (&state));
					input[1] = '\0';
					input[2] = '\0';

					wc = (wchar_t) 0xBADFACE;
					ret = mbrtowc(&wc, input + 3, 1, &state);
					assert(ret == (size_t)(-2));
					assert(wc == (wchar_t) 0xBADFACE);
					assert(!mbsinit (&state));
					input[3] = '\0';

// Copying mbstate_t doesn't really copy the ICU-converter's state, so this
// doesn't work on Haiku.
#ifndef __HAIKU__
					src = input + 4;
					temp_state = state;
					ret = mbsnrtowcs(NULL, &src, 5, unlimited ? BUFSIZE : 2,
						&temp_state);
					assert(ret == 3);
					assert(src == input + 4);
					assert(!mbsinit (&state));
#endif

					src = input + 4;
					ret = mbsnrtowcs(buf, &src, 5, unlimited ? BUFSIZE : 2,
						&state);
					assert(ret == (unlimited ? 3 : 2));
					assert(src == (unlimited ? NULL : input + 7));
					assert(wctob (buf[0]) == EOF);
					assert(wctob (buf[1]) == EOF);
					if (unlimited) {
						assert(buf[2] == '>');
						assert(buf[3] == 0);
						assert(buf[4] == (wchar_t) 0xBADFACE);
					} else
						assert(buf[2] == (wchar_t) 0xBADFACE);
					assert(mbsinit (&state));
				}
					break;

				case '4':
					/* Locale encoding is GB18030.  */
		    	printf("GB18030 ...\n");
				{
					char input[] = "B\250\271\201\060\211\070er"; /* "Büßer" */
					memset(&state, '\0', sizeof(mbstate_t));

					if (setlocale (LC_ALL, "en_US.GB18030") == NULL) {
						fprintf(stderr,
							"unable to set GB18030 locale, skipping\n");
						break;
					}

					wc = (wchar_t) 0xBADFACE;
					ret = mbrtowc(&wc, input, 1, &state);
					assert(ret == 1);
					assert(wc == 'B');
					assert(mbsinit (&state));
					input[0] = '\0';

					wc = (wchar_t) 0xBADFACE;
					ret = mbrtowc(&wc, input + 1, 1, &state);
					assert(ret == (size_t)(-2));
					assert(wc == (wchar_t) 0xBADFACE);
					assert(!mbsinit (&state));
					input[1] = '\0';

// Copying mbstate_t doesn't really copy the ICU-converter's state, so this
// doesn't work on Haiku.
#ifndef __HAIKU__
					src = input + 2;
					temp_state = state;
					ret = mbsnrtowcs(NULL, &src, 8, unlimited ? BUFSIZE : 2,
						&temp_state);
					assert(ret == 4);
					assert(src == input + 2);
					assert(!mbsinit (&state));
#endif

					src = input + 2;
					ret = mbsnrtowcs(buf, &src, 8, unlimited ? BUFSIZE : 2,
						&state);
					assert(ret == (unlimited ? 4 : 2));
					assert(src == (unlimited ? NULL : input + 7));
					assert(wctob (buf[0]) == EOF);
					assert(wctob (buf[1]) == EOF);
					if (unlimited) {
						assert(buf[2] == 'e');
						assert(buf[3] == 'r');
						assert(buf[4] == 0);
						assert(buf[5] == (wchar_t) 0xBADFACE);
					} else
						assert(buf[2] == (wchar_t) 0xBADFACE);
					assert(mbsinit (&state));
				}
					break;

				default:
					return 1;
			}
		}
	}

	return 0;
}