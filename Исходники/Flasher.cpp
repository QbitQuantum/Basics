// Process window messages
LRESULT CALLBACK Flasher::WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	// This is a static method, so we don't know which instantiation we're 
	// dealing with. We use Allen Hadden's ([email protected]) suggestion 
	// from a newsgroup to get the pseudo-this.
	Flasher *_this = (Flasher *) GetWindowLong(hwnd, GWL_USERDATA);

	switch (iMsg) {

	case WM_CREATE:
		return 0;

	case WM_SOCKEVENT:
		{
			assert(HIWORD(lParam) == 0);

			// A new socket created by accept might send messages to
			// this procedure. We can ignore them.
			if(wParam != _this->m_sock) {
				return 0;
			}

			switch(lParam) {
			case FD_ACCEPT:
				{
					SOCKET hNewSock;
					char username[256];
					hNewSock = accept(_this->m_sock, NULL, NULL);
					// make it blocking
					WSAAsyncSelect(hNewSock, hwnd, 0, 0);
					u_long blk = 0;
					int res = ioctlsocket(hNewSock, FIONBIO, &blk);
					assert(res == 0);

					CloseScreenSaver();

					// Se if the server's sending a user name
					int namelen = recv(hNewSock, username, 250, 0);
					if (namelen >= 0) 
						username[namelen] = 0;
					//vnclog.Print(2, _T("Flash for '%s'\n"), username);

					closesocket(hNewSock);


					// flash
					// Receive a DC for the root window
					HDC hrootdc = ::GetDC(NULL);

					HBRUSH holdbrush = (HBRUSH) SelectObject(hrootdc, 
						(HBRUSH) GetStockObject(BLACK_BRUSH));
					
					// Find the size.
					RECT rect;
					GetClipBox(hrootdc, &rect);
					int barwidth = (rect.right - rect.left) / 10;
					int barheight = max( 
						(rect.bottom - rect.top) / 10,
						FLASHFONTHEIGHT);
					HFONT oldfont = (HFONT) SelectObject(hrootdc, _this->m_hfont);

					// Flash the screen
					::Beep(440,50);
										
					Rectangle(hrootdc, rect.left, rect.top, 
								  rect.right, barheight);
					Rectangle(hrootdc, rect.left,  rect.bottom-barheight, 
								  rect.right, rect.bottom);
					Rectangle(hrootdc, rect.left,  rect.top+barheight, 
								  barwidth, rect.bottom-barheight);
					Rectangle(hrootdc, rect.right-barwidth, rect.top+barheight, 
								  rect.right, rect.bottom-barheight);

					RECT topbar;
					SetRect(&topbar, rect.left, rect.top, 
								  rect.right, barheight);
					int i = 0;
					if (namelen > 0) {
						int oldmode = SetBkMode(hrootdc, TRANSPARENT);
						COLORREF oldcolor = SetTextColor(hrootdc, 
							RGB(scalechar(username[0])/(i+1), scalechar(username[1])/(i+1), scalechar(username[2])/(i+1)));
						DrawText(hrootdc, username, -1, &topbar, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						SetTextColor(hrootdc, oldcolor);
						SetBkMode(hrootdc, oldmode);
					}
					GdiFlush();
					SelectObject(hrootdc, holdbrush);
					::Sleep(1000);
						
					SelectObject(hrootdc, oldfont);
					InvalidateRect(0, &rect, TRUE);

					::ReleaseDC(NULL, hrootdc);
					break;
				}
			case FD_CLOSE:
				//vnclog.Print(2, _T("Flasher connection closed\n"));
				Log.Add(_MESSAGE_, "Flasher connection closed");
				DestroyWindow(hwnd);
				break;
			}
			
			return 0;
		}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}