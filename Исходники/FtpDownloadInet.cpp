int FtpDownloadInet::_getFileSize(HINTERNET hRemoteFile) const
{	
	DWORD lpdwFileSizeHigh, lpdwFileSizeLow;
	lpdwFileSizeLow = FtpGetFileSize(hRemoteFile, &lpdwFileSizeHigh);
	return lpdwFileSizeLow;
}