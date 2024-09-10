//===========================================================================
//ディスクの空き容量を調べる
//===========================================================================
__int64 __fastcall TAttacheCaseFileDecrypt1::GetDiskFreeSpaceNum(String FilePath)
{

int i;
int flag;

__int64 FreeSpace;

String DriveName = ExtractFileDrive(FilePath)+":";
String DirPath = IncludeTrailingPathDelimiter(ExtractFileDir(FilePath));

OSVERSIONINFO ovi;   // バージョン情報を格納する構造体
ovi.dwOSVersionInfoSize = sizeof( OSVERSIONINFO );

// バージョン情報取得
GetVersionEx( (LPOSVERSIONINFO)&ovi );

// Windows95 OSR2以前
if( ( ovi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS )
		&& ( int( ovi.dwBuildNumber & 0xffff ) <= 1000 ) ){

	DWORD SCluster,BSector,FCluster,TCluster;

	if ( GetDiskFreeSpaceW(String(DriveName).c_str(), &SCluster, &BSector, &FCluster, &TCluster) > 0){
		FreeSpace = SCluster*BSector*FCluster;
	}
	else{
		//ネットワークサーバ上は取得できずエラーとなる
		FreeSpace = -1;
	}

}
// OSR2以降～
else{

	ULARGE_INTEGER pqwFreeCaller;
	ULARGE_INTEGER pqwTot;
	ULARGE_INTEGER pqwFree;

	if(::GetDiskFreeSpaceExW(String(DirPath).c_str(), &pqwFreeCaller, &pqwTot, &pqwFree)){
		//64bit Integerで返す
		FreeSpace = pqwFreeCaller.QuadPart;
	}
	else{
		FreeSpace = -1;
	}

}

return(FreeSpace);

}//end GetDiskFreeSpaceNum;