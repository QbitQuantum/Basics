/*
Calls TWAIN to actually get the image
*/
BOOL CTwain::GetImage(TW_IMAGEINFO& info)
{
HANDLE hBitmap;
	CallTwainProc(&m_AppId,&m_Source,DG_IMAGE,DAT_IMAGENATIVEXFER,MSG_GET,&hBitmap);
	switch(m_returnCode)
	{
	case TWRC_XFERDONE:
			CopyImage(hBitmap,info);
			break;
	case TWRC_CANCEL:
			break;
	case TWRC_FAILURE:
			CancelTransfer();
			return FALSE;

	}
	GlobalFree(hBitmap);
	return EndTransfer();
}