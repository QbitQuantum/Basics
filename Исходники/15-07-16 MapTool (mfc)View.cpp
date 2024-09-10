void CMy150716MapToolmfcView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	
	m_nSelDrawID = 0;
	SetScrollSizes(MM_TEXT,CSize(TILESIZEX * TILECNTX , TILESIZEY * TILECNTY/2));
	
	
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	if (FAILED(GET_SINGLE(CDevice)->InitDevice(m_hWnd)))
	{
		return;
	}

	if (FAILED(GET_SINGLE(CTextureMgr)->InsertTexture(L"../Resource/Texture/Tile/Tile37.png",L"Test",TEXTYPE_SINGLE)))
	{
		AfxMessageBox(L"이미지 로드 실패1");
		return;
	}

	if(FAILED(GET_SINGLE(CTextureMgr)->InsertTexture(L"../Resource/Texture/Tile/Tile%d.png"
		,L"BackGround",TEXTYPE_MULTI,L"Tile",38)))
	{
		AfxMessageBox(L"이미지 로드 실패2");
		return;
	}


	//mainframe mfc를 전체적으로 관리하고 있는 애 
	CMainFrame* pMainFrm =(CMainFrame*)AfxGetMainWnd(); 
	
	RECT rcWindow;
	pMainFrm->GetWindowRect(&rcWindow); //w전체 윈도우의 rect를 얻어올수있음

	SetRect(&rcWindow,0,0,rcWindow.right - rcWindow.left,
		rcWindow.bottom - rcWindow.top);

	RECT rcMainView;
	GetClientRect(&rcMainView); //view 좌표 , 클라이언트의 rect

	float fRowFrm = rcWindow.bottom - rcMainView.bottom;
	float fColFrm = rcWindow.right - rcMainView.right;

	pMainFrm->SetWindowPos(NULL,0,0,800+fColFrm,600+fRowFrm,SWP_NOZORDER);
	


	InitTile();

}