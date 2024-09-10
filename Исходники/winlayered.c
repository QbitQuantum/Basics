void BitBltMergeLayers(HDC hdcDest, int nWidth, int nHeight, HDC hdcSrc, HWND hWnd)
{
	if (hdcSrc && hdcDest)
	{
		if (hWnd->exstyle & WS_EX_LAYERED)
		{
			DWORD alphaValue;

			POINT ptDelta = {0,0};		
			ptDelta.x = hWnd->winrect.left - hdcDest->pt.x;
			ptDelta.y = hWnd->winrect.top - hdcDest->pt.y;
			
			/*transparency enabled using color key crKey*/
			if (hWnd->dwFlags & LWA_COLORKEY)
			{
				/* mask the color key's most significant byte to 0*/
				COLORREF ColorKey = hWnd->crKey & ~MWROP_EXTENSION;

				if (hWnd->dwFlags & LWA_ALPHA)
				{
					SetAlphaValue(hWnd->bAlpha);
					BitBlt(hdcDest, ptDelta.x, ptDelta.y, nWidth, nHeight, hdcSrc, 0, 0, MWROP_BLENDTRANS | ColorKey);
				} 
				else
				{
					BitBlt(hdcDest, ptDelta.x, ptDelta.y, nWidth, nHeight, hdcSrc, 0, 0, MWROP_SRCTRANSCOPY | ColorKey);
				}				
			}
			else
			{
				alphaValue = (hWnd->dwFlags & LWA_ALPHA) ? (MWROP_BLENDCONSTANT | hWnd->bAlpha) : SRCCOPY;

				if (isLayeredParentWindow(hWnd))
				{
					HRGN hrgn, tempHrgn;
					RECT clientRect, tempRect;
					POINT clientOrigin;
					HWND wp = NULL;						
					
					GetClientRect(currentTargetHWnd, &clientRect);		
					hrgn = CreateRectRgnIndirect(&clientRect);

					/*store screen coordinates of client window for offset*/
					clientOrigin.x = currentTargetHWnd->winrect.left;
					clientOrigin.y = currentTargetHWnd->winrect.top;
					
					/* start with entire client area for clip region,
					 * we then cut out regions occupied by child windows*/
					SelectClipRgn(hdcDest, hrgn);

					/* traverse immediate children to build clip rectangles.
					 * First we call show immediate children to enable
					 * clipping on children for one hide level, check the
					 * clipping to add subtract from clientrect, then disable
					 * back clipping before returning to recursive call
					 */
					ShowImmediateChildWindows(hWnd);
					
					for (wp = hWnd->children; wp; wp=wp->siblings)
					{
						if (wp->unmapcount == 0)
						{
							tempRect.left = wp->winrect.left - clientOrigin.x;
							tempRect.right = wp->winrect.right - clientOrigin.x;
							tempRect.top = wp->winrect.top - clientOrigin.y;
							tempRect.bottom = wp->winrect.bottom - clientOrigin.y;
							
							tempHrgn = CreateRectRgnIndirect(&tempRect);
							ExtSelectClipRgn(hdcDest, tempHrgn, RGN_DIFF);
							DeleteObject(tempHrgn);
						}
					}
					HideImmediateChildWindows(hWnd);

					BitBlt(hdcDest, ptDelta.x, ptDelta.y, nWidth, nHeight, hdcSrc, 0, 0, alphaValue);
	
					SelectClipRgn(hdcDest, NULL);
					DeleteObject(hrgn);
					
				}	
				else
				{
					BitBlt(hdcDest, ptDelta.x, ptDelta.y, nWidth, nHeight, hdcSrc, 0, 0, alphaValue);				
				}
			}
		}
		else
		{
			BitBlt(hdcDest, 0, 0, nWidth, nHeight, hdcSrc, 0, 0, SRCCOPY);		
		}
	}
}