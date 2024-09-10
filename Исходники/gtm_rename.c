uint4 gtm_rename(char *org_fn, int org_fn_len, char *rename_fn, int rename_len, uint4 *ustatus)
{
	*ustatus = SS_NORMAL;	/* used in VMS only */
	assert(0 == org_fn[org_fn_len]);
	assert(0 == rename_fn[rename_len]);
	if (-1 == RENAME(org_fn, rename_fn))
		return errno;
	return SS_NORMAL;
}