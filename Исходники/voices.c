static void GetVoices(const char *path)
{
	FILE *f_voice;
	espeak_VOICE *voice_data;
	int ftype;
	char fname[sizeof(path_home)+100];

#ifdef PLATFORM_WINDOWS
	WIN32_FIND_DATAA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	#undef UNICODE // we need FindFirstFileA() which takes an 8-bit c-string
	sprintf(fname, "%s\\*", path);
	hFind = FindFirstFileA(fname, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
		return;

	do {
		if (n_voices_list >= (N_VOICES_LIST-2))
			break; // voices list is full

		if (FindFileData.cFileName[0] != '.') {
			sprintf(fname, "%s%c%s", path, PATHSEP, FindFileData.cFileName);
			ftype = GetFileLength(fname);

			if (ftype == -2) {
				// a sub-sirectory
				GetVoices(fname);
			} else if (ftype > 0) {
				// a regular line, add it to the voices list
				if ((f_voice = fopen(fname, "r")) == NULL)
					continue;

				// pass voice file name within the voices directory
				voice_data = ReadVoiceFile(f_voice, fname+len_path_voices, FindFileData.cFileName);
				fclose(f_voice);

				if (voice_data != NULL)
					voices_list[n_voices_list++] = voice_data;
			}
		}
	} while (FindNextFileA(hFind, &FindFileData) != 0);
	FindClose(hFind);
#else
	DIR *dir;
	struct dirent *ent;

	if ((dir = opendir((char *)path)) == NULL) // note: (char *) is needed for WINCE
		return;

	while ((ent = readdir(dir)) != NULL) {
		if (n_voices_list >= (N_VOICES_LIST-2))
			break; // voices list is full

		if (ent->d_name[0] == '.')
			continue;

		sprintf(fname, "%s%c%s", path, PATHSEP, ent->d_name);

		ftype = GetFileLength(fname);

		if (ftype == -2) {
			// a sub-sirectory
			GetVoices(fname);
		} else if (ftype > 0) {
			// a regular line, add it to the voices list
			if ((f_voice = fopen(fname, "r")) == NULL)
				continue;

			// pass voice file name within the voices directory
			voice_data = ReadVoiceFile(f_voice, fname+len_path_voices, ent->d_name);
			fclose(f_voice);

			if (voice_data != NULL)
				voices_list[n_voices_list++] = voice_data;
		}
	}
	closedir(dir);
#endif
}