/**
 * Convert a list of utf8 chars to wide-chars.  The reason for doing
 * this is kind-of dorky: its so that we can easily find,
 * character-by-character, if a given character is a quotation mark
 * or a bullet.  This works only because the quotation marks and
 * bullets are exactly one (wide) character in length. I would like
 * it better if we didn't do this wide-char conversion, since wide-chars
 * are badly-behaved in crazy locales, and on MS Windows.
 */
static bool afdict_to_wide(Dictionary afdict, int classno)
{
	Afdict_class * ac;
	wchar_t * wqs;
	mbstate_t mbs;
	size_t i;
	int w;
	dyn_str * qs;
	const char *pqs;

	ac = AFCLASS(afdict, classno);
	if (0 == ac->length) return true;

	qs = dyn_str_new();
	for (i = 0; i < ac->length; i++)
		dyn_strcat(qs, ac->string[i]);

	/*
	 * Convert utf8 to wide chars before use.
	 * In case of error the result is undefined.
	 */
	pqs = qs->str;
	memset(&mbs, 0, sizeof(mbs));
	w = mbsrtowcs(NULL, &pqs, 0, &mbs);
	if (0 > w)
	{
		prt_error("Error: Affix dictionary: %s: "
		          "Invalid utf8 character\n", afdict_classname[classno]);
		return false;
	}

	/* Store the wide char version at the AFCLASS entry. */
	ac->mem_elems =  sizeof(*wqs) * (w+1); /* bytes here, but we don't care */
	ac->string = malloc(ac->mem_elems);
	wqs = (wchar_t *)ac->string;
	pqs = qs->str;
	(void)mbsrtowcs(wqs, &pqs, w, &mbs);
	wqs[w] = L'\0';

	dyn_str_delete(qs);

	return true;
}