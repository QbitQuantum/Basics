/*
 * Given a keyboard layout number return the layout string.
 * We should not be doing this here, but unfortunately there
 * is no interface in the OpenSolaris keyboard API to perform
 * this mapping for us - RFE.
 */
static char *
get_layout_name(int lnum)
{
	FILE *stream;
	char buffer[MAX_LINE_SIZE];
	char *result = NULL;
	int  num;
	char *tmpbuf;

	if ((stream = fopen(KBD_LAYOUT_FILE, "r")) == 0) {
		Perror(KBD_LAYOUT_FILE);
		return (NULL);
	}

	while (fgets(buffer, MAX_LINE_SIZE, stream) != NULL) {
		if (buffer[0] == '#')
			continue;
		if ((result = strtok(buffer, "=")) == NULL)
			continue;
		if ((tmpbuf = strdup(result)) == NULL) {
			Perror("out of memory getting layout names");
			(void) fclose(stream);
			return (NULL);
		}
		if ((result = strtok(NULL, "\n")) == NULL)
			continue;
		num = atoi(result);
		if (num == lnum) {
			break;
		}
		free(tmpbuf);
	}

	(void) fclose(stream);
	return (tmpbuf);
}