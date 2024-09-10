void CScanView::onDrawSelf(CDCHandle dc)
{
    CDC memDC;
    CBitmap memBitmap;
    memDC.CreateCompatibleDC(dc);
    CRect clientRECT;
    this->GetClientRect(&clientRECT);

    memBitmap.CreateCompatibleBitmap(dc,clientRECT.Width() , clientRECT.Height());
    HBITMAP oldBitmap = memDC.SelectBitmap(memBitmap);

    HPEN oldPen = memDC.SelectStockPen(DC_PEN);
   
    HBRUSH oldBrush = memDC.SelectStockBrush(NULL_BRUSH);
    HFONT  oldFont  = memDC.SelectFont(stdfont);

    memDC.SetBkMode(0);
    memDC.SetTextColor(RGB(90, 90, 90));
    memDC.SetTextAlign(TA_CENTER | TA_BASELINE);

    memDC.SetDCPenColor(RGB(60,60,60));

    CPoint centerPt(clientRECT.Width()/2, clientRECT.Height()/2);
    const int maxPixelR = min(clientRECT.Width(), clientRECT.Height())/2 - DEF_MARGIN;
    const float distScale = (float)maxPixelR/_current_display_range;

    char txtBuffer[100];

    // plot rings
    for (int angle = 0; angle<360; angle += 30) {
        float rad = (float)(angle*PI/180.0);

        float endptX = sin(rad)*(maxPixelR+DEF_MARGIN/2) + centerPt.x;
        float endptY = centerPt.y - cos(rad)*(maxPixelR+DEF_MARGIN/2);

        memDC.MoveTo(centerPt);
        memDC.LineTo((int)endptX, (int)endptY);

        sprintf(txtBuffer, "%d", angle);
        memDC.TextOutA((int)endptX, (int)endptY, txtBuffer);

    }

    for (int plotR = maxPixelR; plotR>0; plotR-=DISP_RING_ABS_DIST)
    {
        memDC.Ellipse(centerPt.x-plotR, centerPt.y-plotR,
            centerPt.x+plotR, centerPt.y+plotR);

        sprintf(txtBuffer, "%.1f", (float)plotR/distScale);
        memDC.TextOutA(centerPt.x, centerPt.y-plotR, txtBuffer);
    }

    memDC.SelectStockBrush(DC_BRUSH);
    memDC.SelectStockPen(NULL_PEN);

    int picked_point = 0;
    float min_picked_dangle = 100;

    for (int pos =0; pos < (int)_scan_data.size(); ++pos) {
        float distPixel = _scan_data[pos].dist*distScale;
        float rad = (float)(_scan_data[pos].angle*PI/180.0);
        float endptX = sin(rad)*(distPixel) + centerPt.x;
        float endptY = centerPt.y - cos(rad)*(distPixel);

        float dangle = fabs(rad - _mouse_angle);

        if (dangle<min_picked_dangle) {
            min_picked_dangle = dangle;
            picked_point = pos;
        }

        int brightness = (_scan_data[pos].quality<<1) + 128;
        if (brightness>255) brightness=255;

        memDC.FillSolidRect((int)endptX-1,(int)endptY-1, 2, 2,RGB(0,brightness,brightness));
    }

    memDC.SelectFont(bigfont);

    memDC.SetTextAlign(TA_LEFT | TA_BASELINE);
    memDC.SetTextColor(RGB(255,255,255));

    sprintf(txtBuffer, "%.1f Hz (%d RPM)", _scan_speed, (int)(_scan_speed*60));
    memDC.TextOutA(DEF_MARGIN, DEF_MARGIN + 40, txtBuffer);

    if ((int)_scan_data.size() > picked_point) {
        float distPixel = _scan_data[picked_point].dist*distScale;
        float rad = (float)(_scan_data[picked_point].angle*PI/180.0);
        float endptX = sin(rad)*(distPixel) + centerPt.x;
        float endptY = centerPt.y - cos(rad)*(distPixel);


        memDC.SetDCPenColor(RGB(129,10,16));
        memDC.SelectStockPen(DC_PEN);
        memDC.MoveTo(centerPt.x,centerPt.y);
        memDC.LineTo((int)endptX,(int)endptY);
        memDC.SelectStockPen(NULL_PEN);

        memDC.FillSolidRect((int)endptX-1,(int)endptY-1, 2, 2,RGB(255,0,0));

        memDC.SetTextColor(RGB(255,0,0));
        sprintf(txtBuffer, "Current: %.2f Deg: %.2f", _scan_data[picked_point].dist,  _scan_data[picked_point].angle);
        memDC.TextOutA(DEF_MARGIN, DEF_MARGIN + 20, txtBuffer);
    }

    dc.BitBlt(0, 0, clientRECT.Width(), clientRECT.Height()
        , memDC, 0, 0, SRCCOPY);

    memDC.SelectFont(oldFont);
    memDC.SelectBrush(oldBrush);
    memDC.SelectPen(oldPen);
    memDC.SelectBitmap(oldBitmap);

    
}