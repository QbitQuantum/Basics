TANY W_CALLBACK KpiVBXPictureBC(OBJECTID self, LPSTR ap)
{
    WORD wType = OBJECT_TYPE(self);
    ATOMID idWidget = KppGetItemName(wType, self);
    HWND hWnd = KpsGetWindowFromWidget(idWidget);
    LPVBXINFO lpVBXInfo = GetVBXInfo(hWnd);
    ATOMID idSlot = va_far_arg(ap, ATOMID);
    ATOMID idValue = va_far_arg(ap, ATOMID);
    ATOMID idPic = Kpp_GetOption(wType, self, idSlot, OPT_DATA);
    TANY res;
    PIC pic;
    
    if (lpVBXInfo && idPic && idPic != lpIDs->idNull)
    {
        long lOldPic;
            
        if (KppGetAtomLong(idPic, &lOldPic))
            lpVBXInfo->lpDisp->FreePicture(lpVBXInfo, (HPIC) lOldPic);
    }
        
    res.type = T_ATOM;
    res.data.atom = idValue;
    
    if (!lpVBXInfo || !IsWindow(hWnd) || !idValue || idValue == lpIDs->idNull)
        return res;
    
    pic.picType = PICTYPE_ICON;
    if (idValue == _SYM(Application))
        pic.picData.icon.hicon = LoadIcon(NULL, IDI_APPLICATION);
    else if (idValue == _SYM(Asterisk))
        pic.picData.icon.hicon = LoadIcon(NULL, IDI_ASTERISK);
    else if (idValue == _SYM(Exclamation))
        pic.picData.icon.hicon = LoadIcon(NULL, IDI_EXCLAMATION);
    else if (idValue == _SYM(Hand))
        pic.picData.icon.hicon = LoadIcon(NULL, IDI_HAND);
    else if (idValue == _SYM(Question))
        pic.picData.icon.hicon = LoadIcon(NULL, IDI_QUESTION);
    else 
    {
        HANDLE hDIB = KpiLoadDIBFromFile(NULLID, idValue);
        HBITMAP hBitmap = NULL;
        
        if (hDIB)
            hBitmap = KpiBitmapFromDib(hDIB, GetStockObject(DEFAULT_PALETTE));
        if (!hBitmap)
        {
            if (hDIB)
                GLOBALFREE(hDIB);
            pic.picType = PICTYPE_NONE;
        }
        else
        {
            pic.picType = PICTYPE_BITMAP;
            pic.picData.bmp.hpal = GetStockObject(DEFAULT_PALETTE);
            pic.picData.bmp.hbitmap = hBitmap;
        }
    }
    
    if (pic.picType != PICTYPE_NONE)
    {
        HPIC hPic = lpVBXInfo->lpDisp->CreatePicture(lpVBXInfo, &pic);

        if (hPic)
            idPic = KppAddAtomLong((long) hPic);
        else
            idPic = lpIDs->idNull;
        
        Kpp_SetOption(wType, self, idSlot, OPT_DATA, idPic);
    }    
    
    return res;
}    