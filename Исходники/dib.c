static void draw_graphics(HDC hdc, BITMAPINFO *bmi, BYTE *bits, const char ***sha1)
{
    DWORD dib_size = get_dib_size(bmi);
    HPEN solid_pen, dashed_pen, orig_pen;
    HBRUSH solid_brush, dib_brush, hatch_brush, orig_brush;
    INT i, y, hatch_style;
    HRGN hrgn, hrgn2;
    BYTE dib_brush_buf[sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD) + 16 * 16 * sizeof(DWORD)]; /* Enough for 16 x 16 at 32 bpp */
    BITMAPINFO *brush_bi = (BITMAPINFO*)dib_brush_buf;
    BYTE *brush_bits;
    BOOL dib_is_1bpp = (bmi->bmiHeader.biBitCount == 1);

    memset(bits, 0xcc, dib_size);
    compare_hash(bmi, bits, sha1, "empty");

    solid_pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0xff));
    orig_pen = SelectObject(hdc, solid_pen);
    SetBrushOrgEx(hdc, 0, 0, NULL);

    /* horizontal and vertical lines */
    for(i = 1; i <= 16; i++)
    {
        SetROP2(hdc, i);
        MoveToEx(hdc, 10, i * 3, NULL);
        LineTo(hdc, 100, i * 3); /* l -> r */
        MoveToEx(hdc, 100, 50 + i * 3, NULL);
        LineTo(hdc, 10, 50 + i * 3); /* r -> l */
        MoveToEx(hdc, 120 + i * 3, 10, NULL);
        LineTo(hdc, 120 + i * 3, 100); /* t -> b */
        MoveToEx(hdc, 170 + i * 3, 100, NULL);
        LineTo(hdc, 170 + i * 3, 10); /* b -> t */
    }
    compare_hash(bmi, bits, sha1, "h and v solid lines");
    memset(bits, 0xcc, dib_size);

    /* diagonal lines */
    SetROP2(hdc, R2_COPYPEN);
    for(i = 0; i < 16; i++)
    {
        double s = sin(M_PI * i / 8.0);
        double c = cos(M_PI * i / 8.0);

        MoveToEx(hdc, 200.5 + 10 * c, 200.5 + 10 * s, NULL);
        LineTo(hdc, 200.5 + 100 * c, 200.5 + 100 * s);
    }
    compare_hash(bmi, bits, sha1, "diagonal solid lines");
    memset(bits, 0xcc, dib_size);

    for(i = 0; i < sizeof(bias_check) / sizeof(bias_check[0]); i++)
    {
        MoveToEx(hdc, bias_check[i].left, bias_check[i].top, NULL);
        LineTo(hdc, bias_check[i].right, bias_check[i].bottom);
    }
    compare_hash(bmi, bits, sha1, "more diagonal solid lines");
    memset(bits, 0xcc, dib_size);

    /* solid brush PatBlt */
    solid_brush = CreateSolidBrush(RGB(0x33, 0xaa, 0xff));
    orig_brush = SelectObject(hdc, solid_brush);

    for(i = 0, y = 10; i < 256; i++)
    {
        BOOL ret;

        ret = PatBlt(hdc, 10, y, 100, 10, rop3[i]);

        if(rop_uses_src(rop3[i]))
            ok(ret == FALSE, "got TRUE for %x\n", rop3[i]);
        else
        {
            ok(ret, "got FALSE for %x\n", rop3[i]);
            y += 20;
        }

    }
    compare_hash(bmi, bits, sha1, "solid patblt");
    memset(bits, 0xcc, dib_size);

    /* clipped lines */
    hrgn = CreateRectRgn(10, 10, 200, 20);
    hrgn2 = CreateRectRgn(100, 100, 200, 200);
    CombineRgn(hrgn, hrgn, hrgn2, RGN_OR);
    SetRectRgn(hrgn2, 290, 100, 300, 200);
    CombineRgn(hrgn, hrgn, hrgn2, RGN_OR);
    ExtSelectClipRgn(hdc, hrgn, RGN_COPY);
    DeleteObject(hrgn2);

    for(i = 0; i < sizeof(hline_clips)/sizeof(hline_clips[0]); i++)
    {
        MoveToEx(hdc, hline_clips[i].left, hline_clips[i].top, NULL);
        LineTo(hdc, hline_clips[i].right, hline_clips[i].bottom);
    }
    compare_hash(bmi, bits, sha1, "clipped solid hlines");
    memset(bits, 0xcc, dib_size);

    for(i = 0; i < sizeof(vline_clips)/sizeof(vline_clips[0]); i++)
    {
        MoveToEx(hdc, vline_clips[i].left, vline_clips[i].top, NULL);
        LineTo(hdc, vline_clips[i].right, vline_clips[i].bottom);
    }
    compare_hash(bmi, bits, sha1, "clipped solid vlines");
    memset(bits, 0xcc, dib_size);

    for(i = 0; i < sizeof(line_clips)/sizeof(line_clips[0]); i++)
    {
        MoveToEx(hdc, line_clips[i].left, line_clips[i].top, NULL);
        LineTo(hdc, line_clips[i].right, line_clips[i].bottom);
    }
    compare_hash(bmi, bits, sha1, "clipped solid diagonal lines");
    memset(bits, 0xcc, dib_size);

    /* clipped PatBlt */
    for(i = 0; i < sizeof(patblt_clips) / sizeof(patblt_clips[0]); i++)
    {
        PatBlt(hdc, patblt_clips[i].left, patblt_clips[i].top,
               patblt_clips[i].right - patblt_clips[i].left,
               patblt_clips[i].bottom - patblt_clips[i].top, PATCOPY);
    }
    compare_hash(bmi, bits, sha1, "clipped patblt");
    memset(bits, 0xcc, dib_size);

    /* clipped dashed lines */
    dashed_pen = CreatePen(PS_DASH, 1, RGB(0xff, 0, 0));
    SelectObject(hdc, dashed_pen);
    SetBkMode(hdc, TRANSPARENT);
    SetBkColor(hdc, RGB(0, 0xff, 0));

    for(i = 0; i < sizeof(hline_clips)/sizeof(hline_clips[0]); i++)
    {
        MoveToEx(hdc, hline_clips[i].left, hline_clips[i].top, NULL);
        LineTo(hdc, hline_clips[i].right, hline_clips[i].bottom);
    }
    compare_hash(bmi, bits, sha1, "clipped dashed hlines");
    memset(bits, 0xcc, dib_size);

    for(i = 0; i < sizeof(hline_clips)/sizeof(hline_clips[0]); i++)
    {
        MoveToEx(hdc, hline_clips[i].right - 1, hline_clips[i].bottom, NULL);
        LineTo(hdc, hline_clips[i].left - 1, hline_clips[i].top);
    }
    compare_hash(bmi, bits, sha1, "clipped dashed hlines r -> l");
    memset(bits, 0xcc, dib_size);

    for(i = 0; i < sizeof(vline_clips)/sizeof(vline_clips[0]); i++)
    {
        MoveToEx(hdc, vline_clips[i].left, vline_clips[i].top, NULL);
        LineTo(hdc, vline_clips[i].right, vline_clips[i].bottom);
    }
    compare_hash(bmi, bits, sha1, "clipped dashed vlines");
    memset(bits, 0xcc, dib_size);

    for(i = 0; i < sizeof(vline_clips)/sizeof(vline_clips[0]); i++)
    {
        MoveToEx(hdc, vline_clips[i].right, vline_clips[i].bottom - 1, NULL);
        LineTo(hdc, vline_clips[i].left, vline_clips[i].top - 1);
    }
    compare_hash(bmi, bits, sha1, "clipped dashed vlines b -> t");
    memset(bits, 0xcc, dib_size);

    for(i = 0; i < sizeof(line_clips)/sizeof(line_clips[0]); i++)
    {
        MoveToEx(hdc, line_clips[i].left, line_clips[i].top, NULL);
        LineTo(hdc, line_clips[i].right, line_clips[i].bottom);
    }
    compare_hash(bmi, bits, sha1, "clipped dashed diagonal lines");
    memset(bits, 0xcc, dib_size);

    SetBkMode(hdc, OPAQUE);

    for(i = 0; i < sizeof(line_clips)/sizeof(line_clips[0]); i++)
    {
        MoveToEx(hdc, line_clips[i].left, line_clips[i].top, NULL);
        LineTo(hdc, line_clips[i].right, line_clips[i].bottom);
    }
    compare_hash(bmi, bits, sha1, "clipped opaque dashed diagonal lines");
    memset(bits, 0xcc, dib_size);

    ExtSelectClipRgn(hdc, NULL, RGN_COPY);

    /* 8888 DIB pattern brush */

    brush_bi->bmiHeader = dib_brush_header_8888;
    brush_bits = (BYTE*)brush_bi + sizeof(BITMAPINFOHEADER);
    memset(brush_bits, 0, 16 * 16 * sizeof(DWORD));
    brush_bits[2] = 0xff;
    brush_bits[6] = 0xff;
    brush_bits[14] = 0xff;
    brush_bits[65] = 0xff;
    brush_bits[69] = 0xff;
    brush_bits[72] = 0xff;

    dib_brush = CreateDIBPatternBrushPt(brush_bi, DIB_RGB_COLORS);

    SelectObject(hdc, dib_brush);
    SetBrushOrgEx(hdc, 1, 1, NULL);

    for(i = 0, y = 10; i < 256; i++)
    {
        BOOL ret;

        if(!rop_uses_src(rop3[i]))
        {
            ret = PatBlt(hdc, 10 + i, y, 100, 20, rop3[i]);
            ok(ret, "got FALSE for %x\n", rop3[i]);
            y += 25;
        }
    }
    compare_hash_broken_todo(bmi, bits, sha1, "top-down 8888 dib brush patblt", dib_is_1bpp ? 2 : 0, dib_is_1bpp);
    memset(bits, 0xcc, dib_size);

    SelectObject(hdc, orig_brush);
    DeleteObject(dib_brush);

    /* 8888 bottom-up DIB pattern brush */

    brush_bi->bmiHeader.biHeight = -brush_bi->bmiHeader.biHeight;

    dib_brush = CreateDIBPatternBrushPt(brush_bi, DIB_RGB_COLORS);

    SelectObject(hdc, dib_brush);

    /* This used to set the x origin to 100 as well, but
       there's a Windows bug for 24 bpp where the brush's x offset
       is incorrectly calculated for rops that involve both D and P */
    SetBrushOrgEx(hdc, 4, 100, NULL);

    for(i = 0, y = 10; i < 256; i++)
    {
        BOOL ret;

        if(!rop_uses_src(rop3[i]))
        {
            ret = PatBlt(hdc, 10 + i, y, 100, 20, rop3[i]);
            ok(ret, "got FALSE for %x\n", rop3[i]);
            y += 25;
        }
    }
    compare_hash_broken_todo(bmi, bits, sha1, "bottom-up 8888 dib brush patblt", dib_is_1bpp ? 2 : 0, dib_is_1bpp);
    memset(bits, 0xcc, dib_size);

    SelectObject(hdc, orig_brush);
    DeleteObject(dib_brush);

    /* 24 bpp dib pattern brush */

    brush_bi->bmiHeader = dib_brush_header_24;
    brush_bits = (BYTE*)brush_bi + sizeof(BITMAPINFOHEADER);
    memset(brush_bits, 0, 16 * 16 * 3);
    brush_bits[0] = brush_bits[3] = brush_bits[6] = brush_bits[8] = 0xff;
    brush_bits[49] = brush_bits[52] = 0xff;

    dib_brush = CreateDIBPatternBrushPt(brush_bi, DIB_RGB_COLORS);

    SelectObject(hdc, dib_brush);
    SetBrushOrgEx(hdc, 1, 1, NULL);

    for(i = 0, y = 10; i < 256; i++)
    {
        BOOL ret;

        if(!rop_uses_src(rop3[i]))
        {
            ret = PatBlt(hdc, 10 + i, y, 100, 20, rop3[i]);
            ok(ret, "got FALSE for %x\n", rop3[i]);
            y += 25;
        }
    }
    compare_hash_broken_todo(bmi, bits, sha1, "top-down 24 bpp brush patblt", dib_is_1bpp ? 2 : 0, dib_is_1bpp);
    memset(bits, 0xcc, dib_size);

    SelectObject(hdc, orig_brush);
    DeleteObject(dib_brush);

    /* 555 dib pattern brush */

    brush_bi->bmiHeader = dib_brush_header_555;
    brush_bits = (BYTE*)brush_bi + sizeof(BITMAPINFOHEADER);
    memset(brush_bits, 0, 16 * 16 * sizeof(WORD));
    brush_bits[0] = brush_bits[1] = 0xff;
    brush_bits[32] = brush_bits[34] = 0x7c;

    dib_brush = CreateDIBPatternBrushPt(brush_bi, DIB_RGB_COLORS);

    SelectObject(hdc, dib_brush);
    SetBrushOrgEx(hdc, 1, 1, NULL);

    for(i = 0, y = 10; i < 256; i++)
    {
        BOOL ret;

        if(!rop_uses_src(rop3[i]))
        {
            ret = PatBlt(hdc, 10 + i, y, 100, 20, rop3[i]);
            ok(ret, "got FALSE for %x\n", rop3[i]);
            y += 25;
        }
    }
    compare_hash_broken_todo(bmi, bits, sha1, "top-down 555 dib brush patblt", dib_is_1bpp ? 1 : 0, dib_is_1bpp);
    memset(bits, 0xcc, dib_size);

    SelectObject(hdc, orig_brush);
    DeleteObject(dib_brush);

    SetBrushOrgEx(hdc, 0, 0, NULL);

    /* 8 bpp dib pattern brush */

    brush_bi->bmiHeader = dib_brush_header_8;
    brush_bi->bmiHeader.biClrUsed = 3;
    memset(brush_bi->bmiColors, 0, brush_bi->bmiHeader.biClrUsed * sizeof(RGBQUAD));
    brush_bi->bmiColors[0].rgbRed = 0xff;
    brush_bi->bmiColors[1].rgbRed = 0xff;
    brush_bi->bmiColors[1].rgbGreen = 0xff;
    brush_bi->bmiColors[1].rgbBlue = 0xff;

    brush_bits = (BYTE*)brush_bi + sizeof(BITMAPINFOHEADER) + brush_bi->bmiHeader.biClrUsed * sizeof(RGBQUAD);
    memset(brush_bits, 0, 16 * 16 * sizeof(BYTE));
    brush_bits[0] = brush_bits[1] = 1;
    brush_bits[16] = brush_bits[17] = 2;
    brush_bits[32] = brush_bits[33] = 6;

    dib_brush = CreateDIBPatternBrushPt(brush_bi, DIB_RGB_COLORS);

    SelectObject(hdc, dib_brush);
    SetBrushOrgEx(hdc, 1, 1, NULL);

    for(i = 0, y = 10; i < 256; i++)
    {
        BOOL ret;

        if(!rop_uses_src(rop3[i]))
        {
            ret = PatBlt(hdc, 10 + i, y, 100, 20, rop3[i]);
            ok(ret, "got FALSE for %x\n", rop3[i]);
            y += 25;
        }
    }
    compare_hash_broken_todo(bmi, bits, sha1, "top-down 8 bpp dib brush patblt", dib_is_1bpp ? 2 : 0, dib_is_1bpp);
    memset(bits, 0xcc, dib_size);

    SelectObject(hdc, orig_brush);
    DeleteObject(dib_brush);

    /* 4 bpp dib pattern brush */

    brush_bi->bmiHeader = dib_brush_header_4;
    dib_brush = CreateDIBPatternBrushPt(brush_bi, DIB_RGB_COLORS);

    SelectObject(hdc, dib_brush);
    SetBrushOrgEx(hdc, 1, 1, NULL);

    for(i = 0, y = 10; i < 256; i++)
    {
        BOOL ret;

        if(!rop_uses_src(rop3[i]))
        {
            ret = PatBlt(hdc, 10 + i, y, 100, 20, rop3[i]);
            ok(ret, "got FALSE for %x\n", rop3[i]);
            y += 25;
        }
    }
    compare_hash_broken_todo(bmi, bits, sha1, "top-down 4 bpp dib brush patblt", dib_is_1bpp ? 2 : 0, dib_is_1bpp);
    memset(bits, 0xcc, dib_size);

    SelectObject(hdc, orig_brush);
    DeleteObject(dib_brush);

    /* 1 bpp dib pattern brush */

    brush_bi->bmiHeader = dib_brush_header_1;
    brush_bi->bmiHeader.biClrUsed = 2;
    memset(brush_bits, 0, 16 * 4);
    brush_bits[0] = 0xf0;
    brush_bits[4] = 0xf0;
    brush_bits[8] = 0xf0;

    dib_brush = CreateDIBPatternBrushPt(brush_bi, DIB_RGB_COLORS);
    SelectObject(hdc, dib_brush);
    for(i = 0, y = 10; i < 256; i++)
    {
        BOOL ret;

        if(!rop_uses_src(rop3[i]))
        {
            ret = PatBlt(hdc, 10 + i, y, 100, 20, rop3[i]);
            ok(ret, "got FALSE for %x\n", rop3[i]);
            y += 25;
        }
    }

    compare_hash_broken_todo(bmi, bits, sha1, "top-down 1 bpp dib brush patblt", dib_is_1bpp ? 2 : 0, dib_is_1bpp);
    memset(bits, 0xcc, dib_size);

    SelectObject(hdc, orig_brush);
    SetBrushOrgEx(hdc, 0, 0, NULL);

    /* Rectangle */

    SelectObject(hdc, solid_pen);
    SelectObject(hdc, solid_brush);

    for(i = 0; i < sizeof(rectangles)/sizeof(rectangles[0]); i++)
    {
        Rectangle(hdc, rectangles[i].left, rectangles[i].top, rectangles[i].right, rectangles[i].bottom);
    }

    SelectObject(hdc, dashed_pen);
    for(i = 0; i < sizeof(rectangles)/sizeof(rectangles[0]); i++)
    {
        Rectangle(hdc, rectangles[i].left, rectangles[i].top + 150, rectangles[i].right, rectangles[i].bottom + 150);
    }

    compare_hash(bmi, bits, sha1, "rectangles");
    memset(bits, 0xcc, dib_size);
    SelectObject(hdc, solid_pen);

    /* PaintRgn */

    PaintRgn(hdc, hrgn);
    compare_hash(bmi, bits, sha1, "PaintRgn");
    memset(bits, 0xcc, dib_size);

    /* RTL rectangles */

    if( !pSetLayout )
    {
        win_skip("Don't have SetLayout\n");
        (*sha1)++;
    }
    else
    {
        pSetLayout(hdc, LAYOUT_RTL);
        PaintRgn(hdc, hrgn);
        PatBlt(hdc, 10, 250, 10, 10, PATCOPY);
        Rectangle(hdc, 100, 250, 110, 260);
        compare_hash(bmi, bits, sha1, "rtl");
        memset(bits, 0xcc, dib_size);

        pSetLayout(hdc, LAYOUT_LTR);
    }

    for(i = 0, y = 10; i < 256; i++)
    {
        BOOL ret;

        if(!rop_uses_src(rop3[i]))
        {
            for(hatch_style = HS_HORIZONTAL; hatch_style <= HS_DIAGCROSS; hatch_style++)
            {
                hatch_brush = CreateHatchBrush(hatch_style, RGB(0xff, 0, 0));
                SelectObject(hdc, hatch_brush);
                ret = PatBlt(hdc, 10 + i + 30 * hatch_style, y, 20, 20, rop3[i]);
                ok(ret, "got FALSE for %x\n", rop3[i]);
                SelectObject(hdc, orig_brush);
                DeleteObject(hatch_brush);
            }
            y += 25;
        }
    }

    compare_hash_broken_todo(bmi, bits, sha1, "hatch brushes", 1, FALSE); /* nt4 is different */
    memset(bits, 0xcc, dib_size);

    SelectObject(hdc, orig_brush);
    SelectObject(hdc, orig_pen);
    DeleteObject(hrgn);
    DeleteObject(dib_brush);
    DeleteObject(dashed_pen);
    DeleteObject(solid_brush);
    DeleteObject(solid_pen);
}