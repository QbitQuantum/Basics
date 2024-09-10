	//------------------------------------------------------------------
	LRESULT WinOISInputSupport::windowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		// The user has dropped files on the window
		switch(uMsg)
		{
			case WM_DROPFILES:
			{
				HDROP hDrop = (HDROP)wParam;
				WCHAR szFile[MAX_PATH] = { 0 };
				UINT fcount = DragQueryFileW(hDrop, 0xFFFFFFFF, NULL, 0);

				for(UINT i = 0; i < fcount; i++) 
				{
					DragQueryFileW(hDrop, i, szFile, MAX_PATH);

					String filename;
					if(sizeof(String::value_type) == sizeof(WCHAR))
					{
						filename.assign( (const String::value_type*) szFile);
					}
					else
					{
						CodepageConverter::ByteBuffer buf( (const uint8*) szFile, wcslen(szFile) * sizeof(WCHAR) );
						mUtf16Converter->bufferToUnicode(filename, buf);
					}

					InputSystem::getSingleton()._injectFileDrop( filename );
				}

				::DragFinish(hDrop);
				return 0; // the message was processed
			}
		
			// Hide WIN32 cursor when the cursor pos is within the window
			case WM_SETCURSOR:
			{
				int hitTest = LOWORD(lParam);
				if(hitTest == HTCLIENT)
				{
					hideWinCursor();
					return TRUE; // to halt further processing 
				}
				break;
			}

			case WM_MOUSELEAVE:
			{
				notifyMouseTrackingDisabled();
				MouseEvent evt2(mMouseAbsX, mMouseAbsY, mMouseAbsZ);
				InputSystem::getSingleton()._injectMouseLeave(evt2);
				break;
			}

			case WM_NCMOUSEMOVE:
			{
				MouseEvent evt2(mMouseAbsX, mMouseAbsY, mMouseAbsZ);
				InputSystem::getSingleton()._injectMouseLeave(evt2);
				break;
			}

			case WM_MOUSEMOVE:
			{
				enableMouseTracking(); // we need to determine when the cursor moves outside the window
				int newAbsX = GET_X_LPARAM(lParam);
				int newAbsY = GET_Y_LPARAM(lParam);
				if(mMouseAbsX != newAbsX || mMouseAbsY != newAbsY)
				{
					mMouseAbsX = GET_X_LPARAM(lParam);
					mMouseAbsY = GET_Y_LPARAM(lParam);
					MouseEvent evt2(mMouseAbsX, mMouseAbsY, mMouseAbsZ);
					InputSystem::getSingleton()._injectMouseMove(evt2);
				}
				break;
			}

			case WM_MOUSEWHEEL:
			{
				mMouseAbsZ += GET_WHEEL_DELTA_WPARAM(wParam);
				MouseEvent evt2(mMouseAbsX, mMouseAbsY, mMouseAbsZ);
				InputSystem::getSingleton()._injectMouseMove(evt2);
				break;
			}

			case WM_LBUTTONDOWN:
			case WM_LBUTTONDBLCLK: // Double-clicking the left mouse button actually generates a sequence of four messages: WM_LBUTTONDOWN, WM_LBUTTONUP, WM_LBUTTONDBLCLK, and WM_LBUTTONUP (MSDN).
			{
				mMousePressed[0] = true;
				mMouseAbsX = GET_X_LPARAM(lParam);
				mMouseAbsY = GET_Y_LPARAM(lParam);
				MouseEvent evt2(mMouseAbsX, mMouseAbsY, mMouseAbsZ, MouseButton::LEFT);
				InputSystem::getSingleton()._injectMousePress(evt2);
				break;
			}
			case WM_LBUTTONUP:
			{
				mMousePressed[0] = false;
				mMouseAbsX = GET_X_LPARAM(lParam);
				mMouseAbsY = GET_Y_LPARAM(lParam);
				MouseEvent evt2(mMouseAbsX, mMouseAbsY, mMouseAbsZ, MouseButton::LEFT);
				InputSystem::getSingleton()._injectMouseRelease(evt2);
				break;
			}

			case WM_RBUTTONDOWN:
			{
				mMousePressed[1] = true;
				mMouseAbsX = GET_X_LPARAM(lParam);
				mMouseAbsY = GET_Y_LPARAM(lParam);
				MouseEvent evt2(mMouseAbsX, mMouseAbsY, mMouseAbsZ, MouseButton::RIGHT);
				InputSystem::getSingleton()._injectMousePress(evt2);
				break;
			}
			case WM_RBUTTONUP:
			{
				mMousePressed[1] = false;
				mMouseAbsX = GET_X_LPARAM(lParam);
				mMouseAbsY = GET_Y_LPARAM(lParam);
				MouseEvent evt2(mMouseAbsX, mMouseAbsY, mMouseAbsZ, MouseButton::RIGHT);
				InputSystem::getSingleton()._injectMouseRelease(evt2);
				break;
			}

			case WM_MBUTTONDOWN:
			{
				mMousePressed[2] = true;
				mMouseAbsX = GET_X_LPARAM(lParam);
				mMouseAbsY = GET_Y_LPARAM(lParam);
				MouseEvent evt2(mMouseAbsX, mMouseAbsY, mMouseAbsZ, MouseButton::MIDDLE);
				InputSystem::getSingleton()._injectMousePress(evt2);
				break;
			}
			case WM_MBUTTONUP:
			{
				mMousePressed[2] = false;
				mMouseAbsX = GET_X_LPARAM(lParam);
				mMouseAbsY = GET_Y_LPARAM(lParam);
				MouseEvent evt2(mMouseAbsX, mMouseAbsY, mMouseAbsZ, MouseButton::MIDDLE);
				InputSystem::getSingleton()._injectMouseRelease(evt2);
				break;
			}
		}
	
		// call Ogre's window procedure
		return CallWindowProc((WNDPROC)mOldWindowProc, mHwnd, uMsg, wParam, lParam);
	}