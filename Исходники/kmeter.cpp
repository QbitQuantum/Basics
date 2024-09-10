void Kmeter::drawMarkersStereo(Graphics& g, String& strMarker, int x, int y, int width, int height)
{
    g.setColour(Colours::white);
    g.drawFittedText(strMarker, x + 36, y, width, height, Justification::centred, 1, 1.0f);

    g.setColour(Colours::grey);

    int nMarkerY = y + 5;
    int nStart = 0;
    int nEnd = 0;
    int nWidth = 0;

    nWidth = 9;
    nStart = x + 25;
    nEnd = nStart + nWidth;

    for (int nMarkerX = nStart; nMarkerX < nEnd; nMarkerX++)
    {
        g.setPixel(nMarkerX, nMarkerY);
    }

    nStart = x + 70;
    nEnd = nStart - nWidth;

    for (int nMarkerX = nStart; nMarkerX > nEnd; nMarkerX--)
    {
        g.setPixel(nMarkerX, nMarkerY);
    }
}