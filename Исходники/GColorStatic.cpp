void GColorStatic::OnPaint() {

    CPaintDC paintdc(this);

    CDC * cdc = GetDC();
    if (cdc == NULL) {
//        logger.log("cdc null in GColorStatic::OnPaint()");
        return;
    }
    CRect rect;
    GetClientRect(rect);

	COLORREF clr(RGB(212,208,200));
	clr=RGB(170,170,170);



	COLORREF crblack = RGB(0,0,0);
	CBrush brush(crblack);
//	CGdiObject * oldbrush = cdc->SelectObject(brush);
	cdc->FrameRect(rect, &brush);
	rect.DeflateRect(1,1,1,1);
	cdc->FrameRect(rect, &brush);
	rect.DeflateRect(1,1,1,1);
	cdc->FrameRect(rect, &brush);
//	cdc->SelectObject(oldbrush);


	cdc->FillSolidRect( mRect.TopLeft().x, mRect.TopLeft().y,
		mRect.Width(), mRect.Height(), clr);


	ReleaseDC(cdc);



class CUseBrush {
	CGdiObject* m_OldBrush;
	CDC* m_pDC;
public:
	CUseBrush(CDC* pDC, CGdiObject * br) {
		m_pDC=pDC; 
		m_OldBrush=pDC->SelectObject(br);
	}
	~CUseBrush() {
		m_pDC->SelectObject(m_OldBrush);
	}
};

}