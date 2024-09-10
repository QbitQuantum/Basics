extern dword copy_dir(const char *src, const char *dest, t_copy_cb cb,
					  t_copy_overwritecb ocb, void *data)
{
	int dl = xrIoDopen(src);
	dword result = 0;
	SceIoDirent sid;

	if (dl < 0) {
		if (cb != NULL)
			cb(src, dest, false, data);
		return 0;
	}

	xrIoMkdir(dest, 0777);
	memset(&sid, 0, sizeof(SceIoDirent));

	while (xrIoDread(dl, &sid)) {
		char copysrc[260], copydest[260];

		if (sid.d_name[0] == '.')
			continue;

		SPRINTF_S(copysrc, "%s/%s", src, sid.d_name);
		SPRINTF_S(copydest, "%s/%s", dest, sid.d_name);
		if (FIO_S_ISDIR(sid.d_stat.st_mode)) {
			result += copy_dir(copysrc, copydest, cb, ocb, data);
			continue;
		}
		if (copy_file(copysrc, copydest, cb, ocb, data))
			++result;
		memset(&sid, 0, sizeof(SceIoDirent));
	}
	xrIoDclose(dl);
	return result;
}