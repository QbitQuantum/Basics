static rpmRC
rpmVerifySignature(rpmKeyring keyring, struct rpmsinfo_s *sinfo,
		   DIGEST_CTX ctx, char ** result)
{
    rpmRC res = RPMRC_FAIL;

    if (sinfo->type == RPMSIG_DIGEST_TYPE)
	res = verifyDigest(sinfo, ctx, result);
    else if (sinfo->type == RPMSIG_SIGNATURE_TYPE)
	res = verifySignature(keyring, sinfo, ctx, result);

    return res;
}