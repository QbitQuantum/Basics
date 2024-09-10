void
Test_SrcMono1(ULONG iBmpFormat, HBITMAP hbmpDst, PVOID pvBits)
{
    COLORREF c, expected;
    HBRUSH hbr;
    RECT rect;
    struct
    {
        BITMAPINFOHEADER bmiHeader;
        ULONG bmiColors[2];
        BYTE aj[32];
    } bmi;

    SelectObject(hdcSrc, hbmp1bpp_a);
    SelectObject(hdcDst, hbmpDst);

    /* Set default dc fore and back colors */
    SetTextColor(hdcSrc, 0x000000);
    SetBkColor(hdcSrc, 0xffffff);
    SetTextColor(hdcDst, 0x000000);
    SetBkColor(hdcDst, 0xffffff);

    /* Do a bitblt operation */
    ok(BitBlt(hdcDst, 0, 0, 2, 2, hdcSrc, 0, 0, SRCCOPY), "(%ld): BitBlt failed", iBmpFormat);

    /* Test background color */
    c = GetPixel(hdcDst, 0, 0);
    expected = 0xffffff;
    ok(c == expected, "(%ld): wrong color, expected %lx, got %lx\n", iBmpFormat, expected, c);

    /* Test foreground color */
    c = GetPixel(hdcDst, 1, 0);
    expected = 0x000000;
    ok(c == expected, "(%ld): wrong color, expected %lx, got %lx\n", iBmpFormat, expected, c);

    if (pvBits)
    {
        c = GetDIBPixel(iBmpFormat, pvBits, 0);
        expected = iXlateFromRGB(iBmpFormat,  GetBkColor(hdcSrc));
        ok(c == expected, "(%ld): wrong color, expected %lx, got %lx\n", iBmpFormat, expected, c);

        c = GetDIBPixel(iBmpFormat, pvBits, 1);
        expected = iXlateFromRGB(iBmpFormat, GetTextColor(hdcSrc));
        ok(c == expected, "(%ld): wrong color, expected %lx, got %lx\n", iBmpFormat, expected, c);
    }

    /* Set different dc fore and back colors */
    SetTextColor(hdcSrc, 0xf00f0f);
    SetBkColor(hdcSrc, 0xf0ff0f);
    SetTextColor(hdcDst, 0xefFee5);
    SetBkColor(hdcDst, 0x100121);

    /* Make sure this alone didn't affect the resulting colors */
    c = GetPixel(hdcDst, 0, 0);
    expected = 0xffffff;
    ok(c == expected, "(%ld): wrong color, expected %lx, got %lx\n", iBmpFormat, expected, c);
    c = GetPixel(hdcDst, 1, 0);
    expected = 0x000000;
    ok(c == expected, "(%ld): wrong color, expected %lx, got %lx\n", iBmpFormat, expected, c);

    /* Repeat the bitblt operation */
    ok(BitBlt(hdcDst, 0, 0, 2, 2, hdcSrc, 0, 0, SRCCOPY), "(%ld): BitBlt failed", iBmpFormat);

    /* Test background color */
    c = GetPixel(hdcDst, 0, 0);
    expected = GetClosestColor(iBmpFormat, GetBkColor(hdcDst), 0xffffff);
    ok(c == expected, "(%ld): wrong color, expected %lx, got %lx\n", iBmpFormat, expected, c);

    /* Test foreground color */
    c = GetPixel(hdcDst, 1, 0);
    expected = GetClosestColor(iBmpFormat, GetTextColor(hdcDst), 0);
    ok(c == expected, "(%ld): wrong color, expected %lx, got %lx\n", iBmpFormat, expected, c);

    if (pvBits)
    {
        c = GetDIBPixel(iBmpFormat, pvBits, 0);
        expected = iXlateFromRGB(iBmpFormat, GetBkColor(hdcDst));
        ok(c == expected, "(%ld): wrong color, expected %lx, got %lx\n", iBmpFormat, expected, c);

        c = GetDIBPixel(iBmpFormat, pvBits, 1);
        expected = iXlateFromRGB(iBmpFormat, GetTextColor(hdcDst));
        ok(c == expected, "(%ld): wrong color, expected %lx, got %lx\n", iBmpFormat, expected, c);
    }

    /* Set inverted fore and back colors */
    SetTextColor(hdcSrc, 0);
    SetBkColor(hdcSrc, 0xffffff);
    SetTextColor(hdcDst, 0xffffff);
    SetBkColor(hdcDst, 0x000000);

    /* Repeat the bitblt operation */
    ok(BitBlt(hdcDst, 0, 0, 2, 2, hdcSrc, 0, 0, SRCCOPY), "(%ld): BitBlt failed", iBmpFormat);

    /* Test background color */
    c = GetPixel(hdcDst, 0, 0);
    expected = GetClosestColor(iBmpFormat, GetBkColor(hdcDst), 0xffffff);
    ok(c == expected, "(%ld): wrong color, expected %lx, got %lx\n", iBmpFormat, expected, c);

    /* Test foreground color */
    c = GetPixel(hdcDst, 1, 0);
    expected = GetClosestColor(iBmpFormat, GetTextColor(hdcDst), 0);
    ok(c == expected, "(%ld): wrong color, expected %lx, got %lx\n", iBmpFormat, expected, c);

    if (pvBits)
    {
        c = GetDIBPixel(iBmpFormat, pvBits, 0);
        expected = iXlateFromRGB(iBmpFormat, GetBkColor(hdcDst));
        ok(c == expected, "(%ld): wrong color, expected %lx, got %lx\n", iBmpFormat, expected, c);

        c = GetDIBPixel(iBmpFormat, pvBits, 1);
        expected = iXlateFromRGB(iBmpFormat, GetTextColor(hdcDst));
        ok(c == expected, "(%ld): wrong color, expected %lx, got %lx\n", iBmpFormat, expected, c);
    }


/* Hatch brush ****************************************************************/

    /* Set dc fore and back colors */
    SetTextColor(hdcDst, 0x102030);
    SetBkColor(hdcDst, 0xeeccdd);
    SetBkMode(hdcDst, OPAQUE);

    /* Create a hatch brush */
    hbr = CreateHatchBrush(HS_DIAGCROSS, 0x123456);

    /* Fill the destination bitmap */
    rect.left = rect.top = 0;
    rect.bottom = rect.right = 4;
    ok(FillRect(hdcDst, &rect, hbr), "FillRect failed\n");

    /* Test the fore color of the hatch brush */
    c = GetPixel(hdcDst, 0, 0);
    expected = GetClosestColor(iBmpFormat, 0x123456, 0);
    ok(c == expected, "(%ld): wrong color, expected %lx, got %lx\n", iBmpFormat, expected, c);

    /* Test the back color of the hatch brush */
    c = GetPixel(hdcDst, 1, 0);
    expected = GetClosestColor(iBmpFormat, GetBkColor(hdcDst), 0xffffff);
    ok(c == expected, "(%ld): wrong color, expected %lx, got %lx\n", iBmpFormat, expected, c);

    if (pvBits)
    {
        c = GetDIBPixel(iBmpFormat, pvBits, 0);
        expected = iXlateFromRGB(iBmpFormat, 0x123456);
        ok(c == expected, "(%ld): wrong color, expected %lx, got %lx\n", iBmpFormat, expected, c);

        c = GetDIBPixel(iBmpFormat, pvBits, 1);
        expected = iXlateFromRGB(iBmpFormat, GetBkColor(hdcDst));
        ok(c == expected, "(%ld): wrong color, expected %lx, got %lx\n", iBmpFormat, expected, c);
    }

    DeleteObject(hbr);

/* DIB brush ******************************************************************/

    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = 8;
    bmi.bmiHeader.biHeight = 8;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 1;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biSizeImage = 0;
    bmi.bmiHeader.biXPelsPerMeter = 1;
    bmi.bmiHeader.biYPelsPerMeter = 1;
    bmi.bmiHeader.biClrUsed = 2;
    bmi.bmiHeader.biClrImportant = 2;
    bmi.bmiColors[0] = 0xeeeeee;
    bmi.bmiColors[1] = 0x111111;
    memset(bmi.aj, 0xaaaa, sizeof(bmi.aj));
    hbr = CreateDIBPatternBrushPt(&bmi, DIB_RGB_COLORS);
    ok(hbr != 0, "CreateDIBPatternBrushPt failed\n");

    rect.left = rect.top = 0;
    rect.bottom = rect.right = 4;
    ok(FillRect(hdcDst, &rect, hbr),"FillRect failed\n");

    /* Test color 1 of the dib brush */
    c = GetPixel(hdcDst, 0, 0);
    expected = GetClosestColor(iBmpFormat, bmi.bmiColors[1], 0);
    ok(c == expected, "(%ld): wrong color, expected %lx, got %lx\n", iBmpFormat, expected, c);

    /* Test color 0 of the dib brush */
    c = GetPixel(hdcDst, 1, 0);
    expected = GetClosestColor(iBmpFormat, bmi.bmiColors[0], 0xffffff);
    ok(c == expected, "(%ld): wrong color, expected %lx, got %lx\n", iBmpFormat, expected, c);

    if (pvBits)
    {
        c = GetDIBPixel(iBmpFormat, pvBits, 0);
        expected = iXlateFromRGB(iBmpFormat, bmi.bmiColors[1]);
        ok(c == expected, "(%ld): wrong color, expected %lx, got %lx\n", iBmpFormat, expected, c);

        c = GetDIBPixel(iBmpFormat, pvBits, 1);
        expected = iXlateFromRGB(iBmpFormat, bmi.bmiColors[0]);
        ok(c == expected, "(%ld): wrong color, expected %lx, got %lx\n", iBmpFormat, expected, c);
    }

    DeleteObject(hbr);


}