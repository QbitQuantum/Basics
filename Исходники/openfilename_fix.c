/* MAKE_EXPORT GetSaveFileNameA_fix=GetSaveFileNameA */
BOOL WINAPI GetSaveFileNameA_fix(LPOPENFILENAMEA lpofn)
{
	BOOL ret = GetSaveFileNameA(lpofn);
	if (!ret && CommDlgExtendedError() == CDERR_STRUCTSIZE && lpofn 
		&& lpofn->lStructSize == sizeof(OPENFILENAME))
	{
		lpofn->lStructSize = OPENFILENAME_SIZE_VERSION_400A;
		ret = GetSaveFileNameA(lpofn);
		lpofn->lStructSize = sizeof(OPENFILENAME);
	}
	return ret;
}