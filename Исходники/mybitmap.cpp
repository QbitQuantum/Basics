void MyBitmap::PaintCenter(CDC* pDC, const CRect& rect)
{
    int x = (rect.left+rect.right)/2 - m_width/2;
    int y = (rect.top+rect.bottom)/2 - m_height/2;
    CRect centered(x,y,x+m_width,y+m_height);
    CRect centeredopt;
    centeredopt.IntersectRect(&centered,&rect);
    if(centeredopt.left>rect.left || centeredopt.top>rect.top)
        pDC->FillSolidRect(&rect,m_clrbkg);
    Paint(pDC, centeredopt, false);
}