/**
 * Reads in one word from the file, allocates space for it,
 * and returns it.
 */
static const char * get_a_word(Dictionary dict, FILE * fp)
{
	char word[MAX_WORD+4]; /* allow for 4-byte wide chars */
	const char * s;
	wint_t c;
	mbstate_t mbss;
	int j;

	do {
		c = fgetwc(fp);
	} while ((c != WEOF) && iswspace(c));
	if (c == WEOF) return NULL;

	memset(&mbss, 0, sizeof(mbss));
	for (j=0; (j <= MAX_WORD-1) && (!iswspace(c)) && (c != WEOF);)
	{
		j += wctomb_check(&word[j], c, &mbss);
		c = fgetwc(fp);
	}

	if (j >= MAX_WORD) {
		word[MAX_WORD] = 0x0;
		prt_error("Fatal Error: The dictionary contains a word that "
		          "is too long. The word was: %s", word);
		exit(1);
	}
	word[j] = '\0';
	s = string_set_add(word, dict->string_set);
	return s;
}