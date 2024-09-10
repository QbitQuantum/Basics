/*
 * Open a stdio stream, handling special filenames
 */
FILE *zopen(const char *name, const char *mode)
{
    char command[MAXPATHLEN + 100];

    if (stdio_filename_p(name)) {
	/*
	 * Return stream to stdin or stdout
	 */
	if (*mode == 'r') {
		static int stdin_used = 0;
		static int stdin_warning = 0;
		int fd;

		if (stdin_used) {
		    if (!stdin_warning) {
			fprintf(stderr,
				"warning: '-' used multiple times for input\n");
			stdin_warning = 1;
		    }
		} else {
		    stdin_used = 1;
		}
#ifdef _MSC_VER
		fd = _dup(0);
		return fd < 0 ? NULL : _fdopen(fd, mode);
#else
        fd = dup(0);
		return fd < 0 ? NULL : fdopen(fd, mode);
#endif
	} else if (*mode == 'w' || *mode == 'a') {
		static int stdout_used = 0;
		static int stdout_warning = 0;
		int fd;

		if (stdout_used) {
		    if (!stdout_warning) {
			fprintf(stderr,
				"warning: '-' used multiple times for output\n");
			stdout_warning = 1;
		    }
		} else {
		    stdout_used = 1;
		}
#ifdef _MSC_VER
		fd = _dup(1);
		return fd < 0 ? NULL : _fdopen(fd, mode);
#else
		fd = dup(1);
		return fd < 0 ? NULL : fdopen(fd, mode);
#endif
	} else {
		return NULL;
	}
    } else {
	char *compress_cmd = NULL;
	char *uncompress_cmd = NULL;
	int zip_to_stdout = 1;
	
	if (compressed_filename_p(name)) {
	    compress_cmd = COMPRESS_CMD;
	    uncompress_cmd = UNCOMPRESS_CMD;
	} else if (gzipped_filename_p(name)) {
	    compress_cmd = GZIP_CMD;
	    uncompress_cmd = GUNZIP_CMD;
	} else if (bzipped_filename_p(name)) {
	    compress_cmd = BZIP2_CMD;
	    uncompress_cmd = BUNZIP2_CMD;
	} else if (sevenzipped_filename_p(name)) {
	    compress_cmd = SEVENZIP_CMD;
	    uncompress_cmd = SEVENUNZIP_CMD;
	    zip_to_stdout = 0;
	} else if (xz_filename_p(name)) {
	    compress_cmd = XZ_CMD;
	    uncompress_cmd = XZ_DECOMPRESS_CMD;
	}

	if (compress_cmd != NULL) {
#ifdef NO_ZIO
	    fprintf(stderr, "Sorry, compressed I/O not available on this machine\n");
	    errno = EINVAL;
	    return NULL;
#else /* !NO_ZIO */
	    /*
	     * Return stream to compress pipe
	     */
	    if (*mode == 'r') {
		if (!readable_p(name))
		    return NULL;
		sprintf(command, "%s;%s %s", STD_PATH, uncompress_cmd, name);
		return popen(command, mode);
	    } else if (*mode == 'w') {
		if (!writable_p(name))
		    return NULL;
		if (zip_to_stdout) {
		    sprintf(command, "%s;%s >%s", STD_PATH, compress_cmd, name);
		} else {
		    /*
		     * This is necessary because the compression program might
		     * complain if a zero-length file already exists.
		     * However, it means that existing file owner & permission
		     * attributes are not preserved.
		     */
		    unlink(name);
		    sprintf(command, "%s;%s %s", STD_PATH, compress_cmd, name);
		}
		return popen(command, mode);
	    } else {
		return NULL;
	    }
#endif /* !NO_ZIO */
	} else {
	    return fopen(name, mode);
	}
    }
}