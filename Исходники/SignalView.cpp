void CSignalView::ReDrawmap(CDC *pDC)
{
    if(pDC==NULL)
        return;
    double *pdata = m_SignalData.GetData();
    double *pcolor = m_SignalColor.GetData();
    size_t length = m_SignalData.GetDataSize();
    int base = m_SignalRect.Height()/2;
    pDC->FillSolidRect(0,0,m_SignalRect.Width()  ,m_SignalRect.Height(),RGB(255,255,255));
    COLORREF precolor  = (int)pcolor[0];
    COLORREF curcolor = precolor;
    CPen drawpen;
    int prey = 0;
    if(pdata[0]<=0)
    {
        prey = m_MinValue==0?(pdata[0]*(-1.0)+base):(pdata[0]/m_MinValue*base+base);
    }
    else
        prey = m_MaxValue==0?(base-pdata[0]):(base-pdata[0]/m_MaxValue*base);
    drawpen.CreatePen(PS_SOLID , 1 , precolor);
    for (int i=1; i<length; i++)
    {
        if(precolor!=curcolor)
        {
            drawpen.DeleteObject();
            drawpen.CreatePen(PS_SOLID ,1,curcolor);
            precolor = curcolor;
        }
        pDC->SelectObject(drawpen);
        int cury = 0;
        if(m_MaxValue==0&&m_MinValue==0)
        {
            cury = (int)(pdata[i]*(-1.0)+base);
        }
        else
        {
            cury = (pdata[i]-m_MinValue)*m_SignalRect.Height()/(m_MaxValue-m_MinValue)+base-m_MeanValue;
        }
        pDC->MoveTo(i-1,prey);
        pDC->LineTo(i,cury);
        prey = cury;
        curcolor = (int)pcolor[i];
    }
    drawpen.DeleteObject();
}