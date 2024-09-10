void BDRAW_TransparentBlt (HDC hdc, COLORREF clrTran)
    {
//
// Method #1 -- By Jeff Prosise
//
    HDC hdcImage, hdcAnd, hdcXor, hdcTemp ;
    HBITMAP htAnd, htXor, htTemp ;
    HBITMAP htOldImage, htOldAnd, htOldXor, htOldTemp ;
    int nImage, nAnd, nXor, nTemp ;

    hdcImage   = CreateCompatibleDC (hdc) ;
    htOldImage = (HBITMAP) SelectObject (hdcImage, BoardCfg.htTemp) ;
    nImage     = SetMapMode (hdcImage, GetMapMode (hdc)) ;

    hdcAnd = CreateCompatibleDC (hdc) ;
    nAnd   = SetMapMode (hdcAnd, GetMapMode (hdc)) ;
    htAnd  = CreateBitmap (BoardCfg.nss, BoardCfg.nss, 1, 1, NULL) ;
    htOldAnd = (HBITMAP) SelectObject (hdcAnd, htAnd) ;

    SetBkColor (hdcImage, clrTran) ;
    BitBlt (hdcAnd, 0, 0, BoardCfg.nss, BoardCfg.nss, hdcImage, 0, 0, SRCCOPY) ;

    hdcXor   = CreateCompatibleDC (hdc) ;
    nXor     = SetMapMode (hdcXor, GetMapMode (hdc)) ;
    htXor    = CreateCompatibleBitmap (hdcImage, BoardCfg.nss, BoardCfg.nss) ;
    htOldXor = (HBITMAP) SelectObject (hdcXor, htXor) ;

    BitBlt (hdcXor, 0, 0, BoardCfg.nss, BoardCfg.nss, hdcImage, 0, 0, SRCCOPY ) ;
    BitBlt (hdcXor, 0, 0, BoardCfg.nss, BoardCfg.nss, hdcAnd,   0, 0, 0x220326) ;

    hdcTemp   = CreateCompatibleDC (hdc) ;
    nTemp     = SetMapMode (hdcTemp, GetMapMode (hdc)) ;
    htTemp    = CreateCompatibleBitmap (hdcImage, BoardCfg.nss, BoardCfg.nss) ;
    htOldTemp = (HBITMAP) SelectObject (hdcTemp, htTemp) ;

    BitBlt (hdcTemp, 0, 0, BoardCfg.nss, BoardCfg.nss, hdc,     0, 0, SRCCOPY  ) ;
    BitBlt (hdcTemp, 0, 0, BoardCfg.nss, BoardCfg.nss, hdcAnd,  0, 0, SRCAND   ) ;
    BitBlt (hdcTemp, 0, 0, BoardCfg.nss, BoardCfg.nss, hdcXor,  0, 0, SRCINVERT) ;
    BitBlt (hdc,     0, 0, BoardCfg.nss, BoardCfg.nss, hdcTemp, 0, 0, SRCCOPY  ) ;

    SetMapMode (hdcTemp,  nTemp ) ;
    SetMapMode (hdcXor,   nXor  ) ;
    SetMapMode (hdcAnd,   nAnd  ) ;
    SetMapMode (hdcImage, nImage) ;

    SelectObject (hdcTemp,  htOldTemp ) ;
    SelectObject (hdcXor,   htOldXor  ) ;
    SelectObject (hdcAnd,   htOldAnd  ) ;
    SelectObject (hdcImage, htOldImage) ;

    DeleteObject (hdcTemp ) ;
    DeleteObject (hdcXor  ) ;
    DeleteObject (hdcAnd  ) ;
    DeleteObject (hdcImage) ;

    DeleteObject (htTemp ) ;
    DeleteObject (htXor  ) ;
    DeleteObject (htAnd  ) ;
    }