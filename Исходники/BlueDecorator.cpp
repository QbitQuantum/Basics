void BlueDecorator::FillBackGround(void )
{
    Layer* pcView = GetLayer();

    Rect  cOBounds = pcView->GetBounds();

    Color32_s sFillColor =  m_bHasFocus ? Color32_s(62,101,172,255):Color32_s(191,191,191,255) ;


    Color32_s col_Light  = m_bHasFocus ? Color32_s (32,71,142,255):Color32_s(191,191,191,255) ;
    Color32_s col_Dark   = m_bHasFocus ? Color32_s (62,101,172,255):Color32_s(221,221,221,255);

    Point Left  = Point(cOBounds.left+1,  cOBounds.top+1);
    Point Right = Point(cOBounds.right-1, cOBounds.top+1);

    Color32_s col_Grad = col_Light;
    Color32_s col_Step = Color32_s( (col_Light.red-col_Dark.red)/15,
                                    (col_Light.green-col_Dark.green)/15,
                                    (col_Light.blue-col_Dark.blue)/15, 0 );

    for (int i=0; i<25; i++)
    {
        pcView->SetFgColor( col_Grad );
        pcView->DrawLine( Left, Right );
        Left.y  += 1;
        Right.y += 1;
        col_Grad.red   -= col_Step.red;
        col_Grad.green -= col_Step.green;
        col_Grad.blue  -= col_Step.blue;
    }


    // left
    pcView->FillRect( Rect(cOBounds.left,cOBounds.top+m_vTopBorder,
                           cOBounds.left+m_vLeftBorder,cOBounds.bottom+m_vLeftBorder),sFillColor);
    // right
    pcView->FillRect( Rect(cOBounds.right-m_vRightBorder,cOBounds.top+m_vTopBorder,
                           cOBounds.right,cOBounds.bottom),sFillColor);
    // bottom
    pcView->FillRect( Rect(cOBounds.left,cOBounds.bottom-m_vBottomBorder,
                           cOBounds.right,cOBounds.bottom),sFillColor);
}