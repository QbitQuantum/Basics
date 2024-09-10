CDumpContext& AFXAPI operator <<(CDumpContext& dc, CTime time)
{
	char psz[32];
	psz[0] = '\0';

	__time64_t tmp = time.GetTime();
	errno_t err = _ctime64_s(psz, sizeof(psz), &tmp);

	if ((err != 0) || (psz[0] == '\0') || (time.GetTime() == 0))
	{
		return dc << "CTime(invalid #" << time.GetTime() << ")";
	}

	// format it
	return dc << "CTime(\"" << psz << "\")";
}