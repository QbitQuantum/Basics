bool create_bob_txt()
{
	// current directory 를 구한다.
	wchar_t *buf=NULL;
	uint32_t buflen = 0;
	buflen = GetCurrentDirectoryW(buflen, buf);
	if (0 == buflen)
	{
		print("err, GetCurrentDirectoryW() failed. gle = 0x%08x", GetLastError());
		return false;
	}

	buf = (PWSTR) malloc(sizeof(WCHAR) * buflen);
	if (0 == GetCurrentDirectoryW(buflen, buf))
	{
		print("err, GetCurrentDirectoryW() failed. gle = 0x%08x", GetLastError());
		free(buf);
		return false;
	}

	// current dir \\ bob.txt 파일명 생성
	wchar_t file_name[260];
	if (!SUCCEEDED(StringCbPrintfW(
		file_name,
		sizeof(file_name),
		L"%ws\\bob.txt",
		buf)))
	{  
		print("err, can not create file name");
		free(buf);
		return false;
	}


	if (true == is_file_existsW(file_name))
	{
		::DeleteFileW(file_name);
	}

	// 파일 생성
	HANDLE file_handle = CreateFileW(
		file_name,
		GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		CREATE_NEW,
		FILE_ATTRIBUTE_NORMAL,
		NULL); 

	if(file_handle == INVALID_HANDLE_VALUE)
	{                                              
		print("err, CreateFile(path=%ws), gle=0x%08x", file_name, GetLastError());
		return false;
	}


	// 파일에 데이터 쓰기
	DWORD bytes_written = 0;
	wchar_t string_buf[1024];
	if (!SUCCEEDED(StringCbPrintfW(
		string_buf,
		sizeof(string_buf),
		L"동해물과 백두산이 마르고 닳도록 하느님이 보우하사 우리나라만세")))
	{
		print("err, can not create data to write.");
		CloseHandle(file_handle);
		return false;
	}
	char *pUtf8 =NULL;
	int len = UnicodeToUtf8(string_buf,&pUtf8);

	if (!WriteFile(file_handle, pUtf8, len, &bytes_written, NULL))
	{
		print("err, WriteFile() failed. gle = 0x%08x", GetLastError());
		CloseHandle(file_handle);
		return false;
	}

	// 영어로 쓰기
	if (!SUCCEEDED(StringCbPrintfW(
		string_buf,
		sizeof(string_buf),
		L"All work and no play makes jack a dull boy.")))
	{
		print("err, can not create data to write.");
		CloseHandle(file_handle);
		return false;
	}

	free(pUtf8);

	*pUtf8 =NULL;
	len = UnicodeToUtf8(string_buf,&pUtf8);

	if (!WriteFile(file_handle, string_buf, wcslen(string_buf), &bytes_written, NULL))
	{
		print("err, WriteFile() failed. gle = 0x%08x", GetLastError());
		CloseHandle(file_handle);
		return false;
	}




	char string_bufa[1024];


	if (!SUCCEEDED(StringCbPrintfA(
		string_bufa,
		sizeof(string_bufa),
		"동해물과 백두산이 마르고 닳도록 하느님이 보우하사 우리나라만세")))
	{
		print("err, can not create data to write.");
		CloseHandle(file_handle);
		return false;
	}

	free(pUtf8);

	pUtf8 =NULL;
	pUtf8 =ANSIToUTF8(string_bufa);
	len = strlen(pUtf8);


	if (!WriteFile(file_handle, pUtf8, len, &bytes_written, NULL))
	{
		print("err, WriteFile() failed. gle = 0x%08x", GetLastError());
		CloseHandle(file_handle);
		return false;
	}

	// 영어로 쓰기
	if (!SUCCEEDED(StringCbPrintfA(
		string_bufa,
		sizeof(string_bufa),
		"All work and no play makes jack a dull boy.")))
	{
		print("err, can not create data to write.");
		CloseHandle(file_handle);
		return false;
	}

	free(pUtf8);

	pUtf8 =NULL;
	pUtf8 =ANSIToUTF8(string_bufa);
	len = strlen(pUtf8);


	if (!WriteFile(file_handle, string_bufa, strlen(string_bufa), &bytes_written, NULL))
	{
		print("err, WriteFile() failed. gle = 0x%08x", GetLastError());
		CloseHandle(file_handle);
		return false;
	}

	free(pUtf8);

	// 파일 닫기
	CloseHandle(file_handle);

	wchar_t copy_file_name[260];

	if (!SUCCEEDED(StringCbPrintfW(
		copy_file_name,
		sizeof(copy_file_name),
		L"%ws\\bob2.txt",
		buf)))
	{  
		print("err, can not copy file name");
		free(buf);
		return false;
	}
	free(buf); buf = NULL;

	/* BOB.txt -> BOB2.txt 파일 복사 */
	if(!CopyFileW(file_name,copy_file_name,false)){
		print("CopyFileW fail");
		return false;
	}


	/* ReadFile()을 통한 읽기 후 출력*/

	HANDLE read_file_handle = CreateFileW(
		copy_file_name,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		0,
		NULL); 

	if(read_file_handle == INVALID_HANDLE_VALUE)
	{                                              
		print("err, CreateFile(path=%ws), gle=0x%08x", read_file_handle, GetLastError());
		return false;
	}

	char read_buf[512];
	char buf_noNull[512];
	char* ansi_buf;

	DWORD result=0;
	
	ReadFile(read_file_handle,read_buf,sizeof(char)*512,&result,NULL);
	
	// read_buf의 글자 사이사이에 있는 NULL값 제거 ( UTF8ToANSI 에서  strlen을 사용하기 때문)
	int j=0;
	for(int i=0;i<256;i++){
		if(read_buf[i] != '\0'){
			buf_noNull[j++] = read_buf[i]; 
		}
	}
	buf_noNull[j]='\0';
	
	// 출력
	ansi_buf=UTF8ToANSI(buf_noNull);
	printf("%s\n",ansi_buf);

	CloseHandle(read_file_handle);


	/* MMIO()을 통한 읽기 후 출력*/

	read_file_handle = CreateFileW(
		copy_file_name,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		0,
		NULL); 

	if(read_file_handle == INVALID_HANDLE_VALUE)
	{                                              
		print("err, CreateFile(path=%ws), gle=0x%08x", read_file_handle, GetLastError());
		return false;
	}


	HANDLE file_map = CreateFileMapping(
                            read_file_handle,
                            NULL,
                            PAGE_READONLY,
                            0,
                            0,
                            NULL
                            );
    if (NULL == file_map)
    {
        print("err, CreateFileMapping(%ws) failed, gle = %u", file_name, GetLastError());
        CloseHandle(read_file_handle);
        return false;
    }
 
    PCHAR file_view = (PCHAR) MapViewOfFile(
                                    file_map,
                                    FILE_MAP_READ,
                                    0,
                                    0,
                                    0
                                    );
    if(file_view == NULL)
    {
        print("err, MapViewOfFile(%ws) failed, gle = %u", file_name, GetLastError());
       
        CloseHandle(file_map);
        CloseHandle(read_file_handle);
        return false;
    }

	// read_buf의 글자 사이사이에 있는 NULL값 제거 ( UTF8ToANSI 에서  strlen을 사용하기 때문)
	
	j=0;
	for(int i=0;i<256;i++){
		if(read_buf[i] != '\0'){
			buf_noNull[j++] = file_view[i]; 
		}
	}
	buf_noNull[j]='\0';
	
	// 출력
	ansi_buf=UTF8ToANSI(buf_noNull);
	printf("%s\n",ansi_buf);


	UnmapViewOfFile(file_view);
    CloseHandle(file_map);
	CloseHandle(read_file_handle);

	/* BOB.txt 파일 삭제*/



	::DeleteFileW(file_name);

	return true;

}