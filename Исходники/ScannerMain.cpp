int _tmain(int argc, _TCHAR* argv[])
{
	FILE* pFile=NULL;
	PBYTE PEImage=NULL;
	PBYTE pCodeData=NULL;
	DWORD baseAddress=0;
	unsigned int CodeDatSize=0;
	BYTE MajorLinkerVersion=0;
	PCHAR PEFileNam="..\\test.exe";
	CHAR  LogFileNam[MAX_PATH];

#pragma region 加载PE文件 
	fopen_s(&pFile,PEFileNam,"rb");
	if(!pFile)
	{
		printf("Error:Can't open %s",PEFileNam);
		return 0;
	}
	const unsigned int fileLen=_filelength(_fileno(pFile));
	PEImage=new BYTE[fileLen];
	fread_s(PEImage,fileLen,fileLen,1,pFile);
	fclose(pFile);
#pragma endregion 
	
#pragma region 解析PE文件
	CPEInfo PEInfo;
	if(!PEInfo.Parse(PEImage))
		return 0;
	pCodeData=PEInfo.GetCodeData();
	CodeDatSize=PEInfo.GetCodeDataSize();
	MajorLinkerVersion=PEInfo.GetMajorLinkerVersion();
	baseAddress=PEInfo.GetBaseAddress();
#pragma endregion 
	//初始化LibScanner，其中加载对于的flb文件
	if(!InitLibScanner(MajorLinkerVersion))
		return 0;
	
#pragma region 调用反汇编引擎
	strcpy_s(LogFileNam,MAX_PATH,PEFileNam);
	ModifySuffix(LogFileNam,".log");
	fopen_s(&pLogFile,LogFileNam,"wb");
	if(!pFile)
	{
		printf("Error:Can't open %s\n",PEFileNam);
		return 0;
	}
	PVDasm(pCodeData,CodeDatSize,baseAddress,pLogFile);
	fclose(pLogFile);
#pragma endregion 
	
	printf("PEFile %s Analysis Succeed!\n",PEFileNam);
	delete[] PEImage;
	return 0;
}