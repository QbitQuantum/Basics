// Use GDI to draw in video frame
void	GdiDraw (IDeckLinkVideoFrame* theFrame)
{
	BITMAPINFOHEADER bmi;
	
	ZeroMemory(&bmi, sizeof(bmi));
	bmi.biSize = sizeof(bmi);
	bmi.biWidth = theFrame->GetWidth();
	bmi.biHeight = theFrame->GetHeight();
	bmi.biPlanes = 1;
	bmi.biBitCount = 32;
	bmi.biCompression = BI_RGB;
	bmi.biSizeImage = (bmi.biWidth * bmi.biHeight * 4);
	
	HDC hdc = CreateCompatibleDC(NULL);
	BYTE* pbData = NULL;
	BYTE* pbDestData = NULL;

	RECT fillRect1 = {50, 50, 100, 100};
	RECT fillRect2 = {100, 100, 150, 150};
	RECT fillRect3 = {150, 150, 200, 200};

	HBITMAP hbm = CreateDIBSection(hdc, (BITMAPINFO*)&bmi, DIB_RGB_COLORS, (void**)&pbData, NULL, 0);
	SelectObject(hdc, hbm);

	HBRUSH		backBrush = (HBRUSH)GetStockObject(DC_BRUSH);
	
	TextOut(hdc, bmi.biWidth/2, bmi.biHeight/2, _T("Hello, world!"), 13);	// Place string in centre of screen

	SetDCBrushColor(hdc, RGB(0, 200, 240));								// create square
	FillRect(hdc, &fillRect1, backBrush);
	SetDCBrushColor(hdc, RGB(180, 130, 130));							// create square
	FillRect(hdc, &fillRect2, backBrush);
	SetDCBrushColor(hdc, RGB(0, 120, 242));								// create square
	FillRect(hdc, &fillRect3, backBrush);

	Ellipse(hdc, 200, 200,300,300);										// create ellipse

	theFrame->GetBytes((void**)&pbDestData);							// get frame buffer pointer
	memcpy(pbDestData, pbData, bmi.biSizeImage); 
	DeleteObject(SelectObject(hdc, hbm));								// delete attached GDI object
}