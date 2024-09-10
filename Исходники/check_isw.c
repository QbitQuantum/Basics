void
test2()
{
	unsigned char *s;
	unsigned char *buf;
	int i, j;
	size_t n;
	wchar_t c, d;
	mbstate_t state;

	s = malloc(256);
	if (!s) {
		bad++;
		return;
	}
	buf = malloc(MB_CUR_MAX);
	if (!buf) {
		bad++;
		free(s);
		return;
	}
	for (i = 0; i < 256; i++)
		s[i] = i+1;

	j = 0;
	mbrtowc(NULL, NULL, 1, &state);
	printf(" %02x: ", 0);

	while ((n = mbrtowc(&c, s+j, 256-j, &state)) == 1) {
		printf(" %02x: ", s[j]);
		check_bool(isalnum(s[j]), iswalnum(c), '1');
		check_bool(isalpha(s[j]), iswalpha(c), '2');
		check_bool(isblank(s[j]), iswblank(c), '3');
		check_bool(iscntrl(s[j]), iswcntrl(c), '4');
		check_bool(isdigit(s[j]), iswdigit(c), '5');
		check_bool(isgraph(s[j]), iswgraph(c), '6');
		check_bool(islower(s[j]), iswlower(c), '6');
		check_bool(isprint(s[j]), iswprint(c), '7');
		check_bool(ispunct(s[j]), iswpunct(c), '8');
		check_bool(isspace(s[j]), iswspace(c), '9');
		check_bool(isupper(s[j]), iswupper(c), 'a');
		check_bool(isxdigit(s[j]), iswxdigit(c), 'b');
		d = towlower(c);
		if (wctomb(buf, d) == 1) {	
			check_value(tolower(s[j]), buf[0], 'c');
		} else {
			bad++;
		}
		d = towupper(c);
		if (wctomb(buf, d) == 1) {	
			check_value(toupper(s[j]), buf[0], 'c');
		} else {
			bad++;
		}
		if (s[j] % 8 == 7)
			printf("\n");
		j++;
	}
	if (n != 0 || j != 255) {
		bad++;
	}
	free(s);
	free(buf);
}