/*
 * 'string' compare for scanning
 */
int
ipsc_matchstr(sinfo_t *sp, char *str, int n)
{
	char *s, *t, *up;
	int i = n;

	if (i > sp->s_len)
		i = sp->s_len;
	up = str;

	for (s = sp->s_txt, t = sp->s_msk; i; i--, s++, t++, up++)
		switch ((int)*t)
		{
		case '.' :
			if (*s != *up)
				return 1;
			break;
		case '?' :
			if (!ISALPHA(*up) || ((*s & 0x5f) != (*up & 0x5f)))
				return 1;
			break;
		case '*' :
			break;
		}
	return 0;
}