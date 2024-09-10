/** find first not blank char */
static inline char *skip_blank(char *p)
{
	while(isblank(*p))
		p++;
	return p;
}