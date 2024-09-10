static int 
parse_button(char *s, int *buttonp)
{
    register char *cp;

    /* lower case name */
    for (cp = s; *cp; cp++) {
	if (isascii (*cp) && isupper (*cp)) {
#ifdef _tolower
	    *cp = _tolower (*cp);
#else
	    *cp = tolower (*cp);
#endif /* _tolower */
	}
    }

    if (strcmp (s, "any") == 0) {
	*buttonp = SelectButtonAny;
	return (1);
    }

    /* check for non-numeric input */
    for (cp = s; *cp; cp++) {
	if (!(isascii (*cp) && isdigit (*cp))) return (0);  /* bogus name */
    }

    *buttonp = atoi (s);
    return (1);
}