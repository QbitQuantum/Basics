static int process_package(rpmts ts, char * filename)
{
    FD_t fdi;
    FD_t gzdi;
    Header h;
    int rc = 0;
    char * rpmio_flags = NULL;
    struct archive *a;
    struct archive_entry *entry;

    if (!strcmp(filename, "-")) {
	fdi = fdDup(STDIN_FILENO);
    } else {
	fdi = Fopen(filename, "r.ufdio");
    }

    if (Ferror(fdi)) {
	fprintf(stderr, "rpm2archive: %s: %s\n",
		filename, Fstrerror(fdi));
	exit(EXIT_FAILURE);
    }

    rc = rpmReadPackageFile(ts, fdi, "rpm2cpio", &h);

    switch (rc) {
    case RPMRC_OK:
    case RPMRC_NOKEY:
    case RPMRC_NOTTRUSTED:
	break;
    case RPMRC_NOTFOUND:
	fprintf(stderr, _("argument is not an RPM package\n"));
	exit(EXIT_FAILURE);
	break;
    case RPMRC_FAIL:
    default:
	fprintf(stderr, _("error reading header from package\n"));
	exit(EXIT_FAILURE);
	break;
    }


    /* Retrieve payload size and compression type. */
    {	const char *compr = headerGetString(h, RPMTAG_PAYLOADCOMPRESSOR);
	rpmio_flags = rstrscat(NULL, "r.", compr ? compr : "gzip", NULL);
    }

    gzdi = Fdopen(fdi, rpmio_flags);	/* XXX gzdi == fdi */
    free(rpmio_flags);

    if (gzdi == NULL) {
	fprintf(stderr, _("cannot re-open payload: %s\n"), Fstrerror(gzdi));
	exit(EXIT_FAILURE);
    }

    rpmfiles files = rpmfilesNew(NULL, h, 0, RPMFI_KEEPHEADER);
    rpmfi fi = rpmfiNewArchiveReader(gzdi, files, RPMFI_ITER_READ_ARCHIVE_CONTENT_FIRST);

    /* create archive */
    a = archive_write_new();
    archive_write_add_filter_gzip(a);
    archive_write_set_format_pax_restricted(a);

    if (!strcmp(filename, "-")) {
	if (isatty(STDOUT_FILENO)) {
	    fprintf(stderr, "Error: refusing to output archive data to a terminal.\n");
	    exit(EXIT_FAILURE);
	}
	archive_write_open_fd(a, STDOUT_FILENO);
    } else {
	char * outname = rstrscat(NULL, filename, ".tgz", NULL);
	archive_write_open_filename(a, outname);
	_free(outname);
	// XXX error handling
    }

    entry = archive_entry_new();

    char * buf = xmalloc(BUFSIZE);
    char * hardlink = NULL;

    rc = 0;
    while (rc >= 0) {
	rc = rpmfiNext(fi);
	if (rc == RPMERR_ITER_END) {
	    break;
	}

	rpm_mode_t mode = rpmfiFMode(fi);
	int nlink = rpmfiFNlink(fi);

	fill_archive_entry(a, entry, fi);

	if (nlink > 1) {
	    if (rpmfiArchiveHasContent(fi)) {
		_free(hardlink);
		hardlink = rstrscat(NULL, ".", rpmfiFN(fi), NULL);
	    } else {
		archive_entry_set_hardlink(entry, hardlink);
	    }
	}

	archive_write_header(a, entry);

	if (S_ISREG(mode) && (nlink == 1 || rpmfiArchiveHasContent(fi))) {
	    write_file_content(a, buf, fi);
	}
    }
    /* End of iteration is not an error */
    if (rc == RPMERR_ITER_END) {
	rc = 0;
    }

    _free(hardlink);

    Fclose(gzdi);	/* XXX gzdi == fdi */
    archive_entry_free(entry);
    archive_write_close(a);
    archive_write_free(a);
    buf = _free(buf);
    rpmfilesFree(files);
    rpmfiFree(fi);
    headerFree(h);
    return rc;
}