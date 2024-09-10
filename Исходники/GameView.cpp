void CGameView::OnDraw(CDC* pDC)
{
	CGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//**** 배경색 *************
	CBrush brush (gv_bgColor);
	CBrush *pOldB =pDC ->SelectObject (&brush) ;
	CRect rect;
	GetClientRect(&rect);
	pDC->Rectangle(rect);
	pDC->SelectObject(pOldB); 
	//***********************

	// 랜덤하지 않으면 랜덤함수 호출
	if(pDoc->gd_bRandom) pDoc->OnRandom();

	int nCount = 0;
go:
	CDC memDC;
	CBitmap* pOldBmp;

	if(isInit){
		// Font 설정 Part
		CFont myFont, *pOldFont ;
		myFont.CreateFont (40, 0, 0, 0, FW_BOLD, true, false, false, 
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH, gv_font) ;
		pOldFont =pDC->SelectObject (&myFont) ;

		// Text 설정 Part
		CString str =_T ("HINT") ;
		pDC->SetBkColor (gv_bgColor) ;		// 글자의 배경은 바탕과 같이 
		pDC->SetTextColor (0x00FFFFFF & ~gv_bgColor) ;		// 글자 색을 바탕화면의 반대 색으로
		pDC->SetTextAlign (TA_CENTER) ;		// 가운데 출력
		pDC->TextOutW (rect.Width () /2, rect.top +20, str) ;

		// 보여주는 파트
		pDoc->gd_nBmpFirstID = pDoc->gd_nBmpSecondID = 0 ;		// 비트맵의 이름을 초기화
		pDoc->gd_bMouse = FALSE;

		for(int i=0;i<pDoc->gd_nRow;i++)
			for(int j=0;j<pDoc->gd_nCol;j++)
				pDoc->gd_bShow[i][j] = TRUE;
	}
	memDC.CreateCompatibleDC(pDC);

	for(int n=0;n<pDoc->gd_nRow;n++){
		for(int m=0;m<pDoc->gd_nCol;m++){
			// 이미지 출력 
			int imgStartPtrX = rect.right/(pDoc->gd_nCol+2);
			int imgStartPtrY = rect.bottom/(pDoc->gd_nRow+2);
			/* 이미지 출력 */
			if(pDoc->gd_bShow[n][m]){
				pDoc->gd_bmp[n][m].LoadBitmapW(IDB_BITMAP1+pDoc->gd_nRnd[nCount]);
				pOldBmp = memDC.SelectObject(&pDoc->gd_bmp[n][m]); 
				pDC->StretchBlt(
					imgStartPtrX*(m+1), imgStartPtrY*(n+1),
					imgStartPtrX, imgStartPtrY, 
					&memDC, 0, 0, 
					pDoc->gd_bmCell.cx, pDoc->gd_bmCell.cy, SRCCOPY);
				pDoc->gd_bmp[n][m].DeleteObject();
			}
			/* 커버 출력 */
			if(!pDoc->gd_bShow[n][m]){
				CBitmap bmp;
				bmp.LoadBitmapW(IDB_BITMAP1);	// 커버 출력
				pOldBmp = memDC.SelectObject(&bmp);
				 
				pDC->StretchBlt(
					imgStartPtrX*(m+1), imgStartPtrY*(n+1),
					imgStartPtrX, imgStartPtrY, 
					&memDC, 0, 0, 
					pDoc->gd_bmCell.cx, pDoc->gd_bmCell.cy, SRCCOPY);
				bmp.DeleteObject();
			}
			nCount++;
		}
	}
	memDC.SelectObject(pOldBmp);
	pDoc->ResizeWindow();

	// 게임이 시작된 시점에서의 처리
	if(isInit){
		isInit = FALSE;

		for(int i=0;i<pDoc->gd_nRow;i++)
			for(int j=0;j<pDoc->gd_nCol;j++)
				pDoc->gd_bShow[i][j] = FALSE;

		// 음악 디바이스 열기
		gv_timeDV =OpenSounds (_T ("C:\\image\\심장소리.mp3")) ;	
		gv_successDV =OpenSounds (_T ("C:\\image\\박수갈채.mp3")) ;
		gv_failDV =OpenSounds (_T ("C:\\image\\언더테이커_등장.mp3")) ;	
		gv_bgDV =OpenSounds (_T ("C:\\image\\Terranigma-Light_Side_Field.mp3")) ;

		// 타임바 범위 정의
		gv_timeUpper = gv_min*60 + gv_sec;
		pTimeDlg ->timeCtrl.SetRange32 (0, gv_timeUpper) ;	// 범위
		pTimeDlg ->timeCtrl.SetPos (gv_min*60 +gv_sec) ;		// 초기위치

		PlaySound (L"C:\\image\\즐거운시간되십시오.wav", NULL, SND_SYNC) ;
		
		// Hint time
		int time;
		if(gv_lev == _T("초급")) time = 600;
		else if(gv_lev == _T("중급")) time = 1000;
		else time = 1800;

		pTimeDlg ->ShowWindow (SW_SHOW) ;	// 모달리스 시작
		Sleep(time);
		pDC ->TextOutW (rect.Width () /2, rect.top +20, _T ("             ")) ;
		PlaySounds (gv_bgDV) ;	// 슬립 끝나고 배경음
		SetTimer (true, 1, NULL) ;
		goto go;
	}
}