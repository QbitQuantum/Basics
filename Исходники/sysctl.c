static bool IgnoreDeprecated;
static bool NameOnly;
static bool PrintName;
static bool PrintNewline;
static bool IgnoreError;
static bool Quiet;
static char *pattern;

/* Function prototypes. */
static int pattern_match(const char *string, const char *pat);
static int DisplayAll(const char *restrict const path);

static void slashdot(char *restrict p, char old, char new)
{
	int warned = 1;
	p = strpbrk(p, "/.");
	if (!p)
		/* nothing -- can't be, but oh well */
		return;
	if (*p == new)
		/* already in desired format */
		return;
	while (p) {
		char c = *p;
		if ((*(p + 1) == '/' || *(p + 1) == '.') && warned) {
			xwarnx(_("separators should not be repeated: %s"), p);
			warned = 0;
		}
		if (c == old)
			*p = new;
		if (c == new)