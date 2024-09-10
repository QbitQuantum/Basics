static void calculate_polyline(void)
{
    WINT points, i;
    RECT rect;
    POINT p[9];
    HPEN hOldPen;
    do {
        rect.left = 0x7fff;
        rect.top = 0x7fff;
        rect.right = 0;
        rect.bottom = 0;
        points = get_rand(2, 9);
        for (i=0; i<points; i++)
        {
            p[i].x = get_rand(0, xMax);
            p[i].y = get_rand(0, yMax);
            if (p[i].x < rect.left)
                rect.left = p[i].x;
            if (p[i].x > rect.right)
                rect.right = p[i].x;
            if (p[i].y < rect.top)
                rect.top = p[i].y;
            if (p[i].y > rect.bottom)
                rect.bottom = p[i].y;
        }
        hOldPen = SelectObject(hMemDC, create_pen());
        SetROP2(hMemDC, get_rand(1,17));
        Polyline(hMemDC, &p[0], points);
        DeleteObject(SelectObject(hMemDC, hOldPen));
        if (TestSemaphore(&PainterRequired) < 0)
        {
            InvalidateRect(hWnd, &rect, FALSE);
            UpdateWindow(hWnd);
        }
    } while ((TestSemaphore(&DemoRun)) && (!TestSemaphore(&SingleRun)));
    
    if (!TestSemaphore(&SingleRun));
        Signal(&Done);
}