BOOL CDirTreeCtrl::AttachImgList()
{
	SHFILEINFO shFinfo;
	HIMAGELIST hImgList = NULL;
	if ( GetImageList( TVSIL_NORMAL ) ) m_imgList.Detach();
	
	hImgList = (HIMAGELIST)SHGetFileInfoW(     _T("C:\\"),
		0,         &shFinfo,         sizeof( shFinfo ),
		SHGFI_SYSICONINDEX |  SHGFI_SMALLICON );
	if ( !hImgList )     {
		m_strError = _T("无法得到系统图标文件!");
		return FALSE;
	}
	m_imgList.m_hImageList = hImgList;
	SetImageList( &m_imgList, TVSIL_NORMAL );
	return TRUE;  
}