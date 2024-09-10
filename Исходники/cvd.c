static int cli_untgz(int fd, const char *destdir)
{
	char *path, osize[13], name[101], type;
	char block[TAR_BLOCKSIZE];
	int nbytes, nread, nwritten, in_block = 0, fdd = -1;
	unsigned int size, pathlen = strlen(destdir) + 100 + 5;
	FILE *outfile = NULL;
	STATBUF foo;
	gzFile infile = NULL;


    cli_dbgmsg("in cli_untgz()\n");

    if((fdd = dup(fd)) == -1) {
	cli_errmsg("cli_untgz: Can't duplicate descriptor %d\n", fd);
	return -1;
    }

    if((infile = gzdopen(fdd, "rb")) == NULL) {
	cli_errmsg("cli_untgz: Can't gzdopen() descriptor %d, errno = %d\n", fdd, errno);
	if(FSTAT(fdd, &foo) == 0)
	    close(fdd);
	return -1;
    }

    path = (char *) cli_calloc(sizeof(char), pathlen);
    if(!path) {
	cli_errmsg("cli_untgz: Can't allocate memory for path\n");
	cli_untgz_cleanup(NULL, infile, NULL, fdd);
	return -1;
    }

    while(1) {

	nread = gzread(infile, block, TAR_BLOCKSIZE);

	if(!in_block && !nread)
	    break;

	if(nread != TAR_BLOCKSIZE) {
	    cli_errmsg("cli_untgz: Incomplete block read\n");
	    cli_untgz_cleanup(path, infile, outfile, fdd);
	    return -1;
	}

	if(!in_block) {
	    if (block[0] == '\0')  /* We're done */
		break;

	    strncpy(name, block, 100);
	    name[100] = '\0';

	    if(strchr(name, '/')) {
		cli_errmsg("cli_untgz: Slash separators are not allowed in CVD\n");
		cli_untgz_cleanup(path, infile, outfile, fdd);
		return -1;
	    }

	    snprintf(path, pathlen, "%s"PATHSEP"%s", destdir, name);
	    cli_dbgmsg("cli_untgz: Unpacking %s\n", path);
	    type = block[156];

	    switch(type) {
		case '0':
		case '\0':
		    break;
		case '5':
		    cli_errmsg("cli_untgz: Directories are not supported in CVD\n");
		    cli_untgz_cleanup(path, infile, outfile, fdd);
		    return -1;
		default:
		    cli_errmsg("cli_untgz: Unknown type flag '%c'\n", type);
		    cli_untgz_cleanup(path, infile, outfile, fdd);
		    return -1;
	    }
	    in_block = 1;

	    if(outfile) {
		if(fclose(outfile)) {
		    cli_errmsg("cli_untgz: Cannot close file %s\n", path);
		    outfile = NULL;
		    cli_untgz_cleanup(path, infile, outfile, fdd);
		    return -1;
		}
		outfile = NULL;
	    }

	    if(!(outfile = fopen(path, "wb"))) {
		cli_errmsg("cli_untgz: Cannot create file %s\n", path);
		cli_untgz_cleanup(path, infile, outfile, fdd);
		return -1;
	    }

	    strncpy(osize, block + 124, 12);
	    osize[12] = '\0';

	    if((sscanf(osize, "%o", &size)) == 0) {
		cli_errmsg("cli_untgz: Invalid size in header\n");
		cli_untgz_cleanup(path, infile, outfile, fdd);
		return -1;
	    }

	} else { /* write or continue writing file contents */
	    nbytes = size > TAR_BLOCKSIZE ? TAR_BLOCKSIZE : size;
	    nwritten = fwrite(block, 1, nbytes, outfile);

	    if(nwritten != nbytes) {
		cli_errmsg("cli_untgz: Wrote %d instead of %d (%s)\n", nwritten, nbytes, path);
		cli_untgz_cleanup(path, infile, outfile, fdd);
		return -1;
	    }

	    size -= nbytes;
	    if(size == 0)
		in_block = 0;
	}
    }

    cli_untgz_cleanup(path, infile, outfile, fdd);
    return 0;
}