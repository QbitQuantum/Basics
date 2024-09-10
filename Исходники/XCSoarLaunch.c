void OnPaint(HWND hWnd, HDC hdc, PAINTSTRUCT *ps)

{

#ifdef USE_WATERMARK

    TODAYDRAWWATERMARKINFO dwi;

#endif



    HDC drawdc, tempdc;

    HBITMAP hDrawBitMap;

    HBITMAP hRetDrawBmp;

//	HBITMAP hRetBmp;

    RECT rect;

    RECT selrect;

//	BITMAP bmp;

    int x, y;

    int i;

    HBRUSH hBrush;



    GetClientRect(hWnd, (LPRECT)&rect);



    drawdc = CreateCompatibleDC(hdc);

    tempdc = CreateCompatibleDC(hdc);

    hDrawBitMap = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);

    hRetDrawBmp = SelectObject(drawdc, hDrawBitMap);



#ifdef USE_WATERMARK



    dwi.hdc = drawdc;

    GetClientRect(hWnd, &dwi.rc);

    dwi.hwnd = hWnd;

    SendMessage(GetParent(hWnd), TODAYM_DRAWWATERMARK, 0, (LPARAM)&dwi);



#else

    FillRect(drawdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

#endif





    x = WinLeftMargin;

    y = WinTopMargin;



    for(i = 0; i < FileListCnt; i++) {



        if(SelItem == i) {

            SetRect(&selrect, x, y, x + IconSizeX + (HMargin * 2),

                    y + IconSizeY + (VMargin * 2));

            hBrush = CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));

            FillRect(drawdc, &selrect, hBrush);

            DeleteObject(hBrush);

        }



        SelectObject(tempdc, FileList[i].bitmap);





#ifdef USE_MASKS

        MaskBlt(drawdc,

                x+HMargin, y+VMargin,

                IconSizeX, IconSizeY,

                tempdc, 0, 0, FileList[i].mask, 0, 0,

                MAKEROP4(0x00AA0029,SRCCOPY));

#else

        TransparentBlt(drawdc,

                       x+HMargin, y+VMargin,

                       IconSizeX, IconSizeY,

                       tempdc, 0, 0, IconSizeX, IconSizeY, RGB(0, 0, 255));

#endif



        x+= IconSizeX+HMargin*2;



    }



    BitBlt(hdc, ps->rcPaint.left, ps->rcPaint.top, ps->rcPaint.right, ps->rcPaint.bottom,

           drawdc, ps->rcPaint.left, ps->rcPaint.top, SRCCOPY);





    SelectObject(drawdc, hRetDrawBmp);

    DeleteObject(hDrawBitMap);

    DeleteDC(drawdc);

    DeleteDC(tempdc);

}