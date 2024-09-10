static int
iskw(register char *s)
{
	register char **ss = l_keywds;
	register int i = 1;
	register char *cp = s;

	while (++cp, isidchr(*cp))
		i++;
	while ((cp = *ss++))
		if (!STRNCMP(s,cp,i) && !isidchr(cp[i]))
			return (i);
	return (0);
}