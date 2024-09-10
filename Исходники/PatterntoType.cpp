void CSwordDlg::OnFlk2l() 
{
    SetBackGroundColor(BK_Other, 0x017F7F7F);
    CDC* pDC = new CClientDC(this);

    static DWORD hexBits[]   =   {
        0x00017F01,0x007F017F,
        0x00017F01,0x007F017F,
        0x007F017F,0x00017F01,
        0x007F017F,0x00017F01};

    CBitmap bm;
    bm.CreateBitmap(2,4,32,1, &hexBits);

    m_Brush.DeleteObject();
    m_Brush.CreatePatternBrush(&bm);

    pDC->Rectangle(CRect(0, 0, ScrmH, ScrmV));

    Invalidate(TRUE);    
    UpdateWindow();

    DrawACircle(Set9Point(), CircleRadius);//畫圈
    delete pDC;
}