ssize_t sendfile(int outfd, int infd, off_t *offset, size_t count)
{
	FAR uint8_t *iobuffer;
	FAR uint8_t *wrbuffer;
	off_t startpos = 0;
	ssize_t nbytesread;
	ssize_t nbyteswritten;
	ssize_t ntransferred;
	bool endxfr;

	/* Get the current file position. */

	if (offset) {
		/* Use lseek to get the current file position */

		startpos = lseek(infd, 0, SEEK_CUR);
		if (startpos == (off_t)-1) {
			return ERROR;
		}

		/* Use lseek again to set the new file position */

		if (lseek(infd, *offset, SEEK_SET) == (off_t)-1) {
			return ERROR;
		}
	}

	/* Allocate an I/O buffer */

	iobuffer = (FAR void *)lib_malloc(CONFIG_LIB_SENDFILE_BUFSIZE);
	if (!iobuffer) {
		set_errno(ENOMEM);
		return ERROR;
	}

	/* Now transfer 'count' bytes from the infd to the outfd */

	for (ntransferred = 0, endxfr = false; ntransferred < count && !endxfr;) {
		/* Loop until the read side of the transfer comes to some conclusion */

		do {
			/* Read a buffer of data from the infd */

			nbytesread = read(infd, iobuffer, CONFIG_LIB_SENDFILE_BUFSIZE);

			/* Check for end of file */

			if (nbytesread == 0) {
				/* End of file.  Break out and return current number of bytes
				 * transferred.
				 */

				endxfr = true;
				break;
			}

			/* Check for a read ERROR.  EINTR is a special case.  This function
			 * should break out and return an error if EINTR is returned and
			 * no data has been transferred.  But what should it do if some
			 * data has been transferred?  I suppose just continue?
			 */

			else if (nbytesread < 0) {
				/* EINTR is not an error (but will still stop the copy) */

#ifndef CONFIG_DISABLE_SIGNALS
				if (errno != EINTR || ntransferred == 0)
#endif
				{
					/* Read error.  Break out and return the error condition. */

					ntransferred = ERROR;
					endxfr = true;
					break;
				}
			}
		} while (nbytesread < 0);

		/* Was anything read? */

		if (!endxfr) {
			/* Yes.. Loop until the read side of the transfer comes to some
			 * conclusion.
			 */

			wrbuffer = iobuffer;
			do {
				/* Write the buffer of data to the outfd */

				nbyteswritten = write(outfd, wrbuffer, nbytesread);

				/* Check for a complete (or parial) write.  write() should not
				 * return zero.
				 */

				if (nbyteswritten >= 0) {
					/* Advance the buffer pointer and decrement the number of bytes
					 * remaining in the iobuffer.  Typically, nbytesread will now
					 * be zero.
					 */

					wrbuffer += nbyteswritten;
					nbytesread -= nbyteswritten;

					/* Increment the total number of bytes successfully transferred. */

					ntransferred += nbyteswritten;
				}

				/* Otherwise an error occurred */

				else {
					/* Check for a read ERROR.  EINTR is a special case.  This
					 * function should break out and return an error if EINTR
					 * is returned and no data has been transferred.  But what
					 * should it do if some data has been transferred?  I
					 * suppose just continue?
					 */

#ifndef CONFIG_DISABLE_SIGNALS
					if (errno != EINTR || ntransferred == 0)
#endif
					{
						/* Write error.  Break out and return the error condition */

						ntransferred = ERROR;
						endxfr = true;
						break;
					}
				}
			} while (nbytesread > 0);
		}
	}

	/* Release the I/O buffer */

	lib_free(iobuffer);

	/* Return the current file position */

	if (offset) {
		/* Use lseek to get the current file position */

		off_t curpos = lseek(infd, 0, SEEK_CUR);
		if (curpos == (off_t)-1) {
			return ERROR;
		}

		/* Return the current file position */

		*offset = curpos;

		/* Use lseek again to restore the original file position */

		if (lseek(infd, startpos, SEEK_SET) == (off_t)-1) {
			return ERROR;
		}
	}

	/* Finally return the number of bytes actually transferred (or ERROR
	 * if any failure occurred).
	 */

	return ntransferred;
}