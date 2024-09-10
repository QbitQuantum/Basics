int music_add_dir(const char *spath, const char *lpath)
{
	p_fat_info info;
	dword i, count;

	if (spath == NULL || lpath == NULL)
		return -EINVAL;

	count = fat_readdir(lpath, (char *) spath, &info);

	if (count == INVALID)
		return -EBADF;
	for (i = 0; i < count; i++) {
		char sfn[PATH_MAX];
		char lfn[PATH_MAX];
		
		if ((info[i].attr & FAT_FILEATTR_DIRECTORY) > 0) {
			char lpath2[PATH_MAX], spath2[PATH_MAX];

			if (info[i].filename[0] == '.')
				continue;

			SPRINTF_S(lpath2, "%s%s/", lpath, info[i].longname);
			SPRINTF_S(spath2, "%s%s/", spath, info[i].filename);
			music_add_dir(spath2, lpath2);
			continue;
		}

		if (fs_is_music(info[i].filename, info[i].longname) == false)
			continue;

		SPRINTF_S(sfn, "%s%s", spath, info[i].filename);
		SPRINTF_S(lfn, "%s%s", lpath, info[i].longname);
		music_add(sfn, lfn);
	}
	free((void *) info);

	return 0;
}