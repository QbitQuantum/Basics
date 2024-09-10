//---------------------------------------------------------------------------
void __fastcall TCodeView::PBoxPaint(TObject *Sender)
{
	if( !m_pFont ) return;

	CWaitCursor w;
	Graphics::TBitmap *pBmp = new Graphics::TBitmap;
    pBmp->Width = PBox->Width;
    pBmp->Height = PBox->Height;
	TCanvas *pCanvas = pBmp->Canvas;
	BOOL eud = SBOut->Down;
	if( !m_Base && !eud ) memset(m_tPfx, 0, sizeof(m_tPfx));
	SetPBoxFont(pCanvas);
	if( !eud ) SetMBCP(m_pFont->Charset);
	int x, y, xx, yy, fw, fh;
    char bf[16];
	int c = 0;
	for( y = 0; y < 16; y++ ){
		for( x = 0; x < 16; x++ ){
			if( eud ){
				DrawChar(pCanvas, c, FALSE);
            }
            else {
				if( !m_Base && (_mbsbtype((const unsigned char *)&c, 0) == _MBC_LEAD) ){
					m_tPfx[c] = TRUE;
    	        	DrawCursor(pCanvas, c, FALSE);
        	    }
            	else {
					DrawChar(pCanvas, c, FALSE);
            	}
            }
           	c++;
        }
    }
	pCanvas->Font = Font;
    pCanvas->Pen->Color = clBlack;
	::SetBkMode(pCanvas->Handle, TRANSPARENT);
    for( y = 0; y < 16; y++ ){
		wsprintf(bf, "%X", y);
		fw = pCanvas->TextWidth(bf);
        fh = pCanvas->TextHeight(bf);
        xx = m_XW1 + y*m_XW + (m_XW-fw)/2;
        yy = (m_YW1-fh)/2;
        pCanvas->TextOut(xx, yy, bf);

		if( eud ){
			c = GetEUDC(y, 1) & 0xfff0;
            if( c ){
		        wsprintf(bf, "%04x", c);
            }
            else {
				bf[0] = 0;
            }
        }
		else if( m_Base ){
	        wsprintf(bf, "%04x", y*16 + m_Base);
        }
        else {
	        wsprintf(bf, "%02X", y*16);
        }
		fw = pCanvas->TextWidth(bf);
        fh = pCanvas->TextHeight(bf);
        xx = (m_XW1-fw)/2;
        yy = m_YW1 + y*m_YW + (m_YW-fh)/2;
        pCanvas->TextOut(xx, yy, bf);

		pCanvas->Pen->Width = y ? 1 : 2;
		pCanvas->MoveTo(0, m_YW1 + y*m_YW);
        pCanvas->LineTo(PBox->Width, m_YW1 + y*m_YW);
		pCanvas->MoveTo(m_XW1 + y*m_XW, 0);
        pCanvas->LineTo(m_XW1 + y*m_XW, PBox->Height);
    }
    PBox->Canvas->Draw(0, 0, pBmp);
    delete pBmp;
	m_pfxCount = 0;
    for( x = 0; x < 256; x++ ){
		if( m_tPfx[x] ){
			m_tPfxIdx[m_pfxCount] = x;
        	m_pfxCount++;
        }
    }
	if( m_pfxCount != UDMB->Max ) UDMB->Max = short(m_pfxCount - 1);
}