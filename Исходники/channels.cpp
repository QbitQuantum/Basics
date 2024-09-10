void CChannels::Repaint()
{
    char i;
    int  dcant = SaveDC(memdc);
    SelectObject(memdc,bmp);
    for (i=0;i< 8;i++)
        BitBlt(dc, rect.left +  i    * KEY_WIDTH, rect.top             , KEY_WIDTH, KEY_HEIGHT, memdc, (*channel==i)?KEY_WIDTH:0, 0, SRCCOPY);
    for (i=8;i<16;i++)
        BitBlt(dc, rect.left + (i-8) * KEY_WIDTH, rect.top + KEY_HEIGHT, KEY_WIDTH, KEY_HEIGHT, memdc, (*channel==i)?KEY_WIDTH:0, 0, SRCCOPY);
    RestoreDC(memdc,dcant);
}