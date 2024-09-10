int GetWmaTag(const char *filename, wchar_t *format,char *path)
{

	HANDLE hfile = CreateFile(filename,
			GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL, NULL);

	if (hfile == INVALID_HANDLE_VALUE)
	{
		return -1;
	}

	HANDLE hfilemap = CreateFileMapping(hfile, NULL, PAGE_READONLY, 0, 0, NULL);
	CloseHandle(hfile);

	unsigned char *pfile = (unsigned char*) MapViewOfFile(hfilemap, FILE_MAP_READ, 0, 0, 0);
	CloseHandle(hfilemap);
	if (memcmp( asf_file_guid, pfile, 16) != 0)
	{
		UnmapViewOfFile(pfile);
		return -1;
	}
	long *charStep = setCharStep(asf_tags_guid, 16);
	long answer;
	if ((answer = sundaySearch(pfile, asf_tags_guid, charStep, getFileSize(filename), 16)) >= 0)
	{
		answer += 24;
		struct wma_tags *tag = (struct wma_tags *) & pfile[answer];
		answer += sizeof(struct wma_tags);
		answer += tag->titleLength;
		wchar_t f_name[1024];
		f_name[0]=0;
		while(*format!=0)
		{
			if(*format!=L'%')
			{
				wchar_t temp[20];
				wsprintfW(temp,L"%c",*format);
				wcscat(f_name,temp);
			}
			else
			{
				format++;
				switch(*format)
				{
					//星期
					case 'a':
					case 'A':
						wcscat(f_name,tag->artistLength == 0 ? L"未知歌手" : (wchar_t*)&pfile[answer]);
						break;
					case 't':
					case 'T':
						wcscat(f_name,tag->titleLength == 0 ? L"未知歌曲" : (wchar_t*)&pfile[answer-tag->titleLength]);
						break;
				}
			}
			format++;
		}
		wcscat(f_name,L".wma");
		wchar_t utext[512];
		wchar_t upath[512];
		MultiByteToWideChar(CP_ACP, 0, filename, -1, utext, 512);
		MultiByteToWideChar(CP_ACP, 0, path, -1, upath, 512);
		wcscat(upath,f_name);
		//
		char newpath[1024];
		WideCharToMultiByte( CP_ACP,0,upath,-1,newpath,1024,NULL,NULL );
		mkpathEx(newpath);
		MoveFileW(utext,upath);
	}
	else
	{
		UnmapViewOfFile(pfile);
		return -1;
	}
	UnmapViewOfFile(pfile);
	return 0;
}