/*
 * Completely read named file into a buffer.
 * Params:
 *   path - full path of file
 *   pBuffer - reference to variable where pointer to allocated buffer
 *     should be stored
 *   pLen - reference to variable where length of file should
 *     be stored
 * Returns: 0 if successful, error code (< 0) if not
 */
int Read_Fully(const char *path, void **pBuffer, ulong_t *pLen)
{
    struct File *file = 0;
    struct VFS_File_Stat stat;
    int rc;
    char *buf = 0;
    int numBytesRead;

    if ((rc = Stat(path, &stat)) < 0 || (rc = Open(path, O_READ, &file)) < 0)
		goto fail;
    if (stat.size < 0) {
		rc = ENOTFOUND;
		goto fail;
    }

    buf = (char*) Malloc(stat.size);
    if (buf == 0)
	goto memfail;

    /* Read until buffer is full */
    numBytesRead = 0;
    while (numBytesRead < stat.size) {
	rc = Read(file, buf + numBytesRead, stat.size - numBytesRead);
	if (rc < 0)
	    goto fail;
	numBytesRead += rc;
    }

    /* Success! */
    Close(file);
    *pBuffer = (void*) buf;
    *pLen = stat.size;
    return 0;

memfail:
    rc = ENOMEM;
fail:
    if (file != 0)
	Close(file);
    if (buf != 0)
	Free(buf);
    return rc;
}