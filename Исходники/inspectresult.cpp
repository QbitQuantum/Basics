void InspectResult::Paint(HDC hdc, int BrowserRealWidth, int BrowserRealHeight, int BrowserDrawWidth, int BrowserDrawHeight, int BrowserScrollX, int BrowserScrollY, int BrowserLeft, int BrowserTop)
{
    //worker_log(std::string("Paint<<") + std::to_string(x) + std::string("<<") + std::to_string(y));
    if(!active)
        return;

    POINT pt;
    SelectObject(hdc, GetStockObject(DC_PEN));
    SetDCPenColor(hdc, RGB(255,0,0));

    int     x1 = (float)x * (float)BrowserDrawWidth / (float)BrowserRealWidth
            ,y1 = (float)y * (float)BrowserDrawHeight / (float)BrowserRealHeight
            ,width1 = (float)width* (float)BrowserDrawWidth / (float)BrowserRealWidth
            ,height1 = (float)height* (float)BrowserDrawHeight / (float)BrowserRealHeight;

    if(x1<=0)
       x1 = 1;

    if(y1<=0)
       y1 = 1;

    if(x1 + width1 >= BrowserDrawWidth)
       width1 = BrowserDrawWidth - x1 - 1;

    if(y1 + height1 >= BrowserDrawHeight)
       height1 = BrowserDrawHeight - y1 - 1;

    MoveToEx(hdc, BrowserLeft + x1, BrowserTop + y1, &pt);
    LineTo(hdc, BrowserLeft + x1, BrowserTop + y1 + height1);

    MoveToEx(hdc, BrowserLeft + x1, BrowserTop + y1, &pt);
    LineTo(hdc, BrowserLeft + x1 + width1, BrowserTop + y1);

    MoveToEx(hdc, BrowserLeft + x1, BrowserTop + y1 + height1, &pt);
    LineTo(hdc, BrowserLeft + x1 + width1, BrowserTop + y1 + height1);

    MoveToEx(hdc, BrowserLeft + x1 + width1, BrowserTop + y1, &pt);
    LineTo(hdc, BrowserLeft + x1 + width1, BrowserTop + y1 + height1);

    /*MoveToEx(hdc, 0, 30, &pt);
    LineTo(hdc, 500, 30);

    MoveToEx(hdc, 502, 221, &pt);
    LineTo(hdc, WindowWidth, 221);*/
}