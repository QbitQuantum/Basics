void DrawStartPage(WindowInfo& win, HDC hdc, FileHistory& fileHistory, COLORREF textColor, COLORREF backgroundColor)
{
    HPEN penBorder = CreatePen(PS_SOLID, DOCLIST_SEPARATOR_DY, WIN_COL_BLACK);
    HPEN penThumbBorder = CreatePen(PS_SOLID, DOCLIST_THUMBNAIL_BORDER_W, WIN_COL_BLACK);
    HPEN penLinkLine = CreatePen(PS_SOLID, 1, COL_BLUE_LINK);

    ScopedFont fontSumatraTxt(GetSimpleFont(hdc, L"MS Shell Dlg", 24));
    ScopedFont fontLeftTxt(GetSimpleFont(hdc, L"MS Shell Dlg", 14));

    HGDIOBJ origFont = SelectObject(hdc, fontSumatraTxt); /* Just to remember the orig font */

    ClientRect rc(win.hwndCanvas);
    RECT rTmp = rc.ToRECT();
    ScopedGdiObj<HBRUSH> brushLogoBg(CreateSolidBrush(GetLogoBgColor()));
    FillRect(hdc, &rTmp, brushLogoBg);

    SelectObject(hdc, brushLogoBg);
    SelectObject(hdc, penBorder);

    bool isRtl = IsUIRightToLeft();

    /* render title */
    RectI titleBox = RectI(PointI(0, 0), CalcSumatraVersionSize(hdc));
    titleBox.x = rc.dx - titleBox.dx - 3;
    DrawSumatraVersion(hdc, titleBox);
    PaintLine(hdc, RectI(0, titleBox.dy, rc.dx, 0));

    /* render recent files list */
    SelectObject(hdc, penThumbBorder);
    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, WIN_COL_BLACK);

    rc.y += titleBox.dy;
    rc.dy -= titleBox.dy;
    rTmp = rc.ToRECT();
    ScopedGdiObj<HBRUSH> brushAboutBg(CreateSolidBrush(GetAboutBgColor()));
    FillRect(hdc, &rTmp, brushAboutBg);
    rc.dy -= DOCLIST_BOTTOM_BOX_DY;

    Vec<DisplayState *> list;
    fileHistory.GetFrequencyOrder(list);

    int width = limitValue((rc.dx - DOCLIST_MARGIN_LEFT - DOCLIST_MARGIN_RIGHT + DOCLIST_MARGIN_BETWEEN_X) / (THUMBNAIL_DX + DOCLIST_MARGIN_BETWEEN_X), 1, DOCLIST_MAX_THUMBNAILS_X);
    int height = min((rc.dy - DOCLIST_MARGIN_TOP - DOCLIST_MARGIN_BOTTOM + DOCLIST_MARGIN_BETWEEN_Y) / (THUMBNAIL_DY + DOCLIST_MARGIN_BETWEEN_Y), FILE_HISTORY_MAX_FREQUENT / width);
    PointI offset(rc.x + DOCLIST_MARGIN_LEFT + (rc.dx - width * THUMBNAIL_DX - (width - 1) * DOCLIST_MARGIN_BETWEEN_X - DOCLIST_MARGIN_LEFT - DOCLIST_MARGIN_RIGHT) / 2, rc.y + DOCLIST_MARGIN_TOP);
    if (offset.x < ABOUT_INNER_PADDING)
        offset.x = ABOUT_INNER_PADDING;
    else if (list.Count() == 0)
        offset.x = DOCLIST_MARGIN_LEFT;

    SelectObject(hdc, fontSumatraTxt);
    SIZE txtSize;
    const WCHAR *txt = _TR("Frequently Read");
    GetTextExtentPoint32(hdc, txt, (int)str::Len(txt), &txtSize);
    RectI headerRect(offset.x, rc.y + (DOCLIST_MARGIN_TOP - txtSize.cy) / 2, txtSize.cx, txtSize.cy);
    if (isRtl)
        headerRect.x = rc.dx - offset.x - headerRect.dx;
    rTmp = headerRect.ToRECT();
    DrawText(hdc, txt, -1, &rTmp, (isRtl ? DT_RTLREADING : DT_LEFT) | DT_NOPREFIX);

    SelectObject(hdc, fontLeftTxt);
    SelectObject(hdc, GetStockBrush(NULL_BRUSH));

    win.staticLinks.Reset();
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            if (h * width + w >= (int)list.Count()) {
                // display the "Open a document" link right below the last row
                height = w > 0 ? h + 1 : h;
                break;
            }
            DisplayState *state = list.At(h * width + w);

            RectI page(offset.x + w * (int)(THUMBNAIL_DX + DOCLIST_MARGIN_BETWEEN_X * win.uiDPIFactor),
                       offset.y + h * (int)(THUMBNAIL_DY + DOCLIST_MARGIN_BETWEEN_Y * win.uiDPIFactor),
                       THUMBNAIL_DX, THUMBNAIL_DY);
            if (isRtl)
                page.x = rc.dx - page.x - page.dx;
            bool loadOk = true;
            if (!state->thumbnail)
                loadOk = LoadThumbnail(*state);
            if (loadOk && state->thumbnail) {
                SizeI thumbSize = state->thumbnail->Size();
                if (thumbSize.dx != THUMBNAIL_DX || thumbSize.dy != THUMBNAIL_DY) {
                    page.dy = thumbSize.dy * THUMBNAIL_DX / thumbSize.dx;
                    page.y += THUMBNAIL_DY - page.dy;
                }
                HRGN clip = CreateRoundRectRgn(page.x, page.y, page.x + page.dx, page.y + page.dy, 10, 10);
                SelectClipRgn(hdc, clip);
                RenderedBitmap *clone = state->thumbnail->Clone();
                UpdateBitmapColors(clone->GetBitmap(), textColor, backgroundColor);
                clone->StretchDIBits(hdc, page);
                SelectClipRgn(hdc, NULL);
                DeleteObject(clip);
                delete clone;
            }
            RoundRect(hdc, page.x, page.y, page.x + page.dx, page.y + page.dy, 10, 10);

            int iconSpace = (int)(20 * win.uiDPIFactor);
            RectI rect(page.x + iconSpace, page.y + page.dy + 3, page.dx - iconSpace, iconSpace);
            if (isRtl)
                rect.x -= iconSpace;
            rTmp = rect.ToRECT();
            DrawText(hdc, path::GetBaseName(state->filePath), -1, &rTmp, DT_SINGLELINE | DT_END_ELLIPSIS | DT_NOPREFIX | (isRtl ? DT_RIGHT : DT_LEFT));

            SHFILEINFO sfi;
            HIMAGELIST himl = (HIMAGELIST)SHGetFileInfo(state->filePath, 0, &sfi, sizeof(sfi), SHGFI_SYSICONINDEX | SHGFI_SMALLICON | SHGFI_USEFILEATTRIBUTES);
            ImageList_Draw(himl, sfi.iIcon, hdc,
                           isRtl ? page.x + page.dx - (int)(16 * win.uiDPIFactor) : page.x,
                           rect.y, ILD_TRANSPARENT);

            win.staticLinks.Append(StaticLinkInfo(rect.Union(page), state->filePath, state->filePath));
        }
    }

    /* render bottom links */
    rc.y += DOCLIST_MARGIN_TOP + height * THUMBNAIL_DY + (height - 1) * DOCLIST_MARGIN_BETWEEN_Y + DOCLIST_MARGIN_BOTTOM;
    rc.dy = DOCLIST_BOTTOM_BOX_DY;

    SetTextColor(hdc, COL_BLUE_LINK);
    SelectObject(hdc, penLinkLine);

    HIMAGELIST himl = (HIMAGELIST)SendMessage(win.hwndToolbar, TB_GETIMAGELIST, 0, 0);
    RectI rectIcon(offset.x, rc.y, 0, 0);
    ImageList_GetIconSize(himl, &rectIcon.dx, &rectIcon.dy);
    rectIcon.y += (rc.dy - rectIcon.dy) / 2;
    if (isRtl)
        rectIcon.x = rc.dx - offset.x - rectIcon.dx;
    ImageList_Draw(himl, 0 /* index of Open icon */, hdc, rectIcon.x, rectIcon.y, ILD_NORMAL);

    txt = _TR("Open a document...");
    GetTextExtentPoint32(hdc, txt, (int)str::Len(txt), &txtSize);
    RectI rect(offset.x + rectIcon.dx + 3, rc.y + (rc.dy - txtSize.cy) / 2, txtSize.cx, txtSize.cy);
    if (isRtl)
        rect.x = rectIcon.x - rect.dx - 3;
    rTmp = rect.ToRECT();
    DrawText(hdc, txt, -1, &rTmp, isRtl ? DT_RTLREADING : DT_LEFT);
    PaintLine(hdc, RectI(rect.x, rect.y + rect.dy, rect.dx, 0));
    // make the click target larger
    rect = rect.Union(rectIcon);
    rect.Inflate(10, 10);
    win.staticLinks.Append(StaticLinkInfo(rect, SLINK_OPEN_FILE));

    rect = DrawBottomRightLink(win.hwndCanvas, hdc, _TR("Hide frequently read"));
    win.staticLinks.Append(StaticLinkInfo(rect, SLINK_LIST_HIDE));

    SelectObject(hdc, origFont);

    DeleteObject(penBorder);
    DeleteObject(penThumbBorder);
    DeleteObject(penLinkLine);
}