void CComPrint::WinPrint(CString csText)
{
	char szPrinter[200] = "";
	char *pszDevice = NULL;
	char *pszDriver = NULL;
	char *pszOutput = NULL;

	HDC hdcPrint = NULL; // 定义一个设备环境句柄

	static DOCINFO di={sizeof(DOCINFO),"printer",NULL};

	// 得到设备字符串存入数组szPrinter中
	GetProfileString("windows","device",",,,",szPrinter,80); 

	// 将设备字符串分解
	if( (NULL != (pszDevice = strtok(szPrinter,","))) && 
		(NULL != (pszDriver = strtok(NULL,","))) &&
		(NULL != (pszOutput = strtok(NULL,","))))
	{
		// 创建一个打印机设备句柄
		if((hdcPrint = CreateDC(pszDriver,pszDevice, pszOutput, NULL)) != 0)
		{ 
			if (StartDoc(hdcPrint, &di) > 0)	//开始执行一个打印作业 
			{ 
				StartPage(hdcPrint);			//打印机走纸,开始打印 
				SaveDC(hdcPrint);				//保存打印机设备句柄

				// 输出文字
				CRect rcText(0,0,0,0);
				::DrawText(hdcPrint, csText, csText.GetLength(), &rcText, DT_CALCRECT);	// 计算大小
				::DrawText(hdcPrint, csText, csText.GetLength(), &rcText, DT_WORDBREAK);

				RestoreDC(hdcPrint,-1);			//恢复打印机设备句柄 
				EndPage(hdcPrint);				//打印机停纸,停止打印 
				EndDoc(hdcPrint);				//结束一个打印作业 
			} 

			// 用API函数DeleteDC销毁一个打印机设备句柄 
			DeleteDC(hdcPrint);
		}
	}
}