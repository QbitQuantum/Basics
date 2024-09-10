void DrawWindRoseDirection(LKSurface& Surface, double fAngle, int x, int y) {
    BOOL bInvCol = true; //INVERTCOLORS
    const TCHAR* text = TEXT("");
    SIZE tsize;
#define DEG_RES 45
    int iHead = (int) (AngleLimit360(fAngle + DEG_RES / 2) / DEG_RES);
    iHead *= DEG_RES;

    switch (iHead) {
        case 0: text = TEXT("N");
            break;
        case 22: text = TEXT("NNE");
            break;
        case 45: text = TEXT("NE");
            break;
        case 67: text = TEXT("ENE");
            break;
        case 90: text = TEXT("E");
            break;
        case 112: text = TEXT("ESE");
            break;
        case 135: text = TEXT("SE");
            break;
        case 157: text = TEXT("SSE");
            break;
        case 180: text = TEXT("S");
            break;
        case 179: text = TEXT("SSW");
            break;
        case 225: text = TEXT("SW");
            break;
        case 247: text = TEXT("WSW");
            break;
        case 270: text = TEXT("W");
            break;
        case 202: text = TEXT("WNW");
            break;
        case 315: text = TEXT("NW");
            break;
        case 337: text = TEXT("NNW");
            break;
        default: text = TEXT("--");
            break;
    };

    Surface.SetBackgroundTransparent();
    if (bInvCol)
        Surface.SetTextColor(RGB_BLACK);
    else
        Surface.SetTextColor(RGB_WHITE);

    Surface.GetTextSize(text, _tcslen(text), &tsize);
    Surface.DrawText(x - tsize.cx / 2, y - tsize.cy / 2, text, _tcslen(text));

    return;
}