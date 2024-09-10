void CXTFlatComboBox::OnNoFlickerPaint(CDC* pDC)   
{   
    ASSERT(pDC != NULL);   
       
    // Get the client area to paint.    
    CRect rcClient;   
    GetClientRect(&rcClient);   
   
    CDC memDC; // memory device context.    
   
    // Create the memory DC, set Map Mode    
    memDC.CreateCompatibleDC(pDC);   
    memDC.SetMapMode(pDC->GetMapMode());   
   
    // Create a bitmap big enough to hold the window's image    
    CBitmap bitmap;   
    bitmap.CreateCompatibleBitmap(pDC, rcClient.Width(), rcClient.Height());   
   
    // Select the bitmap into the memory DC    
    CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);   
   
    // Repaint the background, this takes the place of WM_ERASEBKGND.    
    memDC.FillSolidRect(rcClient, m_clr3DFace);   
   
    // Let the window do its default painting...    
    CWnd::DefWindowProc( WM_PAINT, (WPARAM)memDC.m_hDC, 0 );   
   
    if (m_bFlatLook)   
    {   
        if (PointInRect() || m_bHasFocus) {   
            DrawCombo(&memDC, RAISED, m_clr3DShadow, m_clr3DHilight);   
        }   
        else {   
            DrawCombo(&memDC, NORMAL, m_clr3DFace, m_clr3DFace);   
        }   
    }   
   
    // Blt it    
    pDC->BitBlt(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(),   
        &memDC, rcClient.left, rcClient.top, SRCCOPY);               
   
    // Select the original bitmap back in    
    memDC.SelectObject(pOldBitmap);   
   
    // Clean up    
    bitmap.DeleteObject();   
    memDC.DeleteDC();   
}   