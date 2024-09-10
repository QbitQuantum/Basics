void Test_GetRandomRgn_CLIPRGN()
{
    HDC hdc;
    HRGN hrgn1, hrgn2;
    INT ret;
    RECT rect;

    hrgn1 = CreateRectRgn(11, 17, 23, 42);
    if (!hrgn1)
    {
        printf("Coun't create a region\n");
        return;
    }

    hdc = CreateCompatibleDC(0);
    if (!hdc)
    {
        printf("Coun't create a dc\n");
        return;
    }

    ret = GetRandomRgn(hdc, hrgn1, CLIPRGN);
    ok_int(ret, 0);
    GetRgnBox(hrgn1, &rect);
    ok_long(rect.left, 11);
    ok_long(rect.top, 17);
    ok_long(rect.right, 23);
    ok_long(rect.bottom, 42);

    hrgn2 = CreateRectRgn(1, 2, 3, 4);
    SelectClipRgn(hdc, hrgn2);
    DeleteObject(hrgn2);
    ret = GetRandomRgn(hdc, hrgn1, CLIPRGN);
    ok_int(ret, 1);
    GetRgnBox(hrgn1, &rect);
    ok_long(rect.left, 1);
    ok_long(rect.top, 2);
    ok_long(rect.right, 3);
    ok_long(rect.bottom, 4);

    hrgn2 = CreateRectRgn(2, 3, 4, 5);
    SelectClipRgn(ghdcWindow, hrgn2);
    DeleteObject(hrgn2);
    ret = GetRandomRgn(ghdcWindow, hrgn1, CLIPRGN);
    ok_int(ret, 1);
    GetRgnBox(hrgn1, &rect);
    ok_long(rect.left, 2);
    ok_long(rect.top, 3);
    ok_long(rect.right, 4);
    ok_long(rect.bottom, 5);

    MoveWindow(ghwnd, 200, 400, 100, 100, 0);

    ret = GetRandomRgn(ghdcWindow, hrgn1, CLIPRGN);
    ok_int(ret, 1);
    GetRgnBox(hrgn1, &rect);
    ok_long(rect.left, 2);
    ok_long(rect.top, 3);
    ok_long(rect.right, 4);
    ok_long(rect.bottom, 5);


    DeleteObject(hrgn1);
    DeleteDC(hdc);
}