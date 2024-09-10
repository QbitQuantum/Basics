ChessView::ChessView( HWND parent, Contact::ref contact ) 
{   _HWND=parent;
filePathCHESS=appRootPath+L"\\games\\chess\\chess_1.png";
bmpc=SHLoadImageFile(filePathCHESS.c_str());
/*GetObject(bmpc, sizeof(bmc), &bmc);*/
HDC hdcImage2=CreateCompatibleDC(NULL);
    SelectObject(hdcSKIN, bmpc);
SelectObject(hdcImage2, bmpc);
flagaktiv=0;
transparentColorCH=GetPixel(hdcImage2, 0, 0);DeleteDC(hdcImage2);


int Chesspoleinit[9][9]={
	0 , 0, 0, 0, 0, 0, 0, 0, 0,
	0 ,12,13,14,15,16,14,13,12,
	0 ,11,11,11,11,11,11,11,11,
	0 , 0, 0, 0, 0, 0, 0, 0, 0,
	0 , 0, 0, 0, 0, 0, 0, 0, 0,
	0 , 0, 0, 0, 0, 0, 0, 0, 0,
	0 , 0, 0, 0, 0, 0, 0, 0, 0,
	0 , 1, 1, 1, 1, 1, 1, 1, 1,
	0 , 2, 3, 4, 5, 6, 4, 3, 2


};
int cvtp=1;

	for(int x=1;x<=8;x++){for(int y=1;y<=8;y++){
		
		Chesspole[y][x]=Chesspoleinit[y][x];
	
	}}
    BOOST_ASSERT(parent);

    if (windowClass==0)
        windowClass=RegisterWindowClass();
    if (windowClass==0) throw std::exception("Can't create window class");

    parentHWnd=parent;

    this->contact=contact;

    thisHWnd=CreateWindow((LPCTSTR)windowClass, _T("chat"), WS_CHILD |WS_VISIBLE,
        0, 0, 
		CW_USEDEFAULT, CW_USEDEFAULT,
		parent, NULL, g_hInst, (LPVOID)this);
}