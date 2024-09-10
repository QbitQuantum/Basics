/* or process terminates, there would be nothing on disk.   */
void reset_scratch()
{
    char *path;
    if (fp_scratch == NULL)
    {
	fp_scratch = fopen (path=TMPNAM(NULL), "w+");
	if (fp_scratch == NULL)
	    pe ("reset_scratch: cannot open temporary file\n");
	/* the file is deleted at the termination of the */
	if (unlink(path) < 0)
	    pe ("reset_scratch: cannot unlink temporary file\n");
	/* process because its link count would be 0.    */
	setvbuf (fp_scratch, scratch_buffer, _IOFBF, SCRATCH_BUFFER_SIZE);
	/* fully buffered: unless fflush() or page full, it is there */
	return;
    }
    rewind (fp_scratch);
    return;
} /* end reset_scratch() */