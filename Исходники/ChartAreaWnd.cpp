void CChartAreaWnd::DrawRubberRectangle( int x1, int y1, int x2, int y2 )
{
    int  surroundDelta = 2;
    CDC* pDC = GetDC();

    pDC->SetBkColor( RGB(0,0,0) );              
    pDC->SetROP2( R2_XORPEN );                  
    pDC->SelectStockObject(NULL_BRUSH);         
    CPen pen( PS_SOLID, 2, RGB(255, 255, 0) );  
    CPen* oldPen = pDC->SelectObject( &pen );

    pDC->Rectangle( x1-surroundDelta, y1-surroundDelta, 
                    x2+surroundDelta, y2+surroundDelta );

    pDC->SelectObject( oldPen );
}