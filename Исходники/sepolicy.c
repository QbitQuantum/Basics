static rpmRC sepolWritePolicy(const sepol * pol, char **path)
{
    char *tmppath = NULL;
    FD_t fd = NULL;
    char *policy = NULL;
    size_t policylen;
    rpmRC rc = RPMRC_FAIL;

    if (rpmBase64Decode(pol->data, (void **) &policy, &policylen) != 0) {
	rpmlog(RPMLOG_ERR, _("Failed to decode policy for %s\n"),
	       pol->name);
	goto exit;
    }

    fd = rpmMkTempFile(NULL, &tmppath);
    if (fd == NULL || Ferror(fd)) {
	rpmlog(RPMLOG_ERR, _("Failed to create temporary file for %s: %s\n"),
	       pol->name, strerror(errno));
	goto exit;
    }

    if (!Fwrite(policy, sizeof(*policy), policylen, fd)) {
	rpmlog(RPMLOG_ERR, _("Failed to write %s policy to file %s\n"),
	       pol->name, tmppath);
	goto exit;
    }

    *path = tmppath;
    rc = RPMRC_OK;

  exit:
    if (fd)
	Fclose(fd);
    _free(policy);
    if (rc != RPMRC_OK)
	_free(tmppath);

    return rc;
}