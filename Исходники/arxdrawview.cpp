void CArxdrawView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

    CPoint local = point;
    m_lastPoint = local;

    // find out which object is selected
    // 0 = circle
    // 1 - square
    // 2 - up triangle
    // 3 - down triangle
    int objType = -1;

    if (point.x < 65)
    { // circle or square
      if (point.y < 45)
        objType = 0;
      else
        objType = 1;
    }
    else
    {
      if (point.y < 45)
        objType = 2;
      else
        objType = 3;
    }
    
    COleDataSource *pSource = generateDataSource(objType, CRect(CPoint(0,0), CSize(m_sliderVal, m_sliderVal )));
    CMyOverrideDropTarget myDT;
    CDropSource myDS;
    
    // Start overriding AutoCAD's Droptarget
    if (!acedStartOverrideDropTarget(&myDT))
        TRACE("Error in overriding Custom drop target!\n");
    
   
    DROPEFFECT dwEffect = pSource->DoDragDrop( DROPEFFECT_NONE |DROPEFFECT_MOVE | DROPEFFECT_COPY, NULL, &myDS);

    // End overriding AutoCAD default droptarget
    if (!acedEndOverrideDropTarget(&myDT))
        TRACE("Error in ending override drop target\n");

    delete pSource;
}