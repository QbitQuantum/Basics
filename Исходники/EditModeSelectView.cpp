void CEditModeSelectView::OnDraw(CDC* pDC)
{
	
	CNoteEditingToolDoc* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
	
	// 더블버퍼링을 위해
	
	CDC memCDC;
	CBitmap bForMemCDC;
	CRect rect;
	// 창 크기를 받아온다.
	GetClientRect(&rect);


	bForMemCDC.DeleteObject();
	bForMemCDC.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());

	memCDC.CreateCompatibleDC(pDC);
	memCDC.SelectObject(&bForMemCDC);

	


	//Graphics graphics(pDC->m_hDC);
	Graphics graphics(memCDC.m_hDC);
		
	char noteEditingMode = pDoc->getNoteEditingMode();
	char noteWriteType = pDoc->getNoteWriteType();


	// 각각의 아이콘들을 출력 할 좌표를 저장하는 함수.
	int positionX = 0;
	int positionY = 0;


	// 배경 그리기
	HRSRC hResource = FindResource(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_PNG_BACK), _T("PNG"));
	if(!hResource) return;

	DWORD imageSize = SizeofResource(AfxGetApp()->m_hInstance, hResource);
	HGLOBAL hGlobal = LoadResource(AfxGetApp()->m_hInstance, hResource);
	LPVOID pData = LockResource(hGlobal);

	HGLOBAL hBuffer = GlobalAlloc(GMEM_MOVEABLE, imageSize);
	LPVOID pBuffer = GlobalLock(hBuffer);

	CopyMemory(pBuffer,pData,imageSize);
	GlobalUnlock(hBuffer);

	IStream *pStream;
	HRESULT hr = CreateStreamOnHGlobal(hBuffer, TRUE, &pStream);

	Image imagePNG(pStream);


	pStream->Release();
	if (imagePNG.GetLastStatus() != Ok) return;

	graphics.DrawImage(&imagePNG, 0, 0, imagePNG.GetWidth(), imagePNG.GetHeight());



	
	// 현재 선택중인 위치의 음영
	hResource = FindResource(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_PNG_SEL_OK), _T("PNG"));
	if(!hResource) return;
	imageSize = SizeofResource(AfxGetApp()->m_hInstance, hResource);
	hGlobal = LoadResource(AfxGetApp()->m_hInstance, hResource);
	pData = LockResource(hGlobal);
	hBuffer = GlobalAlloc(GMEM_MOVEABLE, imageSize);
	pBuffer = GlobalLock(hBuffer);
	CopyMemory(pBuffer,pData,imageSize);
	GlobalUnlock(hBuffer);
	hr = CreateStreamOnHGlobal(hBuffer, TRUE, &pStream);
	
	Image imagePNGSelOk(pStream);
	pStream->Release();
	if (imagePNGSelOk.GetLastStatus() != Ok) return;
	
	// 음영 위치를 상태에 맞게 변화시킨다.
	if ( calSelectedMenuCursor(noteWriteType, positionX, positionY) < 0 )
	{
		AfxMessageBox(_T("에러!"));
	}
	else
	{
		graphics.DrawImage(&imagePNGSelOk, positionX, positionY, imagePNGSelOk.GetWidth(), imagePNGSelOk.GetHeight());
	}


	// 현재 선택중인 편집 모드의 음영
	hResource = FindResource(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_PNG_MODE_SEL), _T("PNG"));
	if(!hResource) return;
	imageSize = SizeofResource(AfxGetApp()->m_hInstance, hResource);
	hGlobal = LoadResource(AfxGetApp()->m_hInstance, hResource);
	pData = LockResource(hGlobal);
	hBuffer = GlobalAlloc(GMEM_MOVEABLE, imageSize);
	pBuffer = GlobalLock(hBuffer);
	CopyMemory(pBuffer,pData,imageSize);
	GlobalUnlock(hBuffer);
	hr = CreateStreamOnHGlobal(hBuffer, TRUE, &pStream);
	
	Image imagePNGModeSelOk(pStream);
	pStream->Release();
	if (imagePNGModeSelOk.GetLastStatus() != Ok) return;

	// 음영 위치를 상태에 맞게 변화시킨다.
	if ( calSelectedModeCursor(noteEditingMode, positionX, positionY) < 0 )
	{
		AfxMessageBox(_T("에러!"));
	}
	else
	{
		graphics.DrawImage(&imagePNGModeSelOk, positionX, positionY, imagePNGModeSelOk.GetWidth(), imagePNGModeSelOk.GetHeight());
	}


	// 현재 선택중인 재생 모드의 음영
	hResource = FindResource(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_PNG_MODE_SEL), _T("PNG"));
	if(!hResource) return;
	imageSize = SizeofResource(AfxGetApp()->m_hInstance, hResource);
	hGlobal = LoadResource(AfxGetApp()->m_hInstance, hResource);
	pData = LockResource(hGlobal);
	hBuffer = GlobalAlloc(GMEM_MOVEABLE, imageSize);
	pBuffer = GlobalLock(hBuffer);
	CopyMemory(pBuffer,pData,imageSize);
	GlobalUnlock(hBuffer);
	hr = CreateStreamOnHGlobal(hBuffer, TRUE, &pStream);

	Image imagePNGPlaySelOk(pStream);
	pStream->Release();
	if (imagePNGPlaySelOk.GetLastStatus() != Ok) return;


	// 음영 위치를 상태에 맞게 변화시킨다.
	if ( calSelectedPlayCursor(pDoc->getNotePickingViewPtr()->getNowPlayingStatus(), positionX, positionY) < 0 )
	{
		// 그리지 않는다.
		//AfxMessageBox(_T("에러!"));
	}
	else
	{
		graphics.DrawImage(&imagePNGPlaySelOk, positionX, positionY, imagePNGPlaySelOk.GetWidth(), imagePNGPlaySelOk.GetHeight());
	}




	// 연필
	hResource = FindResource(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_PNG_PENCIL), _T("PNG"));
	if(!hResource) return;
	imageSize = SizeofResource(AfxGetApp()->m_hInstance, hResource);
	hGlobal = LoadResource(AfxGetApp()->m_hInstance, hResource);
	pData = LockResource(hGlobal);
	hBuffer = GlobalAlloc(GMEM_MOVEABLE, imageSize);
	pBuffer = GlobalLock(hBuffer);
	CopyMemory(pBuffer,pData,imageSize);
	GlobalUnlock(hBuffer);
	hr = CreateStreamOnHGlobal(hBuffer, TRUE, &pStream);

	Image imagePNGPencil(pStream);
	pStream->Release();
	if (imagePNGPencil.GetLastStatus() != Ok) return;

	graphics.DrawImage(&imagePNGPencil, V_PENCIL_OFFSET_X, V_PENCIL_OFFSET_Y, imagePNGPencil.GetWidth(), imagePNGPencil.GetHeight());



	// 글자 넣기
	hResource = FindResource(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_PNG_TEXT), _T("PNG"));
	if(!hResource) return;
	imageSize = SizeofResource(AfxGetApp()->m_hInstance, hResource);
	hGlobal = LoadResource(AfxGetApp()->m_hInstance, hResource);
	pData = LockResource(hGlobal);
	hBuffer = GlobalAlloc(GMEM_MOVEABLE, imageSize);
	pBuffer = GlobalLock(hBuffer);
	CopyMemory(pBuffer,pData,imageSize);
	GlobalUnlock(hBuffer);
	*pStream;
	hr = CreateStreamOnHGlobal(hBuffer, TRUE, &pStream);
	Image imagePNGText(pStream);

	pStream->Release();
	if (imagePNGText.GetLastStatus() != Ok) return;
	graphics.DrawImage(&imagePNGText, V_TEXT_OFFSET_X, V_TEXT_OFFSET_Y, imagePNGText.GetWidth(), imagePNGText.GetHeight());
	
	

	// 마지막에 한번에 화면 그리기
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memCDC, 0, 0, SRCCOPY);


}