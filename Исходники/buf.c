buf_t* buf_read(FILE *f)
{
	const int sigsize = 8;
	wint_t wc;
	uint8_t y;
	int ret;
	buf_t *b;
	wchar_t wcswap[sigsize];
	uint8_t yswap[2];
	int i;

	/* read sig bytes or first sigsize chars */
	for(i = 0; i < sigsize; i++) {
		wc = getwc(f);
		EXIT_FERROR(f);
		if(wc == WEOF) {
			b = buf_new(false);
			EXIT_NULL(b);
			buf_push_nwchar(b, wcswap, i);
			return b;
		}
		wcswap[i] = (wchar_t)wc;
	}

	/* check for sig to determine if 8xp */
	if( !wcsncmp(wcswap, L"**TI83F*", sigsize) ) {
		b = buf_new(true);
	} else {
		b = buf_new(false);
	}

	/* not 8xp, so just read the rest */
	if( !b->is_8xp) {
		buf_push_nwchar(b, wcswap, sigsize);
		while( (wc = getwc(f)) != WEOF) {
			buf_push_wchar(b, (wchar_t)wc);
		}

		return b;
	}

	/* discard remainder of header */
	for(i = sigsize; i < HEADER_SIZE; i++) {
		ret = fread(&y, sizeof(uint8_t), 1, f);
		EXIT_FERROR(f);
		/* EOF this early means malformed 8xp */
		if(ret <= 0) {
			printf("\e[1mtok8x:\e[0m"
					"\e[1;31merror:\e[0m %s\n",
					"malformed .8xp input"
					);
			exit(EIO);
		}
	}