///===加载图片================================================///
// 参数: 文件实例
// add by xuyz 2011-09-17
void CPicScrollView::LoadPic(CFile& file)
{	
	CArchive ar(&file, CArchive::load | CArchive::bNoFlushOnDelete);
	
	CArchiveStream arcstream(&ar);
	
	ReleasePic();
	
	if (FAILED(OleLoadPicture(&arcstream, 0, FALSE, IID_IPicture, (void**)&m_pPic)))
	{
		return;
	}
	
	m_pPic->get_Width(&m_hmWidth);     
	m_pPic->get_Height(&m_hmHeight); 
    
	CClientDC dc(this);
	
	CSize sz(m_hmWidth,m_hmHeight);
	dc.HIMETRICtoDP(&sz);
	m_cxPic = sz.cx;
	m_cyPic = sz.cy;
	
	SetScrollSizes(MM_TEXT, sz);
	
	Invalidate();
}