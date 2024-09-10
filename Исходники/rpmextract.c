/*
 * explode source RPM into the current directory
 * use filters to skip packages and files we do not need
 */
int explodeRPM(const char *source,
        filterfunc filter,
        dependencyfunc provides,
        dependencyfunc deps,
        void* userptr)
{
    char buffer[BUFFERSIZE+1]; /* make space for trailing \0 */
    FD_t fdi;
    Header h;
    char * rpmio_flags = NULL;
    rpmRC rc;
    FD_t gzdi;
    struct archive *cpio;
    struct archive_entry *cpio_entry;
    struct cpio_mydata cpio_mydata;

    rpmts ts;
    rpmVSFlags vsflags;
    const char *compr;

    if (strcmp(source, "-") == 0)
        fdi = fdDup(STDIN_FILENO);
    else
        fdi = Fopen(source, "r.ufdio");

    if (Ferror(fdi)) {
        const char *srcname = (strcmp(source, "-") == 0) ? "<stdin>" : source;
        logMessage(ERROR, "%s: %s\n", srcname, Fstrerror(fdi));
        return EXIT_FAILURE;
    }
    rpmReadConfigFiles(NULL, NULL);

    /* Initialize RPM transaction */
    ts = rpmtsCreate();
    vsflags = 0;

    /* Do not check digests, signatures or headers */
    vsflags |= _RPMVSF_NODIGESTS;
    vsflags |= _RPMVSF_NOSIGNATURES;
    vsflags |= RPMVSF_NOHDRCHK;
    (void) rpmtsSetVSFlags(ts, vsflags);

    rc = rpmReadPackageFile(ts, fdi, "rpm2dir", &h);

    ts = rpmtsFree(ts);

    switch (rc) {
        case RPMRC_OK:
        case RPMRC_NOKEY:
        case RPMRC_NOTTRUSTED:
            break;
        case RPMRC_NOTFOUND:
            logMessage(ERROR, "%s is not an RPM package", source);
            return EXIT_FAILURE;
            break;
        case RPMRC_FAIL:
        default:
            logMessage(ERROR, "error reading header from %s package\n", source);
            return EXIT_FAILURE;
            break;
    }

    /* Retrieve all dependencies and run them through deps function */
    while (deps) {
        struct rpmtd_s td;
        const char *depname;

        if (!headerGet(h, RPMTAG_REQUIRENAME, &td, HEADERGET_MINMEM))
            break;

        /* iterator */
        while ((depname = rpmtdNextString(&td))) {
            if (deps(depname, userptr)) {
                Fclose(fdi);
                return EXIT_BADDEPS;
            }
        }
        rpmtdFreeData(&td);
        break;
    }

    /* Retrieve all provides and run them through provides function */
    while (provides) {
        struct rpmtd_s td;
        const char *depname;
        int found = 0;

        if (!headerGet(h, RPMTAG_PROVIDES, &td, HEADERGET_MINMEM))
            break;

        /* iterator */
        while ((depname = rpmtdNextString(&td))) {
            if (!provides(depname, userptr)) {
                found++;
            }
        }
        rpmtdFreeData(&td);
        if (found<=0)
            return EXIT_BADDEPS;
        break;
    }

    /* Retrieve type of payload compression. */
    compr = headerGetString(h, RPMTAG_PAYLOADCOMPRESSOR);
    if (compr && strcmp(compr, "gzip")) {
        checked_asprintf(&rpmio_flags, "r.%sdio", compr);
    }
    else {
        checked_asprintf(&rpmio_flags, "r.gzdio");
    }

    /* Open uncompressed cpio stream */
    gzdi = Fdopen(fdi, rpmio_flags);
    free(rpmio_flags);

    if (gzdi == NULL) {
        logMessage(ERROR, "cannot re-open payload: %s\n", Fstrerror(gzdi));
        return EXIT_FAILURE;
    }

    /* initialize cpio decompressor */
    cpio = archive_read_new();
    if (cpio==NULL) {
        Fclose(gzdi);
        return -1;
    }

    cpio_mydata.gzdi = gzdi;
    cpio_mydata.buffer = buffer;
    archive_read_support_compression_all(cpio);
    archive_read_support_format_all(cpio);
    rc = archive_read_open(cpio, &cpio_mydata, NULL, rpm_myread, rpm_myclose);

    /* check the status of archive_open */
    if (rc != ARCHIVE_OK){
        Fclose(gzdi);
        return -1;
    }

    /* read all files in cpio archive */
    while ((rc = archive_read_next_header(cpio, &cpio_entry)) == ARCHIVE_OK){
        const struct stat *fstat;
        int64_t fsize;
        const char* filename;
        int needskip = 1; /* do we need to read the data to get to the next header? */
        int offset = 0;
        int towrite = 0;

        filename = archive_entry_pathname(cpio_entry);
        fstat = archive_entry_stat(cpio_entry);
        fsize = archive_entry_size(cpio_entry);

        /* Strip leading slashes */
        while (filename[offset] == '/')
            offset+=1;

        /* Strip leading ./ */
        while (filename[offset] == '.' && filename[offset+1] == '/')
            offset+=2;

        /* Other file type - we do not care except special cases */
        if (!S_ISREG(fstat->st_mode))
            towrite = 1;
        else
            towrite = 2;

        if (filter && filter(filename+offset, fstat, userptr)) {
            /* filter this file */
            towrite = 0;
        }

        /* Create directories */
        char* dirname = strdup(filename+offset);

        /* If the dup fails, let's hope the dirs already exist */
        if (dirname){
            char* dirptr = dirname;
            while (dirptr && *dirptr) {
                dirptr = strchr(dirptr, '/');
                if (dirptr) {
                    *dirptr = 0;
                    mkdir(dirname, 0700);
                    *dirptr = '/';
                    dirptr++;
                }
            }
            free(dirname);
        }

        /* Regular file */
        if (towrite>=2) {
            FILE *fdout = fopen(filename+offset, "w");

            if (fdout==NULL){
                rc = 33;
                break;
            }
            
            rc = archive_read_data_into_fd(cpio, fileno(fdout));
            if (rc!=ARCHIVE_OK) {
                /* XXX We didn't get the file.. well.. */
                needskip = 0;
            } else {
                needskip = 0;
                fclose(fdout);
            }
        }

        /* symlink, we assume that the path contained in symlink
         * is shorter than BUFFERSIZE */
        while (towrite && S_ISLNK(fstat->st_mode)) {
            char symlinkbuffer[BUFFERSIZE-1];

            needskip = 0;
            if ((rc = archive_read_data(cpio, symlinkbuffer, fsize))!=ARCHIVE_OK) {
                /* XXX We didn't get the file.. well.. */
                break;
            }

            if (symlink(buffer, filename+offset)) {
                logMessage(ERROR, "Failed to create symlink %s -> %s", filename+offset, buffer);
            }

            break;
        }

        if(needskip)
            archive_read_data_skip(cpio);
    }

    archive_read_finish(cpio);

    return rc != ARCHIVE_OK;
}