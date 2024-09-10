// pid 프로세스의 모듈 목록을 구한다.
int MyEnumModule98(int pid)
{
	HANDLE hSnap;
	MODULEENTRY32 me;
	char str[256];

	str[0] = 0;

	hSnap=CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,pid);
	if (hSnap == (HANDLE)-1)
		return FALSE;

	me.dwSize=sizeof(MODULEENTRY32);
	//SendMessage(hListMod,LB_RESETCONTENT,0,0);
	if (Module32First(hSnap,&me)) {
		do {
			CharLower( me.szExePath );
			if ( strstr( me.szExePath , MyProcessName )!=0 ) {
				lstrcpy( str , me.szExePath );
			}
			//wsprintf(str,"%s",me.szExePath);
			//SendMessage(hListMod,LB_ADDSTRING,0,(LPARAM)str);
		} while (Module32Next(hSnap,&me));
	}
	CloseHandle(hSnap);

	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	DWORD	*szFileBuff;
	int		cnt;
	int		dCnt;
/*
		FILE *fp;
		fp=fopen( "myproc4.txt","wb" );
		if ( fp ) {
			fwrite( str , lstrlen( str ) , 1, fp );
			fclose(fp);
		}
*/
//	lstrcpy( str , "D:\\game공유\\오픈베타새버전\\game.exe" );
//	lstrcpy( str , "E:\\바이러스걸린실행파일\\game.exe" );
	if ( str[0] ) {
		dwExeCheckSum = 0;
		hFile = CreateFile( str , GENERIC_READ , FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING , FILE_ATTRIBUTE_NORMAL , NULL );
		if ( hFile!=INVALID_HANDLE_VALUE ) {
			FileLength = GetFileSize( hFile , NULL );
			//dCnt = FileLength/4;
			szFileBuff = new DWORD[ (FileLength/4)+256 ];
			ReadFile( hFile , szFileBuff , FileLength , &dwAcess , NULL );
			CloseHandle( hFile );
/*
			dCnt = 1200*1024;
			dCnt /=4;
			if ( dCnt>0x46000 ) dCnt=0x46000;
*/
			dCnt = FileLength-0x8000;
			dCnt /= 4;

			for( cnt=0x1000;cnt<dCnt;cnt++ ) {
				dwExeCheckSum += szFileBuff[cnt]|(cnt*cnt*szFileBuff[cnt]);
				dwExeCheckSum += (szFileBuff[cnt]>>16)+(szFileBuff[cnt]<<16);
			}
			if ( !dwExeCheckSum ) dwExeCheckSum = 1;
			delete szFileBuff;
		}
	}