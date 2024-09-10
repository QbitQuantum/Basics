BOOL CObjDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	string pathStr = lpszPathName;
	m_Object = new CWavefrontObj(pathStr);

	CRect tRect(0, 0, THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT);
	CDC tDC;
	CBitmap *oldBitmap;
//	CRgn ClipRgn;
	CDC scrDC;
	
	scrDC.Attach(GetDC(GetDesktopWindow()));

//	ClipRgn.CreateRectRgn(tRect.left, tRect.top, tRect.right, tRect.bottom);

	tDC.CreateCompatibleDC(&scrDC);
	tDC.SetMapMode(scrDC.GetMapMode());

	tDC.DPtoLP(&tRect);
	tDC.SetWindowExt(tRect.Size());
	tDC.SetWindowOrg(tRect.left, tRect.top);

	tDC.LPtoDP(&tRect);
	tDC.SetViewportExt(tRect.Size());
	tDC.SetViewportOrg(tRect.left, tRect.top);

	m_ThumbNail.CreateCompatibleBitmap(&scrDC, tRect.Width(), tRect.Height());
	oldBitmap = tDC.SelectObject(&m_ThumbNail);

	tDC.FillSolidRect(tRect, RGB(0xff, 0xff, 0xff));
	// create a thumbnail
	CObjView::RenderImage(&tDC, this, tRect);

	tDC.SelectObject(oldBitmap);

	m_FileName = lpszPathName;
	GetFileTitle(m_FileName, m_DisplayName.GetBuffer(_MAX_FNAME),
		_MAX_FNAME);
	m_DisplayName.ReleaseBuffer();

	// made it this far so add to program list of objects
	gObjLoader->m_WavfObjects.push_back(m_Object);

	OBJECTSTRUCT os;

	os.name = &m_DisplayName;
	os.fileName = &m_FileName;
	os.thumbNail = &m_ThumbNail;
	os.pageIndex = &gObjLoader->m_PageIndex;
	os.rsrcIndex = &m_ObjectIndex;
	os.object = m_Object;

	gObjLoader->m_ProgramInfo->BroadcastMessage(
		AddObjectMessage, &os);

	return TRUE;
}