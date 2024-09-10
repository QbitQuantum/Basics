//构造函数
CUserFaceRes::CUserFaceRes(void)
{
	//加载资源
	HINSTANCE hInstancle=GetModuleHandle(GAMECLIENTLOBBY_EXPORTS_NAME);
	
	//设置变量
	m_NormalSize.SetSize(NOR_FACE_WIDTH,NOR_FACE_HEIGHT);
	m_SmallSize.SetSize(LIT_FACE_WIDTH,LIT_FACE_HEIGHT);
	ImgFileList.clear();
	TempFileList.clear();

	CString DATFile=TEXT("FaceImage.DAT");

	CFileFind	finder;
	BOOL	FF;
	BOOL    bHaveBmp=FALSE;

	FF=finder.FindFile(DATFile);
	if(!FF){
		return;
	}

	CFile pFile;
	pFile.Open(DATFile,CFile::modeRead);

	char FileNum[10];
	pFile.Read(FileNum,9);
	long NUM = atol(FileNum);

	for(long j=0;j<NUM;j++){	

		BITMAPFILEHEADER bmfh;

		// 步骤1　读取文件头
		char filename[128];
		pFile.Read(filename,127);

		int nCount = pFile.Read((LPVOID) &bmfh, sizeof(BITMAPFILEHEADER));

		// 判断是否是BMP格式的位图
		if(bmfh.bfType != BMP_HEADER_MARKER) 
		{
			continue;
		}

		// 计算信息头加上调色板的大小并分内存
		int nSize = bmfh.bfOffBits - sizeof(BITMAPFILEHEADER);
		LPBITMAPINFOHEADER m_pBMIH = (LPBITMAPINFOHEADER) new BYTE[nSize];

		// 步骤2　读取信息头和调色板
		nCount = pFile.Read(m_pBMIH, nSize); 

		// 步骤3　读取图象数据
		LPBYTE	m_pBits = (LPBYTE) new BYTE[m_pBMIH->biSizeImage];
		nCount = pFile.Read(m_pBits, m_pBMIH->biSizeImage); 

		ImgFileList.push_back(filename);
		delete m_pBits;
		delete m_pBMIH;
	}
	pFile.Close();
	m_hDrawDib  = DrawDibOpen();
	return;
}