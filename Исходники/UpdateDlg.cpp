static void Callback_Download( t_DownloadNotifyPara *pDownloadNotifyPara, WPARAM wParam )
{
	if( !pDownloadNotifyPara )
		return;

	if(wParam != DOWNLOAD_WPARAM)
		return;

	if(!updatedlg)
		return;

	int index = pDownloadNotifyPara->nIndex;

	switch ( pDownloadNotifyPara->nNotityType )
	{
	case NOTIFY_TYPE_GOT_REMOTE_FILENAME:
		{
			break;
		}
	case NOTIFY_TYPE_GOT_REMOTE_FILESIZE:
		{
			//PostMessage(updatedlg->m_hWnd, WM_MSG_DOWNLOADER_FILESIZE, wParam, (LPARAM)pDownloadNotifyPara->lpNotifyData);
			updatedlg->m_filesize = (int)pDownloadNotifyPara->lpNotifyData;
			AtlTrace("Remote file size is : %d bytes\n", (int)pDownloadNotifyPara->lpNotifyData);
			break;
		}
	case NOTIFY_TYPE_START_DOWNLOAD:
		{
			AtlTrace(L"Downloading Start");
			break;
		}
	case NOTIFY_TYPE_END_DOWNLOAD:
		{
			ENUM_DOWNLOAD_RESULT eDownloadResult = (ENUM_DOWNLOAD_RESULT)(int)pDownloadNotifyPara->lpNotifyData;
			if ( eDownloadResult == ENUM_DOWNLOAD_RESULT_SUCCESS ) {
				PostMessage(updatedlg->m_hWnd, WM_MSG_DOWNLOADER_FINISHED, wParam, 1);
				AtlTrace(L"Download successfully.\n");
			} else if ( eDownloadResult == ENUM_DOWNLOAD_RESULT_FAILED ) {
				PostMessage(updatedlg->m_hWnd, WM_MSG_DOWNLOADER_FINISHED, wParam, 0);
				AtlTrace(L"Download failed.\n");
			} else if ( eDownloadResult == ENUM_DOWNLOAD_RESULT_CANCEL )
				AtlTrace(L"User cancel download.\n");
			else {
				PostMessage(updatedlg->m_hWnd, WM_MSG_DOWNLOADER_FINISHED, wParam, 0);
				AtlTrace(L"Unknow Download Finished.\n");
			}
			break;
		}
	case NOTIFY_TYPE_THREAD_DOWNLOADED_SIZE:
		{
			PostMessage(updatedlg->m_hWnd, WM_MSG_DOWNLOADER_DOWNSIZE, wParam, (LPARAM)pDownloadNotifyPara->lpNotifyData);
			AtlTrace(L"Downloaded size is : %d bytes\n", (int)pDownloadNotifyPara->lpNotifyData);
			break;
		}
	}
}