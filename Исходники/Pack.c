static rpmRC writeRPM(Header *hdrp, unsigned char ** pkgidp, const char *fileName,
	     CSA_t csa, char **cookie)
{
    FD_t fd = NULL;
    FD_t ifd = NULL;
    ssize_t count;
    char * sigtarget = NULL;;
    char * rpmio_flags = NULL;
    char * SHA1 = NULL;
    const char *s;
    char *buf = NULL;
    Header h;
    Header sig = NULL;
    int xx;
    rpmRC rc = RPMRC_OK;
    struct rpmtd_s td;
    rpmTagVal sizetag;
    rpmTagVal payloadtag;

    /* Transfer header reference form *hdrp to h. */
    h = headerLink(*hdrp);
    *hdrp = headerFree(*hdrp);

    if (pkgidp)
	*pkgidp = NULL;

    /* Save payload information */
    if (headerIsSource(h))
	rpmio_flags = rpmExpand("%{?_source_payload}", NULL);
    else 
	rpmio_flags = rpmExpand("%{?_binary_payload}", NULL);

    if (!(rpmio_flags && *rpmio_flags)) {
	rpmio_flags = _free(rpmio_flags);
	rpmio_flags = xstrdup("w9.gzdio");
    }
    s = strchr(rpmio_flags, '.');
    if (s) {
	const char *compr = NULL;
	headerPutString(h, RPMTAG_PAYLOADFORMAT, "cpio");

	if (rstreq(s+1, "ufdio")) {
	    compr = NULL;
	} else if (rstreq(s+1, "gzdio")) {
	    compr = "gzip";
#if HAVE_BZLIB_H
	} else if (rstreq(s+1, "bzdio")) {
	    compr = "bzip2";
	    /* Add prereq on rpm version that understands bzip2 payloads */
	    (void) rpmlibNeedsFeature(h, "PayloadIsBzip2", "3.0.5-1");
#endif
#if HAVE_LZMA_H
	} else if (rstreq(s+1, "xzdio")) {
	    compr = "xz";
	    (void) rpmlibNeedsFeature(h, "PayloadIsXz", "5.2-1");
	} else if (rstreq(s+1, "lzdio")) {
	    compr = "lzma";
	    (void) rpmlibNeedsFeature(h, "PayloadIsLzma", "4.4.6-1");
#endif
	} else {
	    rpmlog(RPMLOG_ERR, _("Unknown payload compression: %s\n"),
		   rpmio_flags);
	    rc = RPMRC_FAIL;
	    goto exit;
	}

	if (compr)
	    headerPutString(h, RPMTAG_PAYLOADCOMPRESSOR, compr);
	buf = xstrdup(rpmio_flags);
	buf[s - rpmio_flags] = '\0';
	headerPutString(h, RPMTAG_PAYLOADFLAGS, buf+1);
	free(buf);
    }

    /* Create and add the cookie */
    if (cookie) {
	rasprintf(cookie, "%s %d", buildHost(), (int) (*getBuildTime()));
	headerPutString(h, RPMTAG_COOKIE, *cookie);
    }
    
    /* Reallocate the header into one contiguous region. */
    h = headerReload(h, RPMTAG_HEADERIMMUTABLE);
    if (h == NULL) {	/* XXX can't happen */
	rc = RPMRC_FAIL;
	rpmlog(RPMLOG_ERR, _("Unable to create immutable header region.\n"));
	goto exit;
    }
    /* Re-reference reallocated header. */
    *hdrp = headerLink(h);

    /*
     * Write the header+archive into a temp file so that the size of
     * archive (after compression) can be added to the header.
     */
    fd = rpmMkTempFile(NULL, &sigtarget);
    if (fd == NULL || Ferror(fd)) {
	rc = RPMRC_FAIL;
	rpmlog(RPMLOG_ERR, _("Unable to open temp file.\n"));
	goto exit;
    }

    fdInitDigest(fd, PGPHASHALGO_SHA1, 0);
    if (headerWrite(fd, h, HEADER_MAGIC_YES)) {
	rc = RPMRC_FAIL;
	rpmlog(RPMLOG_ERR, _("Unable to write temp header\n"));
    } else { /* Write the archive and get the size */
	(void) Fflush(fd);
	fdFiniDigest(fd, PGPHASHALGO_SHA1, (void **)&SHA1, NULL, 1);
	if (csa->cpioList != NULL) {
	    rc = cpio_doio(fd, h, csa, rpmio_flags);
	} else if (Fileno(csa->cpioFdIn) >= 0) {
	    rc = cpio_copy(fd, csa);
	} else {
	    rc = RPMRC_FAIL;
	    rpmlog(RPMLOG_ERR, _("Bad CSA data\n"));
	}
    }

    if (rc != RPMRC_OK)
	goto exit;

    (void) Fclose(fd);
    fd = NULL;
    (void) unlink(fileName);

    /* Generate the signature */
    (void) fflush(stdout);
    sig = rpmNewSignature();

    /*
     * There should be rpmlib() dependency on this, but that doesn't
     * really do much good as these are signature tags that get read
     * way before dependency checking has a chance to figure out anything.
     * On the positive side, not inserting the 32bit tag at all means
     * older rpm will just bail out with error message on attempt to read
     * such a package.
     */
    if (csa->cpioArchiveSize < UINT32_MAX) {
	sizetag = RPMSIGTAG_SIZE;
	payloadtag = RPMSIGTAG_PAYLOADSIZE;
    } else {
	sizetag = RPMSIGTAG_LONGSIZE;
	payloadtag = RPMSIGTAG_LONGARCHIVESIZE;
    }
    (void) rpmGenDigest(sig, sigtarget, sizetag);
    (void) rpmGenDigest(sig, sigtarget, RPMSIGTAG_MD5);

    if (SHA1) {
	/* XXX can't use rpmtdFromFoo() on RPMSIGTAG_* items */
	rpmtdReset(&td);
	td.tag = RPMSIGTAG_SHA1;
	td.type = RPM_STRING_TYPE;
	td.data = SHA1;
	td.count = 1;
	headerPut(sig, &td, HEADERPUT_DEFAULT);
	SHA1 = _free(SHA1);
    }

    {	
	/* XXX can't use headerPutType() on legacy RPMSIGTAG_* items */
	rpmtdReset(&td);
	td.tag = payloadtag;
	td.count = 1;
	if (payloadtag == RPMSIGTAG_PAYLOADSIZE) {
	    rpm_off_t asize = csa->cpioArchiveSize;
	    td.type = RPM_INT32_TYPE;
	    td.data = &asize;
	    headerPut(sig, &td, HEADERPUT_DEFAULT);
	} else {
	    rpm_loff_t asize = csa->cpioArchiveSize;
	    td.type = RPM_INT64_TYPE;
	    td.data = &asize;
	    headerPut(sig, &td, HEADERPUT_DEFAULT);
	}
    }

    /* Reallocate the signature into one contiguous region. */
    sig = headerReload(sig, RPMTAG_HEADERSIGNATURES);
    if (sig == NULL) {	/* XXX can't happen */
	rc = RPMRC_FAIL;
	rpmlog(RPMLOG_ERR, _("Unable to reload signature header.\n"));
	goto exit;
    }

    /* Open the output file */
    fd = Fopen(fileName, "w.ufdio");
    if (fd == NULL || Ferror(fd)) {
	rc = RPMRC_FAIL;
	rpmlog(RPMLOG_ERR, _("Could not open %s: %s\n"),
		fileName, Fstrerror(fd));
	goto exit;
    }

    /* Write the lead section into the package. */
    {	
	rpmlead lead = rpmLeadFromHeader(h);
	rc = rpmLeadWrite(fd, lead);
	lead = rpmLeadFree(lead);
	if (rc != RPMRC_OK) {
	    rc = RPMRC_FAIL;
	    rpmlog(RPMLOG_ERR, _("Unable to write package: %s\n"),
		 Fstrerror(fd));
	    goto exit;
	}
    }

    /* Write the signature section into the package. */
    if (rpmWriteSignature(fd, sig)) {
	rc = RPMRC_FAIL;
	goto exit;
    }

    /* Append the header and archive */
    ifd = Fopen(sigtarget, "r.ufdio");
    if (ifd == NULL || Ferror(ifd)) {
	rc = RPMRC_FAIL;
	rpmlog(RPMLOG_ERR, _("Unable to open sigtarget %s: %s\n"),
		sigtarget, Fstrerror(ifd));
	goto exit;
    }

    /* Add signatures to header, and write header into the package. */
    /* XXX header+payload digests/signatures might be checked again here. */
    {	Header nh = headerRead(ifd, HEADER_MAGIC_YES);

	if (nh == NULL) {
	    rc = RPMRC_FAIL;
	    rpmlog(RPMLOG_ERR, _("Unable to read header from %s: %s\n"),
			sigtarget, Fstrerror(ifd));
	    goto exit;
	}

#ifdef	NOTYET
	(void) headerMergeLegacySigs(nh, sig);
#endif

	xx = headerWrite(fd, nh, HEADER_MAGIC_YES);
	nh = headerFree(nh);

	if (xx) {
	    rc = RPMRC_FAIL;
	    rpmlog(RPMLOG_ERR, _("Unable to write header to %s: %s\n"),
			fileName, Fstrerror(fd));
	    goto exit;
	}
    }
	
    /* Write the payload into the package. */
    buf = xmalloc(BUFSIZ);
    while ((count = Fread(buf, 1, BUFSIZ, ifd)) > 0) {
	if (count == -1) {
	    free(buf);
	    rc = RPMRC_FAIL;
	    rpmlog(RPMLOG_ERR, _("Unable to read payload from %s: %s\n"),
		     sigtarget, Fstrerror(ifd));
	    goto exit;
	}
	if (Fwrite(buf, sizeof(buf[0]), count, fd) != count) {
	    free(buf);
	    rc = RPMRC_FAIL;
	    rpmlog(RPMLOG_ERR, _("Unable to write payload to %s: %s\n"),
		     fileName, Fstrerror(fd));
	    goto exit;
	}
    }
    free(buf);
    rc = RPMRC_OK;

exit:
    rpmio_flags = _free(rpmio_flags);
    SHA1 = _free(SHA1);
    h = headerFree(h);

    /* XXX Fish the pkgid out of the signature header. */
    if (sig != NULL && pkgidp != NULL) {
	struct rpmtd_s md5tag;
	headerGet(sig, RPMSIGTAG_MD5, &md5tag, HEADERGET_DEFAULT);
	if (rpmtdType(&md5tag) == RPM_BIN_TYPE &&
	    			md5tag.count == 16 && md5tag.data != NULL) {
	    *pkgidp = md5tag.data;
	}
    }

    sig = rpmFreeSignature(sig);
    if (ifd) {
	(void) Fclose(ifd);
	ifd = NULL;
    }
    if (fd) {
	(void) Fclose(fd);
	fd = NULL;
    }
    if (sigtarget) {
	(void) unlink(sigtarget);
	sigtarget = _free(sigtarget);
    }

    if (rc == RPMRC_OK)
	rpmlog(RPMLOG_NOTICE, _("Wrote: %s\n"), fileName);
    else
	(void) unlink(fileName);

    return rc;
}