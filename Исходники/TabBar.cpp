void TabBarPlus::drawItem(DRAWITEMSTRUCT *pDrawItemStruct)
{
	RECT rect = pDrawItemStruct->rcItem;
	
	int nTab = pDrawItemStruct->itemID;
	if (nTab < 0)
	{
		::MessageBox(NULL, TEXT("nTab < 0"), TEXT(""), MB_OK);
		//return ::CallWindowProc(_tabBarDefaultProc, hwnd, Message, wParam, lParam);
	}
	bool isSelected = (nTab == ::SendMessage(_hSelf, TCM_GETCURSEL, 0, 0));

	TCHAR label[MAX_PATH];
	TCITEM tci;
	tci.mask = TCIF_TEXT|TCIF_IMAGE;
	tci.pszText = label;     
	tci.cchTextMax = MAX_PATH-1;

	if (!::SendMessage(_hSelf, TCM_GETITEM, nTab, reinterpret_cast<LPARAM>(&tci))) 
	{
		::MessageBox(NULL, TEXT("! TCM_GETITEM"), TEXT(""), MB_OK);
		//return ::CallWindowProc(_tabBarDefaultProc, hwnd, Message, wParam, lParam);
	}
	HDC hDC = pDrawItemStruct->hDC;
	
	int nSavedDC = ::SaveDC(hDC);

	::SetBkMode(hDC, TRANSPARENT);
	HBRUSH hBrush = ::CreateSolidBrush(::GetSysColor(COLOR_BTNFACE));
	::FillRect(hDC, &rect, hBrush);
	::DeleteObject((HGDIOBJ)hBrush);

	if (isSelected)
	{
		if (_drawTopBar)
		{
			RECT barRect = rect;
			
			if (_isVertical)
			{
				barRect.right = barRect.left + 6;
				rect.left += 2;
			}
			else
			{
				barRect.bottom = barRect.top + 6;
				rect.top += 2;
			}

			if (::SendMessage(_hParent, NPPM_INTERNAL_ISFOCUSEDTAB, 0, (LPARAM)_hSelf))
				hBrush = ::CreateSolidBrush(_activeTopBarFocusedColour); // #FAAA3C
			else
				hBrush = ::CreateSolidBrush(_activeTopBarUnfocusedColour); // #FAD296

			::FillRect(hDC, &barRect, hBrush);
			::DeleteObject((HGDIOBJ)hBrush);		
		}
	}
	else
	{
		if (_drawInactiveTab)
		{
			RECT barRect = rect;

			hBrush = ::CreateSolidBrush(_inactiveBgColour);
			::FillRect(hDC, &barRect, hBrush);
			::DeleteObject((HGDIOBJ)hBrush);
		}
	}

	if (_drawTabCloseButton)
	{
		RECT closeButtonRect = _closeButtonZone.getButtonRectFrom(rect);
		if (isSelected)
		{
			if (!_isVertical)
			{
				//closeButtonRect.top  += 2;
				closeButtonRect.left -= 2;
			}
		}
		else
		{
			if (_isVertical)
				closeButtonRect.left += 2;			
		}

		
		// 3 status for each inactive tab and selected tab close item :
		// normal / hover / pushed
		int idCloseImg;

		if (_isCloseHover && (_currentHoverTabItem == nTab) && (_whichCloseClickDown == -1)) // hover
			idCloseImg = IDR_CLOSETAB_HOVER;
		else if (_isCloseHover && (_currentHoverTabItem == nTab) && (_whichCloseClickDown == _currentHoverTabItem)) // pushed
			idCloseImg = IDR_CLOSETAB_PUSH;
		else
			idCloseImg = isSelected?IDR_CLOSETAB:IDR_CLOSETAB_INACT;


		HDC hdcMemory;
		hdcMemory = ::CreateCompatibleDC(hDC);
		HBITMAP hBmp = ::LoadBitmap(_hInst, MAKEINTRESOURCE(idCloseImg));
		BITMAP bmp;
		::GetObject(hBmp, sizeof(bmp), &bmp);
		
		if (_isVertical)
			rect.top = closeButtonRect.top + bmp.bmHeight;		
		else
			rect.right = closeButtonRect.left;

		int bmDpiDynamicalWidth = NppParameters::getInstance()->_dpiManager.scaleX(bmp.bmWidth);
		int bmDpiDynamicalHeight = NppParameters::getInstance()->_dpiManager.scaleY(bmp.bmHeight);
		::SelectObject(hdcMemory, hBmp);
		::BitBlt(hDC, closeButtonRect.left, closeButtonRect.top, bmDpiDynamicalWidth, bmDpiDynamicalHeight, hdcMemory, 0, 0, SRCCOPY);
		::DeleteDC(hdcMemory);
		::DeleteObject(hBmp);
	}

	// Draw image
	HIMAGELIST hImgLst = (HIMAGELIST)::SendMessage(_hSelf, TCM_GETIMAGELIST, 0, 0);

	SIZE charPixel;
	::GetTextExtentPoint(hDC, TEXT(" "), 1, &charPixel);
	int spaceUnit = charPixel.cx;

	if (hImgLst && tci.iImage >= 0)
	{
		IMAGEINFO info;
		int yPos = 0, xPos = 0;
		int marge = 0;

		ImageList_GetImageInfo(hImgLst, tci.iImage, &info);

		RECT & imageRect = info.rcImage;
		
		if (_isVertical)
			xPos = (rect.left + (rect.right - rect.left)/2 + 2) - (imageRect.right - imageRect.left)/2;
		else
			yPos = (rect.top + (rect.bottom - rect.top)/2 + (isSelected?0:2)) - (imageRect.bottom - imageRect.top)/2;

		if (isSelected)
			marge = spaceUnit*2;
		else
			marge = spaceUnit;

		if (_isVertical)
		{
			rect.bottom -= imageRect.bottom - imageRect.top;			
			ImageList_Draw(hImgLst, tci.iImage, hDC, xPos, rect.bottom - marge, isSelected?ILD_TRANSPARENT:ILD_SELECTED);
			rect.bottom += marge;
		}
		else
		{
			rect.left += marge;
			ImageList_Draw(hImgLst, tci.iImage, hDC, rect.left, yPos, isSelected?ILD_TRANSPARENT:ILD_SELECTED);
			rect.left += imageRect.right - imageRect.left;
		}
	}

	bool isStandardSize = (::SendMessage(_hParent, NPPM_INTERNAL_ISTABBARREDUCED, 0, 0) == TRUE);

	if (isStandardSize)
	{
		if (_isVertical)
			SelectObject(hDC, _hVerticalFont);
		else
			SelectObject(hDC, _hFont);
	}
	else
	{
		if (_isVertical)
			SelectObject(hDC, _hVerticalLargeFont);
		else
			SelectObject(hDC, _hLargeFont);
	}

	int Flags = DT_SINGLELINE | DT_NOPREFIX;

	TCHAR decodedLabel[MAX_PATH];

	{
		const TCHAR* in = label;
		TCHAR* out = decodedLabel;

		//This code will read in one character at a time and remove every first ampersand(&).
		//ex. If input "test && test &&& test &&&&" then output will be "test & test && test &&&".
		//Tab's caption must be encoded like this because otherwise tab control would make tab too small or too big for the text.

		while (*in != 0)
		if (*in == '&')
		while (*(++in) == '&')
			*out++ = *in;
		else
			*out++ = *in++;
		*out = '\0';
	}

	if (_drawTabCloseButton)
	{
		Flags |= DT_LEFT;
	}
	else
	{
		if (!_isVertical)
			Flags |= DT_CENTER;
	}
		
	// the following uses pixel values the fix alignments issues with DrawText 
	// and font's that are rotated 90 degrees
	if (isSelected) 
	{
		//COLORREF selectedColor = RGB(0, 0, 255);
		::SetTextColor(hDC, _activeTextColour);

		if (_isVertical)
		{
			rect.bottom -= 2;
			rect.left   += ::GetSystemMetrics(SM_CXEDGE) + 4;
			rect.top    += (_drawTabCloseButton)?spaceUnit:0;

			Flags |= DT_BOTTOM;
		}
		else
		{
			rect.top -= ::GetSystemMetrics(SM_CYEDGE);
			rect.top += 3;
			rect.left += _drawTabCloseButton?spaceUnit:0;

			Flags |= DT_VCENTER;
		}
	} 
	else 
	{
		::SetTextColor(hDC, _inactiveTextColour);
		if (_isVertical)
		{
			rect.top	+= 2;
			rect.bottom += 4;
			rect.left   += ::GetSystemMetrics(SM_CXEDGE) + 2;
		}
		else
		{
			rect.left   += (_drawTabCloseButton)?spaceUnit:0;
		}
			
		Flags |= DT_BOTTOM;
	}
	::DrawText(hDC, decodedLabel, lstrlen(decodedLabel), &rect, Flags);
	::RestoreDC(hDC, nSavedDC);
}