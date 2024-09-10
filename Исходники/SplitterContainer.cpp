LRESULT SplitterContainer::runProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_CREATE :
			_splitter.init(_hInst, _hSelf, _splitterSize, _ratio, _dwSplitterStyle);
			return TRUE;
		
		case WM_COMMAND :
		{
			switch (LOWORD(wParam)) 
			{
				case ROTATION_A_GAUCHE:
					rotateTo(LEFT);
					return TRUE;
				case ROTATION_A_DROITE:
					rotateTo(RIGHT);
					return TRUE;
			}
			return TRUE;
		}
		case WM_RESIZE_CONTAINER :
		{
			RECT rc0, rc1;
			getClientRect(rc0);

			rc1.top = rc0.top += _y;
			rc1.bottom = rc0.bottom;
			rc1.left = rc0.left += _x;
			rc1.right = rc0.right;

			if (_dwSplitterStyle & SV_VERTICAL)
			{
				if (wParam != 0)
				{
					rc0.right = int(wParam);

					rc1.left = int(wParam) + _x + _splitter.getPhysicalSize();
					rc1.right = rc1.right - rc1.left + _x;
				}
			}
			else //SV_HORIZONTAL
			{
				if (lParam != 0)
				{
					rc0.bottom = int(lParam); 

					rc1.top   = int(lParam) + _y + _splitter.getPhysicalSize();
					rc1.bottom = rc1.bottom - rc1.top + _y;
				}
			}
			_pWin0->reSizeTo(rc0);
			_pWin1->reSizeTo(rc1);

			::InvalidateRect(_splitter.getHSelf(), NULL, TRUE);
			return TRUE;
		}
		
		case WM_DOPOPUPMENU :
		{
			if ((_splitterMode != LEFT_FIX) && (_splitterMode != RIGHT_FIX) )
			{
				POINT p;
				::GetCursorPos(&p);
				
				if (!_hPopupMenu)
				{
					POINT p;
					::GetCursorPos(&p);
					_hPopupMenu = ::CreatePopupMenu();
					::InsertMenu(_hPopupMenu, 1, MF_BYPOSITION, ROTATION_A_GAUCHE, TEXT("Rotate to left"));
					::InsertMenu(_hPopupMenu, 0, MF_BYPOSITION, ROTATION_A_DROITE, TEXT("Rotate to right"));
				}
				
				::TrackPopupMenu(_hPopupMenu, TPM_LEFTALIGN, p.x, p.y, 0, _hSelf, NULL);
			}
			return TRUE;
		}

		case WM_GETSPLITTER_X :
        {
            if (_splitterMode == LEFT_FIX)
                return MAKELONG(_pWin0->getWidth(), LEFT_FIX);
            else if (_splitterMode == RIGHT_FIX)
            {
                int x = getWidth()-_pWin1->getWidth();
                if (x < 0)
                    x = 0;
                return MAKELONG(x, RIGHT_FIX);
            }
            else
			    return MAKELONG(0, DYNAMIC);
         
        }

		case WM_GETSPLITTER_Y :
        {
            if (_splitterMode == LEFT_FIX)
                return MAKELONG(_pWin0->getHeight(), LEFT_FIX);
            else if (_splitterMode == RIGHT_FIX)
            {
                int y = getHeight()-_pWin1->getHeight();
                if (y < 0)
                    y = 0;
                return MAKELONG(y, RIGHT_FIX);
            }
            else
			    return MAKELONG(0, DYNAMIC);
        }

		case WM_LBUTTONDBLCLK:
		{			
			POINT pt;
			::GetCursorPos(&pt);
			::ScreenToClient(_splitter.getHSelf(), &pt);
			
			Window* targetWindow;
			
			if(this->isVertical())
				targetWindow = pt.x < 0?_pWin0:_pWin1;
			else
				targetWindow = pt.y < 0?_pWin0:_pWin1;
			
			HWND parent = ::GetParent(getHSelf());
			
			::SendMessage(parent, NPPM_INTERNAL_SWITCHVIEWFROMHWND, 0, (LPARAM)targetWindow->getHSelf());
			::SendMessage(parent, WM_COMMAND, IDM_FILE_NEW, 0);
			return TRUE;
		}

		default :
			return ::DefWindowProc(_hSelf, message, wParam, lParam);
	}
}