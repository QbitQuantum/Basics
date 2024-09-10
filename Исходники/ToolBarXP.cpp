///////////////////////////////////////////////////////////////////////////////
// Paint the toolbar
void CToolBarXP::OnPaint ()
{
    if ( m_bDelayedButtonLayout )
    {
        Layout();
    }
    CPaintDC cpDC (this);
    CBufferDC cDC (cpDC);
    CRect rcClip;
    cDC.GetClipBox (rcClip);
    cDC.SetBkMode (TRANSPARENT);
    cDC.SelectObject (CFont::FromHandle ((HFONT)GetStockObject (DEFAULT_GUI_FONT)));

    cDC.FillSolidRect (rcClip, HLS_TRANSFORM (::GetSysColor (COLOR_3DFACE), 20, 0));

    CPoint ptCursor;
    ::GetCursorPos (&ptCursor);
    ScreenToClient (&ptCursor);

    CClientRect rcClient (this);
    HIMAGELIST m_hImageList = (HIMAGELIST)DefWindowProc (TB_GETIMAGELIST, 0, 0);
    TBBUTTON tbbutton;
    int nCount = DefWindowProc (TB_BUTTONCOUNT, 0, 0);
    int nHotItem = GetToolBarCtrl().GetHotItem();

    for ( int i = 0; i < nCount; i++ )
    {
        VERIFY(DefWindowProc (TB_GETBUTTON, i, (LPARAM)&tbbutton));

        if ( !IS_VISIBLE(tbbutton) )
        {
            continue;
        }
        CRect rcButton;
        VERIFY(DefWindowProc (TB_GETITEMRECT, i, (LPARAM)&rcButton));

        if ( !CRect().IntersectRect (rcClip, rcButton) )
        {
            continue;
        }
        bool bOver = nHotItem == i && IS_ENABLED(tbbutton);
        bool bPressed = false;

        if ( IS_INDETERMINATE(tbbutton) )
        {
            CPenDC pen (cDC, ::GetSysColor (COLOR_3DDKSHADOW));

            cDC.MoveTo (rcButton.left, rcButton.bottom);
            cDC.LineTo (rcButton.left, rcButton.top);
            cDC.LineTo (rcButton.right-1, rcButton.top);
            cDC.LineTo (rcButton.right-1, rcButton.bottom-1);
            cDC.LineTo (rcButton.left, rcButton.bottom-1);
            bOver = true;
        }
        else if ( bOver || IS_CHECKED(tbbutton) )
        {
            bPressed = KEYDOWN(VK_LBUTTON) && rcButton.PtInRect (ptCursor);

            if ( IS_DROPDOWN(tbbutton) && bPressed )
            {
                bPressed = ptCursor.x < rcButton.right-13;

                if ( bPressed )
                {
                    rcButton.right -= 13;
                }
            }
            COLORREF crHighLight = ::GetSysColor (COLOR_HIGHLIGHT);
            CPenDC pen (cDC, crHighLight);
            CBrushDC brush (cDC, bPressed||(bOver&&IS_CHECKED(tbbutton)) ? HLS_TRANSFORM (crHighLight, +50, -50) : (bOver ? HLS_TRANSFORM (crHighLight, +70, -57) : HLS_TRANSFORM (crHighLight, +80, -66)));

            cDC.Rectangle (&rcButton);

            if ( IS_DROPDOWN(tbbutton) )
            {
                if ( bPressed )
                {
                    int nLeft = rcButton.left;

                    rcButton.left = rcButton.right-1;
                    rcButton.right += 13;

                    brush.Color (HLS_TRANSFORM (crHighLight, +70, -66));
                    cDC.Rectangle (&rcButton);

                    rcButton.left = nLeft;
                }
                else
                {
                    cDC.MoveTo (rcButton.right-14, rcButton.top);
                    cDC.LineTo (rcButton.right-14, rcButton.bottom);
                }
            }
        }
        if ( IS_SEPARATOR(tbbutton) )
        {
            CPenDC pen (cDC, HLS_TRANSFORM (::GetSysColor (COLOR_3DFACE), -15, 0));

            if ( IS_WRAP(tbbutton) )
            {
                cDC.MoveTo (rcClient.left+2, rcButton.bottom-4);
                cDC.LineTo (rcClient.right-2, rcButton.bottom-4);
            }
            else
            {
                cDC.MoveTo ((rcButton.right+rcButton.left)/2-1, rcButton.top+2);
                cDC.LineTo ((rcButton.right+rcButton.left)/2-1, rcButton.bottom-2);
            }
        }
        else if ( !IS_CONTROL(tbbutton) )
        {
            if ( IS_DROPDOWN(tbbutton) )
            {
                CPenDC pen (cDC, ( bOver && !IS_INDETERMINATE(tbbutton) ) ? RGB(0,0,0) : ::GetSysColor (IS_ENABLED(tbbutton) ? COLOR_BTNTEXT : COLOR_GRAYTEXT));

                cDC.MoveTo (rcButton.right-9, (rcButton.top+rcButton.bottom)/2-1);
                cDC.LineTo (rcButton.right-4, (rcButton.top+rcButton.bottom)/2-1);
                cDC.MoveTo (rcButton.right-8, (rcButton.top+rcButton.bottom)/2);
                cDC.LineTo (rcButton.right-5, (rcButton.top+rcButton.bottom)/2);
                cDC.SetPixel (rcButton.right-7, (rcButton.top+rcButton.bottom)/2+1, pen.Color());

                rcButton.right -= 14;
            }
            if ( tbbutton.iBitmap >= 0 )
            {
                if ( !IS_ENABLED(tbbutton) || (bOver && !bPressed) )
                {
                    HICON hIcon = ImageList_ExtractIcon (NULL, m_hImageList, tbbutton.iBitmap);
                    cDC.DrawState (CPoint (rcButton.left + ( bOver ? 4 : 3 ), rcButton.top + ( bOver ? 4 : 3 )), m_sizeImage, hIcon, DSS_MONO, CBrush (bOver ? (IS_INDETERMINATE(tbbutton) ? HLS_TRANSFORM (::GetSysColor (COLOR_3DFACE), -20, 0) : HLS_TRANSFORM (::GetSysColor (COLOR_HIGHLIGHT), +50, -66)) : HLS_TRANSFORM (::GetSysColor (COLOR_3DFACE), -27, 0)));
                    DestroyIcon (hIcon);
                }
                if ( IS_ENABLED(tbbutton) )
                {
                    ::ImageList_Draw (m_hImageList, tbbutton.iBitmap, cDC.m_hDC,
                                      rcButton.left + ( (bOver && !bPressed) ? 2 : 3 ), rcButton.top + ( (bOver && !bPressed) ? 2 : 3 ), ILD_TRANSPARENT);
                }
            }
        }
    }
}