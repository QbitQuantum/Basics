void KDCAttributes::DumpDC(HDC hDC)
{
	POINT pnt;
	SIZE  size;

	m_List.DeleteAll();

	Add(_T("Technology"),  _T("%d"), GetDeviceCaps(hDC, TECHNOLOGY));
	Add(_T("width"),	   _T("%d"), GetDeviceCaps(hDC, HORZRES));
	Add(_T("height"),	   _T("%d"), GetDeviceCaps(hDC, VERTRES));

	GetDCOrgEx(hDC, & pnt); 
	Add(_T("DC Origin"), _T("{ %d, %d }"), pnt.x, pnt.y);

	TCHAR szTitle[MAX_PATH];

	szTitle[0] = 0;

	GetWindowText(WindowFromDC(hDC), szTitle, MAX_PATH);
	Add(_T("Window"),    _T("0x%X \"%s\""), WindowFromDC(hDC), szTitle);

	Add(_T("Bitmap"),        _T("0x%X"), GetCurrentObject(hDC, OBJ_BITMAP));

	Add(_T("Graphics Mode"), _T("%d"), GetGraphicsMode(hDC));
	Add(_T("Mapping Mode"),  _T("%d"), GetMapMode(hDC));

	GetViewportExtEx(hDC, & size);
	Add(_T("Viewport Extent"), _T("{ %d, %d }"), size.cx, size.cy);
	
	GetViewportOrgEx(hDC, & pnt);
	Add(_T("Viewport Origin"), _T("{ %d, %d }"), pnt.x, pnt.y);

	GetWindowExtEx(hDC, & size);
	Add(_T("Window Extent"), _T("{ %d, %d }"), size.cx, size.cy);
	
	GetWindowOrgEx(hDC, & pnt);
	Add(_T("Window Origin"), _T("{ %d, %d }"), pnt.x, pnt.y);

	XFORM xform;
	GetWorldTransform(hDC, & xform);

	Add(_T("World transformation"), _T("{ %f, %f, %f, %f, %f, %f }"),
		xform.eM11, xform.eM12, xform.eM21, xform.eM22, xform.eDx, xform.eDy);

	// transformation

	Add(_T("Background Color"), _T("0x%X"), GetBkColor(hDC));
	Add(_T("Text Color"),       _T("0x%X"), GetTextColor(hDC));
	Add(_T("Palette"),          _T("0x%X"), GetCurrentObject(hDC, OBJ_PAL));

	{
		COLORADJUSTMENT ca;
		GetColorAdjustment(hDC, & ca);
	
		Add(_T("Color Adjustment"), _T("{ %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d }"), 
			ca.caSize, ca.caFlags, ca.caIlluminantIndex,
			ca.caRedGamma, ca.caGreenGamma, ca.caBlueGamma, 
			ca.caReferenceBlack, ca.caReferenceWhite,
			ca.caContrast, ca.caBrightness, ca.caColorfulness, ca.caRedGreenTint);
	}

	Add(_T("Color Space"), _T("0x%X"), GetColorSpace(hDC));
	Add(_T("ICM Mode"),    _T("%d"),   SetICMMode(hDC, ICM_QUERY));

	{
		TCHAR szProfile[MAX_PATH];
		DWORD dwSize = MAX_PATH;

		szProfile[0] = 0;
		GetICMProfile(hDC, & dwSize, szProfile);

		Add(_T("ICM Profile"), _T("%s"), szProfile);
	}

	GetCurrentPositionEx(hDC, & pnt);
	Add(_T("Current Position"), _T("{ %d, %d }"), pnt.x, pnt.y);

	Add(_T("ROP2"),				_T("%d"),	GetROP2(hDC));
	Add(_T("Background Mode"),	_T("%d"),	GetBkMode(hDC));
	Add(_T("Logical Pen"),		_T("0x%X"), GetCurrentObject(hDC, OBJ_PEN));
	Add(_T("DC Pen Color"),     _T("0x%X"), GetDCPenColor(hDC));
	Add(_T("Arc Direction"),	_T("%d"),	GetArcDirection(hDC));

	FLOAT miter;
	GetMiterLimit(hDC, & miter);

	Add(_T("Miter Limit"),		_T("%f"),	miter);
	
	Add(_T("Logical Brush"),    _T("0x%X"), GetCurrentObject(hDC, OBJ_BRUSH));
	Add(_T("DC Brush Color"),   _T("0x%X"), GetDCBrushColor(hDC));

	GetBrushOrgEx(hDC, & pnt);
	Add(_T("Brush Origin"),     _T("{ %d, %d }"), pnt.x, pnt.y);

	Add(_T("Polygon Filling Mode"),   _T("%d"), GetPolyFillMode(hDC));
	Add(_T("Bitmap Stretching Mode"), _T("%d"), GetStretchBltMode(hDC));
	Add(_T("Logical Font"),			  _T("0x%X"), GetCurrentObject(hDC, OBJ_FONT));
	Add(_T("Inter-character spacing"), _T("%d"), GetTextCharacterExtra(hDC));

	DWORD flag = SetMapperFlags(hDC, 0);
	SetMapperFlags(hDC, flag);

	Add(_T("Font Mapper Flags"),       _T("0x%X"), flag);

	Add(_T("Text Alignment"),		   _T("0x%X"), GetTextAlign(hDC));

	Add(_T("Text Justification"),      _T("write only"), 0);

	Add(_T("Layout"),                  _T("%d"), GetLayout(hDC));

	Add(_T("Path"),					   _T("%d bytes"), GetPath(hDC, NULL, NULL, 0));

	RECT rect;

	int typ = GetClipBox(hDC, & rect);

	HRGN hRgn = CreateRectRgn(0, 0, 1, 1);
	
	GetClipRgn(hDC, hRgn);

	Add(_T("Clipping"),				   _T("type %d clip box { %d, %d, %d, %d } size %d bytes"), 
		typ, rect.left, rect.top, rect.right, rect.bottom,
		GetRegionData(hRgn, 0, NULL)
		);
	
	GetMetaRgn(hDC, hRgn);

	GetRgnBox(hRgn, & rect);
	Add(_T("Meta Region"), _T("size %d bytes, rgn box { %d, %d, %d, %d }"), 
		GetRegionData(hRgn, 0, NULL), rect.left, rect.top, rect.right, rect.bottom);

	for (int i=1; i<=5; i++)
	{
		int rslt = GetRandomRgn(hDC, hRgn, i);

		if ( rslt==1 )
		{
			GetRgnBox(hRgn, & rect);
			Add(_T("Random Region"), _T("size %d bytes, rgn box { %d, %d, %d, %d }"), 
			GetRegionData(hRgn, 0, NULL), rect.left, rect.top, rect.right, rect.bottom);
		}
		else if ( rslt==0 )
			Add(_T("Random Region"), _T("NULL"), 0);
		else
			Add(_T("Random Region"), _T("FAIL"), 0);
	}
	DeleteObject(hRgn);

	GetBoundsRect(hDC, & rect, 0);

	Add(_T("Bounds Rectangle"),		_T("{ %d, %d, %d, %d }"), 
		rect.left, rect.top, rect.right, rect.bottom);
}