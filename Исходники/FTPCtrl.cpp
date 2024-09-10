BOOL CFTPCtrl::FtpDownloadFile(CString ftpFileName,CString localFilePath)
{
	//localFilePath=CreateFilePath(ftpFileName,localFilePath);
	HANDLE hOpenFile = (HANDLE)CreateFile(localFilePath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_NEW, NULL, NULL);
	if(hOpenFile==INVALID_HANDLE_VALUE)
	{		
		if (IDYES==AfxMessageBox(_T("创建本地文件失败，指定路径下可能已存在同名文件，是否覆盖?"),MB_YESNO))
		{
			hOpenFile = (HANDLE)CreateFile(localFilePath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, NULL, NULL);
			if(hOpenFile==INVALID_HANDLE_VALUE)
			{		
				AfxMessageBox(_T("创建本地文件失败,请重新选择文件路径后重试!"));
				CloseHandle(hOpenFile);//一定注意在函数退出之前对句柄进行释放。
				return FALSE;	
			}
		}
		else
		{
			AfxMessageBox(_T("下载文件失败!"));
			CloseHandle(hOpenFile);//一定注意在函数退出之前对句柄进行释放。
			return FALSE;
		}		
	}

	HINTERNET hFtpOpen = FtpOpenFile( m_hConnect, ftpFileName, GENERIC_READ, FTP_TRANSFER_TYPE_ASCII, 0 );
	if ( NULL == hFtpOpen )
	{
		AfxMessageBox(_T("Ftp远程文件打开失败！"));
		return FALSE;
	}
	
	DWORD fileSize=	FtpGetFileSize(hFtpOpen,NULL);//这种调用只能获取4GB以内的文件，FtpGetFileSize该函数第二个参数64位文件大小的高32位。
	DWORD readSize;
	char *buffer=new char[fileSize];	
	if (FALSE==InternetReadFile(hFtpOpen,buffer,fileSize,&readSize))
	{
		AfxMessageBox(_T("读取Ftp文件失败！"));
		return FALSE;
	}

	DWORD dwBytesWritten;
	if (FALSE==WriteFile(  hOpenFile, buffer,fileSize,&dwBytesWritten,NULL))
	{
		AfxMessageBox(_T("下载文件失败！"));
		return FALSE;
	}

	CloseHandle( hOpenFile );
	InternetCloseHandle(hFtpOpen);
	return TRUE;

}