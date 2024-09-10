rpmRC
rpmVerifySignature(rpmKeyring keyring, rpmtd sigtd, pgpDigParams sig,
		   DIGEST_CTX ctx, char ** result)
{
    rpmRC res = RPMRC_NOTFOUND;
    char *msg = NULL;
    int hdrsig = 0;

    if (sigtd->data == NULL || sigtd->count <= 0 || ctx == NULL)
	goto exit;

    switch (sigtd->tag) {
    case RPMSIGTAG_MD5:
	res = verifyMD5Digest(sigtd, ctx, &msg);
	break;
    case RPMSIGTAG_SHA1:
	res = verifySHA1Digest(sigtd, ctx, &msg);
	break;
    case RPMSIGTAG_RSA:
    case RPMSIGTAG_DSA:
	hdrsig = 1;
	/* fallthrough */
    case RPMSIGTAG_PGP5:	/* XXX legacy */
    case RPMSIGTAG_PGP:
    case RPMSIGTAG_GPG:
	if (sig != NULL)
	    res = verifySignature(keyring, sig, ctx, hdrsig, &msg);
	break;
    default:
	break;
    }

exit:
    if (res == RPMRC_NOTFOUND) {
	rasprintf(&msg,
		  _("Verify signature: BAD PARAMETERS (%d %p %d %p %p)\n"),
		  sigtd->tag, sigtd->data, sigtd->count, ctx, sig);
	res = RPMRC_FAIL;
    }

    if (result) {
	*result = msg;
    } else {
	free(msg);
    }
    return res;
}