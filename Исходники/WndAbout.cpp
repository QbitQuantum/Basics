// window message processing procedure
LRESULT CALLBACK WndAbout::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
        case WM_CREATE:
        {
            // resize window so that client area := 400x300
            {
                RECT cRect;
                RECT wRect;

                GetClientRect(hwnd, &cRect);
                GetWindowRect(hwnd, &wRect);

                uint32 difW = (wRect.right  - wRect.left) - (cRect.right);
                uint32 difH = (wRect.bottom - wRect.top)  - (cRect.bottom);

                MoveWindow(hwnd, wRect.left, wRect.top, difW + 400, difH + 300, TRUE);
            }

            EnableWindow(m_parent, FALSE);

            HDC hDC = GetDC(hwnd);

            int nHeight = -MulDiv(8, GetDeviceCaps(hDC, LOGPIXELSY), 72);

			m_hFont = CreateFont(nHeight, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_ROMAN, "Verdana");

            m_BackBmp = CreateCompatibleBitmap(hDC, 400, 300);

            // decompress jpeg, convert to bitmap resource
            {
                HRSRC hSrc = FindResource(NULL, MAKEINTRESOURCE(IDR_JPEG_ABOUT), "JPEG");
                HGLOBAL hRes = LoadResource(NULL, hSrc);
                uint08 *jpgData = (uint08*)LockResource(hRes);

                uint32 jpgFileSize = SizeofResource(NULL, hSrc);
                uint32 bmpFileSize = 0;
                uint32 bmpWidth, bmpHeight;

                uint08 *bmpBuff = jpeg2bmp(jpgData, jpgFileSize, &bmpFileSize, &bmpWidth, &bmpHeight);

                // create bitmap
                {
                    BITMAPINFO BmpInfo;

                    BmpInfo.bmiHeader.biSize          = sizeof(BITMAPINFO) - sizeof(RGBQUAD);
                    BmpInfo.bmiHeader.biWidth         = bmpWidth;
                    BmpInfo.bmiHeader.biHeight        = 0 - (int)bmpHeight;
                    BmpInfo.bmiHeader.biPlanes        = 1;
                    BmpInfo.bmiHeader.biBitCount      = 24;
                    BmpInfo.bmiHeader.biCompression   = BI_RGB;
                    BmpInfo.bmiHeader.biSizeImage     = 0;
                    BmpInfo.bmiHeader.biXPelsPerMeter = 0;
                    BmpInfo.bmiHeader.biYPelsPerMeter = 0;
                    BmpInfo.bmiHeader.biClrUsed       = 0;
                    BmpInfo.bmiHeader.biClrImportant  = 0;

                    SetDIBits(hDC, m_BackBmp, 0, bmpHeight, bmpBuff, &BmpInfo, DIB_RGB_COLORS);
                }

                free(bmpBuff);

                UnlockResource(hRes);
            }

            m_BackDC  = CreateCompatibleDC(hDC);

            m_OrigBmp  = (HBITMAP)SelectObject(m_BackDC, m_BackBmp);

            ReleaseDC(hwnd, hDC);

            SetClassLong(hwnd, GCL_HICON, (LONG)LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_CXBX)));
        }
        break;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;

            BeginPaint(hwnd, &ps);

            HDC hDC = GetDC(hwnd);

            HGDIOBJ OrgObj = SelectObject(hDC, m_hFont);

            // draw bitmap
            BitBlt(hDC, 0, 0, 400, 300, m_BackDC, 0, 0, SRCCOPY);

            SelectObject(hDC, OrgObj);

            if(hDC != NULL)
                ReleaseDC(hwnd, hDC);

            EndPaint(hwnd, &ps);
        }
        break;

        case WM_LBUTTONUP:
            SendMessage(hwnd, WM_CLOSE, 0, 0);
			break;

        case WM_CLOSE:
            EnableWindow(m_parent, TRUE);
            DestroyWindow(hwnd);
			break;

        case WM_DESTROY:
            DeleteObject(m_hFont);
            PostQuitMessage(0);
			break;

        default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

    return 0;
}