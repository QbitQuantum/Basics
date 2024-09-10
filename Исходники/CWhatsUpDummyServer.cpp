LRESULT __cdecl CWhatsUpDummyServer::ParentWndProc(HWND hWnd,
													UINT iMessage,
													WPARAM wParam,
													LPARAM lParam)
{
	switch ( iMessage )
	{
		case WM_GM_CONNECT_SERVER_MSG:
			switch ( lParam & 0xFFFF & 0xFFFF )
			{
				case FD_ACCEPT:
					{
						sockaddr_in sockinfo;
						int isockinfolen=16;
						SOCKET sckTemp;
						int iRetVal;

						sckTemp = accept(wParam & 0xFFFF & 0xFFFF, (sockaddr *)&sockinfo, &isockinfolen);

						if ( sckTemp == INVALID_SOCKET )
							return FALSE;

						iRetVal = WSAAsyncSelect(sckTemp, hWnd, WM_GM_CONNECT_SERVER_MSG, FD_READ|FD_CLOSE);

						if ( iRetVal == -1 )
						{
							closesocket(sckTemp);
						}
						return FALSE;
					}
					break;
				case FD_READ:
					{
						char cBUFFER[256];
						int iRecvBytes = recv(wParam & 0xFFFF & 0xFFFF, cBUFFER, sizeof(cBUFFER), 0);

						if ( iRecvBytes <= 0 )
						{
							closesocket(wParam & 0xFFFF & 0xFFFF);
						}
						return FALSE;
					}
					break;
				case FD_CLOSE:
					closesocket(wParam & 0xFFFF & 0xFFFF);
					return FALSE;
				default:
					return FALSE;
			}
			break;
		default:
#ifdef _WIN64
			return CallWindowProcA((WNDPROC)CWhatsUpDummyServer::m_lpOldProc, hWnd, iMessage, wParam, lParam);
#else
			return CallWindowProcA(CWhatsUpDummyServer::m_lpOldProc, hWnd, iMessage, wParam, lParam);
#endif
	}
}