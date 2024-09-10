void 
pntConstel(HDC hdc, DConstel & constel, int x, int y, int size)
{
    int w = size, h = size;
    int centerX = x + w / 2;
    int centerY = y + h / 2;

    int index = constel.current - constel.count + DCONSTEL_HISLEN;
    index %= DCONSTEL_HISLEN;

    // this draw the circles
    SelectObject(hdc, getGreyPen());
    Arc(hdc, x, y, x + w, y + h, 0, 0, 0, 0);
    Arc(hdc, centerX - w / 4, centerY - h / 4,
            centerX + w / 4, centerY + h / 4, 0, 0, 0, 0);
    
    MoveToEx(hdc, x, centerY, NULL); 
    LineTo(hdc, x + w, centerY);
    MoveToEx(hdc, centerX, y, NULL); 
    LineTo(hdc, centerX, y + h);

    for (int i = 0; i < constel.count; i++)
    {
        int b = (i + DCONSTEL_HISLEN - constel.count + 1) * 255 / DCONSTEL_HISLEN;
        // dprintf("%d: %d", i, b);
        double sx = constel.data[index].re * constel.normalOne_1;
        if (sx > 1.0) sx = 1.0; if (sx < -1.0) sx = -1.0;
        double sy = constel.data[index].im * constel.normalOne_1;
        if (sy > 1.0) sy = 1.0; if (sy < -1.0) sy = -1.0;

        int px = centerX + (int)(sx * w / 2);
        int py = centerY + (int)(sy * h / 2);

        pntDrawCross(hdc, px, py, 
                getColor(constel.lightColor, constel.darkColor, b));

        index++;
        index %= DCONSTEL_HISLEN;
    }

    char buf[1000];
    sprintf(buf, "r = %.2f", constel.normalOne);
    pntText(hdc, x + 1, y + h - 15, buf);
}