static int
find_file(int fd, zentry *entry, const char *file_name)
{
    int	    bytes;
    int	    res;
    int	    entry_size;
    int	    read_size;
    int	    base_offset;
    Byte    *p;
    Byte    *bp;
    Byte    *buffer;
    Byte    locbuf[LOCHDR];

    if ((buffer = (Byte*)malloc(BUFSIZE)) == NULL) {
	return(-1);
    }

    p = buffer;
    bp = buffer;

    /*
     * Read the END Header, which is the starting point for ZIP files.
     * (Clearly designed to make writing a zip file easier than reading
     * one. Now isn't that precious...)
     */
    if ((base_offset = find_end(fd, bp)) == -1) {
        free(buffer);
	return (-1);
    }

    /*
     * There is a historical, but undocumented, ability to allow for
     * additional "stuff" to be prepended to the zip/jar file. It seems
     * that this has been used to prepend an actual java launcher
     * executable to the jar on Windows.  Although this is just another
     * form of statically linking a small piece of the JVM to the
     * application, we choose to continue to support it.  Note that no
     * guarantees have been made (or should be made) to the customer that
     * this will continue to work.
     *
     * Therefore, calculate the base offset of the zip file (within the
     * expanded file) by assuming that the central directory is followed
     * immediately by the end record.
     */
    base_offset = base_offset - ENDSIZ(p) - ENDOFF(p);

    /*
     * The END Header indicates the start of the Central Directory
     * Headers. Remember that the desired Central Directory Header (CEN)
     * will almost always be the second one and the first one is a small
     * directory entry ("META-INF/"). Keep the code optimized for
     * that case.
     *
     * Begin by seeking to the beginning of the Central Directory and
     * reading in the first buffer full of bits.
     */
    if (lseek(fd, base_offset + ENDOFF(p), SEEK_SET) < (off_t)0) {
        free(buffer);
	return (-1);
    }
    if ((bytes = read(fd, bp, MINREAD)) < 0) {
        free(buffer);
	return (-1);
    }

    /*
     * Loop through the Central Directory Headers. Note that a valid zip/jar
     * must have an ENDHDR (with ENDSIG) after the Central Directory.
     */
    while (GETSIG(p) == CENSIG) {

	/*
	 * If a complete header isn't in the buffer, shift the contents
	 * of the buffer down and refill the buffer.  Note that the check
	 * for "bytes < CENHDR" must be made before the test for the entire
	 * size of the header, because if bytes is less than CENHDR, the
	 * actual size of the header can't be determined. The addition of
	 * SIGSIZ guarantees that the next signature is also in the buffer
	 * for proper loop termination.
	 */
	if (bytes < CENHDR) {
	    p = memmove(bp, p, bytes);
	    if ((res = read(fd, bp + bytes, MINREAD)) <= 0) {
	      	free(buffer);
		return (-1);
	    }
	    bytes += res;
	}
	entry_size = CENHDR + CENNAM(p) + CENEXT(p) + CENCOM(p);
	if (bytes < entry_size + SIGSIZ) {
	    if (p != bp)
		p = memmove(bp, p, bytes);
	    read_size = entry_size - bytes + SIGSIZ;
	    read_size = (read_size < MINREAD) ? MINREAD : read_size;
	    if ((res = read(fd, bp + bytes,  read_size)) <= 0) {
	      	free(buffer);
		return (-1);
 	    }
	    bytes += res;
	}

	/*
	 * Check if the name is the droid we are looking for; the jar file
	 * manifest.  If so, build the entry record from the data found in
	 * the header located and return success.
	 */
        if (CENNAM(p) == strlen(file_name) &&
          memcmp((p + CENHDR), file_name, strlen(file_name)) == 0) {
	    if (lseek(fd, base_offset + CENOFF(p), SEEK_SET) < (off_t)0) {
    		free(buffer);
		return (-1);
	    }
	    if (read(fd, locbuf, LOCHDR) < 0) {
    		free(buffer);
		return (-1);
	    }
	    if (GETSIG(locbuf) != LOCSIG) {
    		free(buffer);
		return (-1);
	    }
	    entry->isize = CENLEN(p);
	    entry->csize = CENSIZ(p);
	    entry->offset = base_offset + CENOFF(p) + LOCHDR +
		LOCNAM(locbuf) + LOCEXT(locbuf);
	    entry->how = CENHOW(p);
	    free(buffer);
	    return (0);
	}

	/*
	 * Point to the next entry and decrement the count of valid remaining
	 * bytes.
	 */
	bytes -= entry_size;
	p += entry_size;
    }
    free(buffer);
    return (-1);	/* Fell off the end the loop without a Manifest */
}