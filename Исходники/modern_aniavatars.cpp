static void _AniAva_RenderAvatar(ANIAVA_WINDOWINFO * dat, HDC hdcParent /* = NULL*/, RECT * rcInParent /* = NULL */ )
{
	if (dat->bPaused>0)	{	dat->bPended=TRUE;	return; 	}
	else dat->bPended=FALSE;
	
	if ( IMMEDIATE_DRAW && hdcParent == NULL ) return;
	GdiFlush();
#ifdef _DEBUG
	__AniAva_DebugRenderStrip();
#endif
	if (dat->bPlaying && IsWindowVisible(dat->hWindow))
	{
		POINT ptWnd={0};
		SIZE szWnd={dat->rcPos.right-dat->rcPos.left,dat->rcPos.bottom-dat->rcPos.top};
		BLENDFUNCTION bf={AC_SRC_OVER, 0,g_CluiData.bCurrentAlpha*dat->bAlpha/256, AC_SRC_ALPHA };
		POINT pt_from={0,0};
		HDC hDC_animation=GetDC(NULL);
		HDC copyFromDC;
		RECT clistRect;
		HDC tempDC=NULL;
		HBITMAP hBmp;
		HBITMAP hOldBmp;

		/*
		int x=bf.SourceConstantAlpha;
		x=(49152/(383-x))-129;
		x=min(x,255);	x=max(x,0);
		bf.SourceConstantAlpha=x;
		*/
		if ( AniAva.bFlags == 0 ) //simple and fastest method - no borders, round corners and etc. just copy
		{
			pt_from.x=dat->ptFromPoint.x+dat->currentFrame*dat->sizeAvatar.cx;
			pt_from.y=dat->ptFromPoint.y;
			copyFromDC=AniAva.hAniAvaDC;
		}
		else
		{
			// ... need to create additional hDC_animation
			HRGN hRgn=NULL;
			int cornerRadius= AniAva.cornerRadius;
			tempDC	= CreateCompatibleDC( NULL );
			hBmp	= ske_CreateDIB32( szWnd.cx, szWnd.cy );
			hOldBmp	= (HBITMAP)SelectObject(tempDC,hBmp);
			if ( AniAva.bFlags & AAO_ROUND_CORNERS )
			{
				if (!cornerRadius)  //auto radius
					cornerRadius = min(szWnd.cx, szWnd.cy )/5;
			}
			if ( AniAva.bFlags & AAO_HAS_BORDER )
			{
				// if has borders - create region (round corners) and fill it, remember internal as clipping
				HBRUSH hBrush = CreateSolidBrush( AniAva.borderColor );
				HBRUSH hOldBrush = (HBRUSH)SelectObject( tempDC, hBrush );
				HRGN rgnOutside = CreateRoundRectRgn( 0, 0, szWnd.cx+1, szWnd.cy+1, cornerRadius<<1, cornerRadius<<1);
				hRgn=CreateRoundRectRgn( 1, 1, szWnd.cx, szWnd.cy, cornerRadius<<1, cornerRadius<<1);
				CombineRgn( rgnOutside,rgnOutside,hRgn,RGN_DIFF);
				FillRgn( tempDC, rgnOutside, hBrush);
				ske_SetRgnOpaque( tempDC, rgnOutside, TRUE);
				SelectObject(tempDC, hOldBrush);
				DeleteObject(hBrush);
				DeleteObject(rgnOutside);
			} 
			else if ( cornerRadius > 0 )
			{
				// else create clipping area (round corners)
				hRgn=CreateRoundRectRgn(0, 0, szWnd.cx+1, szWnd.cy+1, cornerRadius<<1, cornerRadius<<1);
			}
			else
			{
				hRgn=CreateRectRgn(0, 0, szWnd.cx+1, szWnd.cy+1);
			}
			// select clip area
			if ( hRgn )
				ExtSelectClipRgn(tempDC, hRgn, RGN_AND);

			if ( AniAva.bFlags & AAO_OPAQUE)
			{
				// if back color - fill clipping area
				HBRUSH hBrush = CreateSolidBrush( AniAva.bkgColor );
				HBRUSH hOldBrush = (HBRUSH)SelectObject( tempDC, hBrush );
				FillRgn( tempDC, hRgn, hBrush );
				ske_SetRgnOpaque( tempDC, hRgn, TRUE );
			}
			// draw avatar
			if ( !(AniAva.bFlags & AAO_OPAQUE) )
				BitBlt(tempDC,0, 0, szWnd.cx, szWnd.cy , AniAva.hAniAvaDC , dat->ptFromPoint.x+dat->sizeAvatar.cx*dat->currentFrame, dat->ptFromPoint.y, SRCCOPY);
			else
			{
				BLENDFUNCTION abf={AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
				ske_AlphaBlend(tempDC,0, 0, szWnd.cx, szWnd.cy , AniAva.hAniAvaDC, dat->ptFromPoint.x+dat->sizeAvatar.cx*dat->currentFrame, dat->ptFromPoint.y, szWnd.cx, szWnd.cy, abf);
			}
			// reset clip area
			if ( hRgn )
			{
				DeleteObject(hRgn);
				hRgn = CreateRectRgn(0, 0, szWnd.cx, szWnd.cy);
				SelectClipRgn(tempDC, hRgn);
				DeleteObject(hRgn);
			}

			if ( ( AniAva.bFlags & AAO_HAS_OVERLAY )
				  && ( dat->overlayIconIdx != -1 )
				  && ( AniAva.overlayIconImageList ) )
			{
				// if overlay - draw overlay icon
				// position - on avatar
				int x=szWnd.cx-ICON_WIDTH;
				int y=szWnd.cy-ICON_HEIGHT;
				ske_ImageList_DrawEx(AniAva.overlayIconImageList,
					dat->overlayIconIdx&0xFFFF,
					tempDC, x, y, ICON_WIDTH, ICON_HEIGHT,
					CLR_NONE, CLR_NONE, ILD_NORMAL);
			}
			copyFromDC=tempDC;
		}
		// intersect visible area
		// update layered window
		GetWindowRect(pcli->hwndContactTree, &clistRect);
		if (dat->rcPos.top<0)
		{
			pt_from.y+=-dat->rcPos.top;
			szWnd.cy+=dat->rcPos.top;
		}
		if (dat->rcPos.bottom>clistRect.bottom-clistRect.top)
		{
			szWnd.cy-=(dat->rcPos.bottom-(clistRect.bottom-clistRect.top));
		}
		ptWnd.x=dat->rcPos.left+clistRect.left;
		ptWnd.y=(dat->rcPos.top>0 ? dat->rcPos.top :0)+clistRect.top;
		if (szWnd.cy>0)
		{
			if ( hdcParent && rcInParent && IMMEDIATE_DRAW )
			{
				if ( AniAva.bFlags & AAO_OPAQUE )
					BitBlt( hdcParent, rcInParent->left, rcInParent->top, szWnd.cx, szWnd.cy, copyFromDC, pt_from.x, pt_from.y, SRCCOPY);
				else
				{
					BLENDFUNCTION abf={AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
					ske_AlphaBlend( hdcParent, rcInParent->left, rcInParent->top, szWnd.cx, szWnd.cy, copyFromDC, pt_from.x, pt_from.y, szWnd.cx, szWnd.cy, abf);
				}
			}
			else if (!g_proc_UpdateLayeredWindow(dat->hWindow, hDC_animation, &ptWnd, &szWnd, copyFromDC, &pt_from, RGB(0,0,0), &bf, ULW_ALPHA ))
			{
				LONG exStyle;
				exStyle=GetWindowLong(dat->hWindow,GWL_EXSTYLE);
				exStyle|=WS_EX_LAYERED;
				SetWindowLong(dat->hWindow,GWL_EXSTYLE,exStyle);
				if ( !IMMEDIATE_DRAW )
					SetWindowPos( pcli->hwndContactTree, dat->hWindow, 0, 0, 0, 0, SWP_ASYNCWINDOWPOS | SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSENDCHANGING );
				g_proc_UpdateLayeredWindow(dat->hWindow, hDC_animation, &ptWnd, &szWnd, copyFromDC, &pt_from, RGB(0,0,0), &bf, ULW_ALPHA );
			}

			g_CluiData.fAeroGlass = false;
			CLUI_UpdateAeroGlass();
		}
		else
		{
			dat->bPlaying=FALSE;
		}
		ReleaseDC(NULL,hDC_animation);
		if (tempDC)
		{
			SelectObject(tempDC, hOldBmp);
			DeleteObject(hBmp);
			DeleteDC(tempDC);
		}
	}
	if (!dat->bPlaying)
	{
		ShowWindow(dat->hWindow, SW_HIDE);
		KillTimer(dat->hWindow,2);  //stop animation till set pos will be called
	}
	GdiFlush();
}