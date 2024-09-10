int DrawMaxButton(HDC hdc, RECT *pRect, COLORREF clrBorder, COLORREF clrBack, COLORREF clrBtn, int isZoomed)
{
    HBRUSH hBackBrush = CreateSolidBrush (clrBack);
    HBRUSH hBorderBrush = CreateSolidBrush (clrBorder);
    HBRUSH hBtBrush = CreateSolidBrush (clrBtn); 
    int width = pRect->right - pRect->left;
    int height = pRect->bottom - pRect->top;
    RECT rc1, rc2;
    rc1.top = pRect->top + height/5;
    rc1.bottom = pRect->top + height * 2 /3 + height/4;
    rc1.left = pRect->left + width*2/7;
    rc1.right = pRect->right - width*2/7;

    rc2 = rc1;
    rc2.top += 3;
    rc2.bottom -= 3;
    rc2.left += 3;
    rc2.right -= 3;

    FillRect(hdc, pRect, hBackBrush);
    FrameRect(hdc, pRect, hBorderBrush);
    if (isZoomed){     
        OffsetRect(&rc1, 3, -1);
        OffsetRect(&rc2, 3, -1);
        FillRect(hdc, &rc1, hBtBrush);
        FrameRect(hdc, &rc1, hBorderBrush);
        FillRect(hdc, &rc2, hBackBrush);
        FrameRect(hdc, &rc2, hBorderBrush);

        OffsetRect(&rc1, -4, 3);
        OffsetRect(&rc2, -4, 3);
        FillRect(hdc, &rc1, hBtBrush);
        FrameRect(hdc, &rc1, hBorderBrush);
        FillRect(hdc, &rc2, hBackBrush);
        FrameRect(hdc, &rc2, hBorderBrush);
    }else{
        FillRect(hdc, &rc1, hBtBrush);
        FrameRect(hdc, &rc1, hBorderBrush);
        FillRect(hdc, &rc2, hBackBrush);
        FrameRect(hdc, &rc2, hBorderBrush);
    }
    
    DeleteObject(hBackBrush);
    DeleteObject(hBorderBrush);
    DeleteObject(hBtBrush);
    return 0;
}