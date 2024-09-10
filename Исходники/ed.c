static char *skip_blank(const char *cp)
{
	while (isblank(*cp))
		cp++;
	return (char *)cp;
}