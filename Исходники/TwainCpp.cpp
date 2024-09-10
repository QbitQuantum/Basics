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
		TRACE("********** GetImage --> TWRC_XFERDONE ************\n");
			CopyImage(hBitmap,info);
			break;
	case TWRC_CANCEL:
		TRACE("GetImage --> TWRC_CANCEL.\n");
			break;
	case TWRC_FAILURE:
		TRACE("********** GetImage --> TWRC_FAILURE ************\n");
			CancelTransfer();
			return FALSE;
	default:
		TRACE("GetImage --> default.\n");
		break;
	}
	GlobalFree(hBitmap);

	TRACE("********** GetImage --> done ************\n");
	return EndTransfer();
}