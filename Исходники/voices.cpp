static void GetVoices(const char *path)
{//====================================
	FILE *f_voice;
	espeak_VOICE *voice_data;
	int ftype;
	char fname[sizeof(path_home)+100];

#ifdef PLATFORM_RISCOS
	int len;
	int *type;
	char *p;
	_kernel_swi_regs regs;
	_kernel_oserror *error;
	char buf[80];
	char directory2[sizeof(path_home)+100];

	regs.r[0] = 10;
	regs.r[1] = (int)path;
	regs.r[2] = (int)buf;
	regs.r[3] = 1;
	regs.r[4] = 0;
	regs.r[5] = sizeof(buf);
	regs.r[6] = 0;

	while(regs.r[3] > 0)
	{
		error = _kernel_swi(0x0c+0x20000,&regs,&regs);      /* OS_GBPB 10, read directory entries */
		if((error != NULL) || (regs.r[3] == 0))
		{
			break;
		}
		type = (int *)(&buf[16]);
		len = strlen(&buf[20]);
		sprintf(fname,"%s.%s",path,&buf[20]);

		if(*type == 2)
		{
			// a sub-directory
			GetVoices(fname);
		}
		else
		{
			// a regular line, add it to the voices list
			if((f_voice = fopen(fname,"r")) == NULL)
				continue;

			// pass voice file name within the voices directory
			voice_data = ReadVoiceFile(f_voice, fname+len_path_voices, &buf[20]);
			fclose(f_voice);

			if(voice_data != NULL)
			{
				voices_list[n_voices_list++] = voice_data;
			}
		}
	}
#else
#ifdef PLATFORM_WINDOWS
	WIN32_FIND_DATAA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;

#undef UNICODE         // we need FindFirstFileA() which takes an 8-bit c-string
	sprintf(fname,"%s\\*",path);
	hFind = FindFirstFileA(fname, &FindFileData);
	if(hFind == INVALID_HANDLE_VALUE)
		return;

	do {
		if(n_voices_list >= (N_VOICES_LIST-2))
			break;   // voices list is full

		if(FindFileData.cFileName[0] != '.')
		{
			sprintf(fname,"%s%c%s",path,PATHSEP,FindFileData.cFileName);
			ftype = GetFileLength(fname);

			if(ftype == -2)
			{
				// a sub-sirectory
				GetVoices(fname);
			}
			else if(ftype > 0)
			{
				// a regular line, add it to the voices list
				if((f_voice = fopen(fname,"r")) == NULL)
					continue;

				// pass voice file name within the voices directory
				voice_data = ReadVoiceFile(f_voice, fname+len_path_voices, FindFileData.cFileName);
				fclose(f_voice);

				if(voice_data != NULL)
				{
					voices_list[n_voices_list++] = voice_data;
				}
			}
		}
	} while(FindNextFileA(hFind, &FindFileData) != 0);
	FindClose(hFind);

#else
	DIR *dir;
	struct dirent *ent;

	if((dir = opendir((char *)path)) == NULL)    // note: (char *) is needed for WINCE
		return;

	while((ent = readdir(dir)) != NULL)
	{
		if(n_voices_list >= (N_VOICES_LIST-2))
			break;   // voices list is full

		if(ent->d_name[0] == '.')
			continue;

		sprintf(fname,"%s%c%s",path,PATHSEP,ent->d_name);

		ftype = GetFileLength(fname);

		if(ftype == -2)
		{
			// a sub-sirectory
			GetVoices(fname);
		}
		else if(ftype > 0)
		{
			// a regular line, add it to the voices list
			if((f_voice = fopen(fname,"r")) == NULL)
				continue;

			// pass voice file name within the voices directory
			voice_data = ReadVoiceFile(f_voice, fname+len_path_voices, ent->d_name);
			fclose(f_voice);

			if(voice_data != NULL)
			{
				voices_list[n_voices_list++] = voice_data;
			}
		}
	}
	closedir(dir);
#endif
#endif
}   // end of GetVoices