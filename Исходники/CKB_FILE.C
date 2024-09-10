/*
 * raw_read_file:
 *	read the CKB file completely
 */
BOOL raw_read_file(char *name)
{
	DTA		mydta;
	int		handle;

	if (CKBfileblock) {
		Mfree(CKBfileblock);
		CKBfileblock = NULL;
	}

	Readlnidx = 0; cline=0;

	/* locate file */
	Fsetdta(&mydta);
	if (Fsfirst(name, FA_READONLY|FA_ARCHIVE|FA_SYSTEM)!=0) return FALSE;		/* file not found */

	/* alloc space for the file */
	CKBfileblock = Malloc((mydta.d_length+16L)&(-16L));
	if (CKBfileblock==0) return FALSE;				/* out of memory */

	/* open the file */
	handle = (int)Fopen(name, FO_READ);
	if (handle<=0) return FALSE;					/* file open error */

	/* read all of it */
	CKBfilesize = Fread(handle, mydta.d_length, CKBfileblock);

	/* close it */
	Fclose(handle);

	if (CKBfilesize<=0) return FALSE;
	return TRUE;
}