LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  HWND hwndParent = hWndParent;
  HWND hwndImage = hWndImage;

  if (hwnd == hwndParent) {
    if (message == WM_SIZE) {
      ShowWindow(hwndImage, wParam == SIZE_MINIMIZED ? SW_HIDE : SW_SHOW);
    }
    if (message == WM_WINDOWPOSCHANGED) {
      SetWindowPos(hwndImage, hwndParent, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
    }
    return CallWindowProc(
      (long (__stdcall *)(HWND,unsigned int,unsigned int,long))oldProc,
      hwnd,
      message,
      wParam,
      lParam
    );
  }
  switch (message) {
    case WM_PAINT:
    if (bgBitmap.bReady) {
      ECS();

      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(hwnd, &ps);

      if (bgBitmap.iType == MIL_BITMAP) {
        HDC cdc = CreateCompatibleDC(hdc);
        SelectObject(cdc, bgBitmap.hBitmap);
        for (unsigned int x = 0; x < uWndWidth; x += bgBitmap.rPos.right) {
          for (unsigned int y = 0; y < uWndHeight; y += bgBitmap.rPos.bottom) {
            BitBlt(hdc, x, y, bgBitmap.rPos.right, bgBitmap.rPos.bottom, cdc, 0, 0, SRCCOPY);
          }
        }
        DeleteDC(cdc);
      }
      else {
        int r = GetRValue(bgBitmap.cGradientFrom) << 10;
        int g = GetGValue(bgBitmap.cGradientFrom) << 10;
        int b = GetBValue(bgBitmap.cGradientFrom) << 10;
        int dr = ((GetRValue(bgBitmap.cGradientTo) << 10) - r) / (int)uWndHeight * 4;
        int dg = ((GetGValue(bgBitmap.cGradientTo) << 10) - g) / (int)uWndHeight * 4;
        int db = ((GetBValue(bgBitmap.cGradientTo) << 10) - b) / (int)uWndHeight * 4;
        RECT rect;
        rect.left = 0;
        rect.top = 0;
        rect.right = uWndWidth;
        rect.bottom = 4;
        while (rect.top < (int)uWndHeight)
        {
          HBRUSH brush = CreateSolidBrush(RGB(r>>10,g>>10,b>>10));
          FillRect(hdc, &rect, brush);
          DeleteObject(brush);
          rect.top+=4;
          rect.bottom+=4;
          r+=dr;
          g+=dg;
          b+=db;
        }
      }

      myImageList *img = bgBitmap.next;
      while (img) {
        if (img->iType == MIL_TEXT) {
          SetBkMode(hdc, TRANSPARENT);

          SetTextColor(hdc, img->cTextColor);
          SelectObject(hdc, img->hFont);
          DrawText(hdc, img->szText, -1, &img->rPos, DT_TOP | DT_LEFT | DT_NOPREFIX | DT_WORDBREAK);
        }
        else if (img->iType == MIL_BITMAP) {
          HDC cdc = CreateCompatibleDC(hdc);
          SelectObject(cdc, img->hBitmap);
          BitBlt(hdc, img->rPos.left, img->rPos.top, img->rPos.right - img->rPos.left, img->rPos.bottom - img->rPos.top, cdc, 0, 0, SRCCOPY);
          DeleteDC(cdc);
        }
        else {
          COLORREF   cColor;
          HBITMAP    bmAndBack, bmAndObject, bmAndMem, bmSave;
          HBITMAP    bmBackOld, bmObjectOld, bmMemOld, bmSaveOld;
          HDC        hdcMem, hdcBack, hdcObject, hdcTemp, hdcSave;
          POINT      ptSize;

          HBITMAP hBitmap = img->hBitmap;

          hdcTemp = CreateCompatibleDC(hdc);
          SelectObject(hdcTemp, hBitmap);   // Select the bitmap

          ptSize.x = img->rPos.right - img->rPos.left;
          ptSize.y = img->rPos.bottom - img->rPos.top;
          DPtoLP(hdcTemp, &ptSize, 1);  // Convert from device to logical points

          // Create some DCs to hold temporary data.
          hdcBack   = CreateCompatibleDC(hdc);
          hdcObject = CreateCompatibleDC(hdc);
          hdcMem    = CreateCompatibleDC(hdc);
          hdcSave   = CreateCompatibleDC(hdc);

          // Create a bitmap for each DC. DCs are required for a number of
          // GDI functions.

          // Monochrome DC
          bmAndBack   = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

          // Monochrome DC
          bmAndObject = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

          bmAndMem    = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);
          bmSave      = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);

          // Each DC must select a bitmap object to store pixel data.
          bmBackOld   = (HBITMAP)SelectObject(hdcBack, bmAndBack);
          bmObjectOld = (HBITMAP)SelectObject(hdcObject, bmAndObject);
          bmMemOld    = (HBITMAP)SelectObject(hdcMem, bmAndMem);
          bmSaveOld   = (HBITMAP)SelectObject(hdcSave, bmSave);

          // Set proper mapping mode.
          SetMapMode(hdcTemp, GetMapMode(hdc));

          // Save the bitmap sent here, because it will be overwritten.
          BitBlt(hdcSave, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCCOPY);

          // Set the background color of the source DC to the color.
          // contained in the parts of the bitmap that should be transparent
          cColor = SetBkColor(hdcTemp, img->cTransparent);

          // Create the object mask for the bitmap by performing a BitBlt
          // from the source bitmap to a monochrome bitmap.
          BitBlt(hdcObject, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0,
              SRCCOPY);

          // Set the background color of the source DC back to the original
          // color.
          SetBkColor(hdcTemp, cColor);

          // Create the inverse of the object mask.
          BitBlt(hdcBack, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0,
              NOTSRCCOPY);

          // Copy the background of the main DC to the destination.
          BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdc, img->rPos.left, img->rPos.top,
              SRCCOPY);

          // Mask out the places where the bitmap will be placed.
          BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, SRCAND);

          // Mask out the transparent colored pixels on the bitmap.
          BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcBack, 0, 0, SRCAND);

          // XOR the bitmap with the background on the destination DC.
          BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCPAINT);

          // Copy the destination to the screen.
          BitBlt(hdc, img->rPos.left, img->rPos.top, ptSize.x, ptSize.y, hdcMem, 0, 0,
              SRCCOPY);

          // Place the original bitmap back into the bitmap sent here.
          BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcSave, 0, 0, SRCCOPY);

          // Delete the memory bitmaps.
          DeleteObject(SelectObject(hdcBack, bmBackOld));
          DeleteObject(SelectObject(hdcObject, bmObjectOld));
          DeleteObject(SelectObject(hdcMem, bmMemOld));
          DeleteObject(SelectObject(hdcSave, bmSaveOld));

          // Delete the memory DCs.
          DeleteDC(hdcMem);
          DeleteDC(hdcBack);
          DeleteDC(hdcObject);
          DeleteDC(hdcSave);
          DeleteDC(hdcTemp);
        }
        img = img->next;
      }

      LCS();

      EndPaint(hwnd, &ps);
    }
    break;
    case WM_WINDOWPOSCHANGING:
      if (IsWindow(hwndParent))
      {
        LPWINDOWPOS wp = (LPWINDOWPOS) lParam;
        wp->flags |= SWP_NOACTIVATE;
        wp->hwndInsertAfter = hwndParent;
      }
      break;
    case WM_CLOSE:
      DestroyWindow(hwnd);
    break;
    default:
      return DefWindowProc(hwnd, message, wParam, lParam);
  }