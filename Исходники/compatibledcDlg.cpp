void CcompatibledcDlg::OnBnClickedOk()
{
    CRect rc;
    m_show.GetClientRect(rc);
    CDC* pdc = m_show.GetDC();
    pdc->SetMapMode(MM_ANISOTROPIC);
    CDC memdc;
    memdc.CreateCompatibleDC(pdc);
    
    CBitmap membitmap;
    membitmap.CreateCompatibleBitmap(pdc,rc.Width(),rc.Height());
    membitmap.LoadBitmap("f:\\back.bmp");
    
    
    CBitmap* poldbitmap = memdc.SelectObject(&membitmap);
    
    
    //memdc.FillSolidRect(0,0,rc.Width(),rc.Height(),RGB(122,122,122));
    memdc.MoveTo(0,0);
    memdc.LineTo(rc.Width(),rc.Height());
    
    
    pdc->BitBlt(0,0,rc.Width(),rc.Height(),&memdc,0,0,SRCCOPY);
    
    
    pdc->SelectObject(poldbitmap);
    
}