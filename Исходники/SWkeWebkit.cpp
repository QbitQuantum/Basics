 void SWkeWebkit::OnPaint(IRenderTarget *pRT)
 {
     CRect rcClip;
     pRT->GetClipBox(&rcClip);
     CRect rcClient;
     GetClientRect(&rcClient);
     CRect rcInvalid;
     rcInvalid.IntersectRect(&rcClip,&rcClient);
     HDC hdc=pRT->GetDC();
     m_pWebView->paint(hdc,rcInvalid.left,rcInvalid.top,rcInvalid.Width(),rcInvalid.Height(),rcInvalid.left-rcClient.left,rcInvalid.top-rcClient.top,true);
     pRT->ReleaseDC(hdc);
 }