LRESULT CALLBACK MainDialog::PictureBox_OnMessage(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
		case STM_SETIMAGE:
			::InvalidateRect(hWnd, NULL, FALSE);
			break;

		case WM_PAINT:
			{
				PAINTSTRUCT ps = {NULL};
				HDC hdc = ::BeginPaint(hWnd, &ps);

				HBITMAP hBitmap = (HBITMAP)::SendMessage(hWnd, (UINT)STM_GETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)0L);
				if(!hBitmap) break;

				RECT rcClient = {NULL};
				::GetClientRect(hWnd, &rcClient);
				int iWidth = (rcClient.right - rcClient.left);
				int iHeight = (rcClient.bottom - rcClient.top);
	
				TransparentBlt(hdc, 0, 0, iWidth, iHeight, hBitmap, 0, 0, RGB(255, 0, 255), NULL);

				::EndPaint(hWnd, &ps);
			}
			break;
	}
	return ::CallWindowProc(m_hDefaultPictureProc, hWnd, Message, wParam, lParam);
};