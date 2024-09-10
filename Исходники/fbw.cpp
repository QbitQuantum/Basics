///////////////////////////////////////////////////////////////////////
// Class				:	CWinDisplay
// Method				:	redraw
// Description			:	Redraw the image
// Return Value			:	-
// Comments				:
void	CWinDisplay::redraw() {
	RECT	windowRect;
	RECT	imageRect;
	HDC		cDc;

	cDc				=	GetDC(hWnd);

	imageRect.left	=	0;
	imageRect.top	=	0;
	imageRect.right	=	width;
	imageRect.bottom=	height;
	
	GetClientRect(hWnd,&windowRect);

	SetStretchBltMode(cDc, COLORONCOLOR);
	StretchDIBits(cDc,	0,0,width,height,
						0,0,width,height,
						imageData,&info,DIB_RGB_COLORS,SRCCOPY);
	willRedraw		=	FALSE;
}