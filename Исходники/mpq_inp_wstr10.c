int mpq_inp_wstr10(mpq_t rop, FILE* in) {
	char* buf = malloc(sizeof(char));
	size_t len = 1;
	wint_t c;
	for(;;) {
		c = fgetwc(in);
		if(!(iswdigit(c) || (len == 1 && c == L'-') || (c == L'/')))
			break;
		len++;
		buf = realloc(buf, sizeof(char) * len);
		buf[len - 2] = wctob(c);
	}
	buf[len - 1] = '\0';
	ungetwc(c, in);
	
	int n = mpq_set_str(rop, buf, 10);
	free(buf);
	
	return n;
}