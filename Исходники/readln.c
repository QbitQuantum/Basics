char *
Readline(char *prompt)
{
	char *linecopy, *line, *cp;
	char lbuf[256];

	if (gIsTTYr) {
		line = getline(prompt);
	} else {
		line = fgets(lbuf, sizeof(lbuf) - 1, stdin);
		if (line != NULL) {
			cp = line + strlen(line) - 1;
			if (*cp == '\n')
				*cp = '\0';
		}
	}

	if (line != NULL) {
		if (line[0] == '\0')
			return NULL;	/* EOF */
		linecopy = StrDup(line);
		line = linecopy;
	}
	return (line);
}	/* Readline */