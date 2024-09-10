void CTexLbox::DrawItem(LPDRAWITEMSTRUCT pDraw) 
{
    RECT&   rpl = pDraw->rcItem;
    CDC*    pDC = CDC::FromHandle(pDraw->hDC);
	char	exTra[128]={0};
	char	tOut[64]={0};

	GetText(pDraw->itemID ,tOut);

    if (pDraw->itemState & ODS_SELECTED ) 
    {
        pDC->SetBkColor(RGB(255,255,255));//theApp._color[2]);
    }
    else
    {
        pDC->SetBkColor(theApp._color[2]);
    }
    
    pDC->ExtTextOut(0,0,ETO_OPAQUE, &pDraw->rcItem,"", 0, NULL );

    const char*    pszTn = 0;
    try{
        do{
        TexHandler      th;
        pszTn = _pParent->GetTextureFullName(pDraw->itemID);
        if(_invalides.findelement(string(pszTn))==_invalides.end()
            && th.LoadThisFile(pszTn,0))
        {
            HDC              hdc    = pDraw->hDC;
            HDC              hMemDC = CreateCompatibleDC(hdc);
            BITMAPINFOHEADER bi     = {0};

            bi.biSize        = sizeof(BITMAPINFOHEADER);
            bi.biHeight      = th.n_y; 
            bi.biWidth       = th.n_x;
            bi.biPlanes      = 1;
            bi.biCompression = BI_RGB;
            bi.biBitCount    = 24;
            th.SwapRB();
            HBITMAP hBitmap = CreateDIBitmap(hdc, 
                                             &bi, 
                                             CBM_INIT, 
                                             th.Buffer(), 
                                             (BITMAPINFO*)&bi, 
                                             DIB_RGB_COLORS);
            HBITMAP ob = (HBITMAP)SelectObject(hMemDC, hBitmap);
            if(_bitblt)
            {
                BitBlt(hdc,0,0,th.n_x ,th.n_y, hMemDC,0,0,SRCCOPY);
            }
            else
            {
                StretchBlt( hdc,rpl.left+LEFT_MARG, 
                            rpl.top + LEFT_MARG, 
                            rpl.right-rpl.left-LEFT_MARG*2, 
					        rpl.bottom-rpl.top-LEFT_MARG*2,
					        hMemDC,0,0,th.n_x ,th.n_y, SRCCOPY);
            }


            ::SelectObject(hMemDC, ob);
            ::DeleteObject(hBitmap) ;
            ::DeleteDC(hMemDC);

            _pParent->_bpp   = th.n_bpp;
            _pParent->_sz.cx = th.n_x;
            _pParent->_sz.cy = th.n_y;
            _pParent->_name  = pszTn;

            if(pDraw->itemID!=-1 && GetItemData(pDraw->itemID) == 0)
            {
                SetItemData(pDraw->itemID, MAKELONG(th.n_x, th.n_y));
            }

       		    
            pDC->DrawText(tOut, strlen(tOut), &pDraw->rcItem, DT_CENTER|DT_BOTTOM|DT_SINGLELINE);
        }
	    else
	    {
		    if(pDraw->itemID != -1)
		    {
			    _stprintf(exTra, _T("Cannot Load '%s'"),tOut);
			    pDC->DrawText(exTra,strlen(exTra),&pDraw->rcItem, DT_CENTER|DT_BOTTOM|DT_SINGLELINE);
                _invalides << pszTn;
		    }
        }



	    if(((th.n_y & (th.n_y-1))!= 0)|| ((th.n_x & (th.n_x-1))!=0))
	    {
		    CPen* pO = (CPen*)pDC->SelectObject(&_errorPen);
		    pDC->MoveTo(CPoint(rpl.right-8,rpl.bottom-8));
		    pDC->LineTo(CPoint(rpl.right-2,rpl.bottom-2));
		    pDC->MoveTo(CPoint(rpl.right-8,rpl.bottom-2));
		    pDC->LineTo(CPoint(rpl.right-2,rpl.bottom-8));
		    pDC->SelectObject(pO);
	    }

        InflateRect(&pDraw->rcItem,-1,-1);
        pDC->Draw3dRect(&pDraw->rcItem, theApp._color[1],theApp._color[2]);
        th.Reset();
	    _curSel = pDraw->itemID;
        }while(0);
    }catch(...)
    {
        PostMessage(LB_DELETESTRING,pDraw->itemID,0);
        if(pszTn)
        {
            _invalides << pszTn;
        }
    }
}