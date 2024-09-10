int get_trait (qse_wcint_t code)
{
	int trait = 0;

	if (iswupper(code))    trait |= TRAIT_UPPER;
	if (iswlower(code))    trait |= TRAIT_LOWER;
	if (iswalpha(code))    trait |= TRAIT_ALPHA;
	if (iswdigit(code))    trait |= TRAIT_DIGIT;
	if (iswxdigit(code))   trait |= TRAIT_XDIGIT;
	if (iswalnum(code))    trait |= TRAIT_ALNUM;
	if (iswspace(code))    trait |= TRAIT_SPACE;
	if (iswprint(code))    trait |= TRAIT_PRINT;
	if (iswgraph(code))    trait |= TRAIT_GRAPH;
	if (iswcntrl(code))    trait |= TRAIT_CNTRL;
	if (iswpunct(code))    trait |= TRAIT_PUNCT;
	if (iswblank(code))    trait |= TRAIT_BLANK;
	/*
	if (iswascii(code))    trait |= TRAIT_ASCII;
	if (isphonogram(code)) trait |= TRAIT_PHONO;
	if (isideogram(code))  trait |= TRAIT_IDEOG;
	if (isenglish(code))   trait |= TRAIT_ENGLI;
	*/

	return trait;
}