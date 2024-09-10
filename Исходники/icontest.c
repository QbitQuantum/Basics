LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hDC;
    HICON hIcon;
    HGDIOBJ hOld;
    HDC hMemDC;
    CURSORINFO cursorinfo;
    ICONINFO iconinfo;
    BITMAP bmp;
    RECT rc;
    CHAR str[20];

    switch(msg)
    {
    case WM_PAINT:
      hDC = BeginPaint(hWnd, &ps);
      SelectObject(hDC, tf);
      SetBkMode(hDC, TRANSPARENT);

      TextOut(hDC, 160, 10, file, strlen(file));
      TextOut(hDC, 15, 85, titleDrwIco, strlen(titleDrwIco));
      TextOut(hDC, 160, 85, titleMask, strlen(titleMask));
      TextOut(hDC, 300, 85, titleXor, strlen(titleXor));

      hIcon = LoadImage(NULL, "icon.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE|LR_LOADFROMFILE);
      DrawIcon(hDC,50,50,hIcon);

      hMemDC = CreateCompatibleDC(hDC);
      GetIconInfo(hIcon, &iconinfo);
      DestroyIcon(hIcon);

      hOld = SelectObject(hMemDC, iconinfo.hbmMask);
      BitBlt(hDC, 200, 50, 32, 32, hMemDC, 0, 0, SRCCOPY);
      SelectObject(hMemDC, iconinfo.hbmColor);
      BitBlt(hDC, 350, 50, 32, 32, hMemDC, 0, 0, SRCCOPY);

      DeleteObject(iconinfo.hbmMask);
      DeleteObject(iconinfo.hbmColor);

      TextOut(hDC, 145, 150, res, strlen(res));
      TextOut(hDC, 15, 225, titleDrwIco, strlen(titleDrwIco));
      TextOut(hDC, 160, 225, titleMask, strlen(titleMask));
      TextOut(hDC, 300, 225, titleXor, strlen(titleXor));

      hIcon = LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE);
      DrawIcon(hDC,50,190,hIcon);

      GetIconInfo(hIcon, &iconinfo);
      DestroyIcon(hIcon);

      SelectObject(hMemDC, iconinfo.hbmMask);
      BitBlt(hDC, 200, 190, 32, 32, hMemDC, 0, 0, SRCCOPY);
      SelectObject(hMemDC, iconinfo.hbmColor);
      BitBlt(hDC, 350, 190, 32, 32, hMemDC, 0, 0, SRCCOPY);

      DeleteObject(iconinfo.hbmMask);
      DeleteObject(iconinfo.hbmColor);

      cursorinfo.cbSize = sizeof(CURSORINFO);
      if(GetCursorInfo(&cursorinfo))
      {
        if(cursorinfo.hCursor && cursorinfo.flags)
        {
          TextOut(hDC, 160, 290, cursor, strlen(cursor));
          DrawIcon(hDC, 50, 330, cursorinfo.hCursor);
          GetIconInfo(cursorinfo.hCursor, &iconinfo);
          TextOut(hDC, 15, 365, titleDrwIco, strlen(titleDrwIco));

          sprintf(str, "Hotspot: %ld; %ld", iconinfo.xHotspot, iconinfo.yHotspot);
          TextOut(hDC, 15, 380, str, strlen(str));

          if(iconinfo.hbmMask)
          {
            GetObjectW(iconinfo.hbmMask, sizeof(BITMAP), &bmp);
            SelectObject(hMemDC, iconinfo.hbmMask);
            BitBlt(hDC, 200, 330, bmp.bmWidth, bmp.bmHeight, hMemDC, 0, 0, SRCCOPY);
            DeleteObject(iconinfo.hbmMask);
            TextOut(hDC, 160, 365 - 32 + bmp.bmHeight, cursormask, strlen(cursormask));

            sprintf(str, "%dBPP", bmp.bmBitsPixel);
            TextOut(hDC, 160, 380 - 32 + bmp.bmHeight, str, strlen(str));
          }

          if(iconinfo.hbmColor)
          {
            GetObjectW(iconinfo.hbmColor, sizeof(BITMAP), &bmp);
            SelectObject(hMemDC, iconinfo.hbmColor);
            BitBlt(hDC, 350, 330, bmp.bmWidth, bmp.bmHeight, hMemDC, 0, 0, SRCCOPY);
            DeleteObject(iconinfo.hbmColor);
            TextOut(hDC, 300, 365 - 32 + bmp.bmHeight, cursorcolor, strlen(cursorcolor));

            sprintf(str, "%dBPP", bmp.bmBitsPixel);
            TextOut(hDC, 300, 380 - 32 + bmp.bmHeight, str, strlen(str));
          }
        }
      }

      SelectObject(hMemDC, hOld);

      DeleteObject(hMemDC);
      EndPaint(hWnd, &ps);
    break;

    case WM_TIMER:
      rc.left = 0;
      rc.top = 330;
      rc.right = 480;
      rc.bottom = 480;
      InvalidateRect(hWnd, &rc, TRUE);
      break;

    case WM_DESTROY:
      PostQuitMessage(0);
    break;

    default:
      return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}