BYTE* CCaptureVideo::EnumCompress()
{
	CVideoCodec cVideo; 
	int	fccHandler;
    char strName[MAX_PATH];
	LPBYTE lpBuffer=NULL;
	lpBuffer = (LPBYTE)LocalAlloc(LPTR, 1);
    int iCount=0;//共有多上个压缩设备
	
	while(cVideo.MyEnumCodecs(&fccHandler, strName))
	{
		iCount++;
		DWORD 	dwOffset = LocalSize(lpBuffer);
		int iMsgSize=strlen(strName)+sizeof(DWORD)+1;    //一个表达压缩设备所用的大小
		//开辟新的内存储存数据
		lpBuffer = (LPBYTE)LocalReAlloc(lpBuffer, dwOffset +iMsgSize, LMEM_ZEROINIT|LMEM_MOVEABLE);
		memcpy(lpBuffer+dwOffset,&fccHandler,sizeof(DWORD));     //压缩的编码
		strcpy((char*)(lpBuffer+dwOffset+sizeof(DWORD)),strName);
	}
	lpBuffer[0]=iCount;
	return lpBuffer;
}