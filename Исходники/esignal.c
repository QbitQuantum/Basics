int
ReadPreamble(char **version,	/* version (output) */
	     char **arch,	/* architecture (output) */
	     long *pre_size,	/* preamble size (output) */
	     long *hdr_size,	/* header size (output) */
	     long *rec_size,	/* record size (output) */
	     FILE *file)	/* input file */
{
    char    buf[PREAM_MAX + 1]; /* input string + null */

    /* Check magic number, MAGIC. */

    if (!GetLine(buf, 8, file))
	return FALSE;

    if (strcmp(buf, MAGIC) != 0)
	return FALSE;

    if (!GetLine(buf, 8, file))
	return FALSE;
    if (version != NULL)
	*version = StrDup(buf);

    /* Get architecture. */

    if (!GetLine(buf, 8, file))
	return FALSE;
    if (arch != NULL)
	*arch = StrDup(buf);

    /* Get preamble size */

    if (!GetLong(pre_size, 8, file))
	return FALSE;

    /* Could check *pre_size here. */

    /* Get header size */

    if (!GetLong(hdr_size, 8, file))
	return FALSE;

    /* Get record size */

    if (!GetLong(rec_size, 8, file))
	return FALSE;

    return TRUE;		/* success */
}