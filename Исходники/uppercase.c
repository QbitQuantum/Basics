char   *uppercase(char *string)
{
    char   *cp;
    int     ch;

    for (cp = string; (ch = *cp) != 0; cp++)
	if (ISLOWER(ch))
	    *cp = TOUPPER(ch);
    return (string);
}