/////////////////////////////////////////////////////////////////////////
//名称：GetExcelDriver
//功能：获取ODBC中Excel驱动
//日期：2014-3-5
/////////////////////////////////////////////////////////////////////////
CString GetExcelDriver()
{
	char szBuf[2001];
	WORD cbBufMax = 2000;
	WORD cbBufOut;
	char *pszBuf = szBuf;
	CString sDriver;

	//获取已安装驱动的名称(函数在odbcinst.h里)
	if(!SQLGetInstalledDrivers(szBuf,cbBufMax,&cbBufOut))
		return "";

	//检索已安装的驱动是否有Excel...
	do 
	{
		if(strstr(pszBuf,"Excel") != 0)			
		{
			//发现!
			sDriver = CString(pszBuf);
			break;
		}
		pszBuf=strchr(pszBuf,'\0') + 1;
	} while (pszBuf[1]!='\0');

	return sDriver;
}