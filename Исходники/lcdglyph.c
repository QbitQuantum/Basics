JNIEXPORT jlong JNICALL
Java_sun_font_FileFontStrike__1getGlyphImageFromWindows
(JNIEnv *env, jobject unused,
 jstring fontFamily, jint style, jint size, jint glyphCode, jboolean fm) {

    GLYPHMETRICS glyphMetrics;
    LOGFONTW lf;
    BITMAPINFO bmi;
    TEXTMETRIC textMetric;
    RECT rect;
    int bytesWidth, dibBytesWidth, extra, imageSize, dibImageSize;
    unsigned char* dibImage = NULL, *rowPtr, *pixelPtr, *dibPixPtr, *dibRowPtr;
    unsigned char r,g,b;
    unsigned char* igTable;
    GlyphInfo* glyphInfo = NULL;
    int nameLen;
    LPWSTR name;
    HFONT oldFont, hFont;
    MAT2 mat2;

    unsigned short width;
    unsigned short height;
    short advanceX;
    short advanceY;
    int topLeftX;
    int topLeftY;
    int err;
    int bmWidth, bmHeight;
    int x, y;
    HBITMAP hBitmap = NULL, hOrigBM;
    int gamma, orient;

    HWND hWnd = NULL;
    HDC hDesktopDC = NULL;
    HDC hMemoryDC = NULL;

    hWnd = GetDesktopWindow();
    hDesktopDC = GetWindowDC(hWnd);
    if (hDesktopDC == NULL) {
        return (jlong)0;
    }
    if (GetDeviceCaps(hDesktopDC, BITSPIXEL) < 15) {
        FREE_AND_RETURN;
    }

    hMemoryDC = CreateCompatibleDC(hDesktopDC);
    if (hMemoryDC == NULL || fontFamily == NULL) {
        FREE_AND_RETURN;
    }
    err = SetMapMode(hMemoryDC, MM_TEXT);
    if (err == 0) {
        FREE_AND_RETURN;
    }

    memset(&lf, 0, sizeof(LOGFONTW));
    lf.lfHeight = -size;
    lf.lfWeight = (style & 1) ? FW_BOLD : FW_NORMAL;
    lf.lfItalic = (style & 2) ? 0xff : 0;
    lf.lfCharSet = DEFAULT_CHARSET;
    lf.lfQuality = CLEARTYPE_QUALITY;
    lf.lfOutPrecision = OUT_TT_PRECIS;
    lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
    lf.lfPitchAndFamily = DEFAULT_PITCH;

    nameLen = (*env)->GetStringLength(env, fontFamily);
    name = (LPWSTR)alloca((nameLen+1)*2);
    if (name == NULL) {
       FREE_AND_RETURN;
    }
    (*env)->GetStringRegion(env, fontFamily, 0, nameLen, name);
    name[nameLen] = '\0';

    if (nameLen < (sizeof(lf.lfFaceName) / sizeof(lf.lfFaceName[0]))) {
        wcscpy(lf.lfFaceName, name);
    } else {
        FREE_AND_RETURN;
    }

    hFont = CreateFontIndirectW(&lf);
    if (hFont == NULL) {
        FREE_AND_RETURN;
    }
    oldFont = SelectObject(hMemoryDC, hFont);

    memset(&textMetric, 0, sizeof(TEXTMETRIC));
    err = GetTextMetrics(hMemoryDC, &textMetric);
    if (err == 0) {
        FREE_AND_RETURN;
    }
    memset(&glyphMetrics, 0, sizeof(GLYPHMETRICS));
    memset(&mat2, 0, sizeof(MAT2));
    mat2.eM11.value = 1; mat2.eM22.value = 1;
    err = GetGlyphOutline(hMemoryDC, glyphCode,
                          GGO_METRICS|GGO_GLYPH_INDEX,
                          &glyphMetrics,
                          0, NULL, &mat2);
    if (err == GDI_ERROR) {
        /* Probably no such glyph - ie the font wasn't the one we expected. */
        FREE_AND_RETURN;
    }

    width  = (unsigned short)glyphMetrics.gmBlackBoxX;
    height = (unsigned short)glyphMetrics.gmBlackBoxY;

    /* Don't handle "invisible" glyphs in this code */
    if (width <= 0 || height == 0) {
       FREE_AND_RETURN;
    }

    advanceX = glyphMetrics.gmCellIncX;
    advanceY = glyphMetrics.gmCellIncY;
    topLeftX = glyphMetrics.gmptGlyphOrigin.x;
    topLeftY = glyphMetrics.gmptGlyphOrigin.y;

    /* GetGlyphOutline pre-dates cleartype and I'm not sure that it will
     * account for all pixels touched by the rendering. Need to widen,
     * and also adjust by one the x position at which it is rendered.
     * The extra pixels of width are used as follows :
     * One extra pixel at the left and the right will be needed to absorb
     * the pixels that will be touched by filtering by GDI to compensate
     * for colour fringing.
     * However there seem to be some cases where GDI renders two extra
     * pixels to the right, so we add one additional pixel to the right,
     * and in the code that copies this to the image cache we test for
     * the (rare) cases when this is touched, and if its not reduce the
     * stated image width for the blitting loops.
     * For fractional metrics :
     * One extra pixel at each end to account for sub-pixel positioning used
     * when fractional metrics is on in LCD mode.
     * The pixel at the left is needed so the blitting loop can index into
     * that a byte at a time to more accurately position the glyph.
     * The pixel at the right is needed so that when such indexing happens,
     * the blitting still can use the same width.
     * Consequently the width that is specified for the glyph is one less
     * than that of the actual image.
     * Note that in the FM case as a consequence we need to adjust the
     * position at which GDI renders, and the declared width of the glyph
     * See the if (fm) {} cases in the code.
     * For the non-FM case, we not only save 3 bytes per row, but this
     * prevents apparent glyph overlapping which affects the rendering
     * performance of accelerated pipelines since it adds additional
     * read-back requirements.
     */
    width+=3;
    if (fm) {
        width+=1;
    }
    /* DIB scanline must end on a DWORD boundary. We specify 3 bytes per pixel,
     * so must round up as needed to a multiple of 4 bytes.
     */
    dibBytesWidth = bytesWidth = width*3;
    extra = dibBytesWidth % 4;
    if (extra != 0) {
        dibBytesWidth += (4-extra);
    }
    /* The glyph cache image must be a multiple of 3 bytes wide. */
    extra = bytesWidth % 3;
    if (extra != 0) {
        bytesWidth += (3-extra);
    }
    bmWidth = width;
    bmHeight = height;

    /* Must use desktop DC to create a bitmap of that depth */
    hBitmap = CreateCompatibleBitmap(hDesktopDC, bmWidth, bmHeight);
    if (hBitmap == NULL) {
        FREE_AND_RETURN;
    }
    hOrigBM = (HBITMAP)SelectObject(hMemoryDC, hBitmap);

    /* Fill in black */
    rect.left = 0;
    rect.top = 0;
    rect.right = bmWidth;
    rect.bottom = bmHeight;
    FillRect(hMemoryDC, (LPRECT)&rect, GetStockObject(BLACK_BRUSH));

    /* Set text color to white, background to black. */
    SetBkColor(hMemoryDC, RGB(0,0,0));
    SetTextColor(hMemoryDC, RGB(255,255,255));

    /* adjust rendering position */
    x = -topLeftX+1;
    if (fm) {
        x += 1;
    }
    y = topLeftY - textMetric.tmAscent;
    err = ExtTextOutW(hMemoryDC, x, y, ETO_GLYPH_INDEX|ETO_OPAQUE,
                (LPRECT)&rect, (LPCWSTR)&glyphCode, 1, NULL);
    if (err == 0) {
        FREE_AND_RETURN;
    }

    /* Now get the image into a DIB.
     * MS docs for GetDIBits says the compatible bitmap must not be
     * selected into a DC, so restore the original first.
     */
    SelectObject(hMemoryDC, hOrigBM);
    SelectObject(hMemoryDC, oldFont);
    DeleteObject(hFont);

    memset(&bmi, 0, sizeof(BITMAPINFO));
    bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 24;
    bmi.bmiHeader.biCompression = BI_RGB;

    dibImage = SAFE_SIZE_ARRAY_ALLOC(malloc, dibBytesWidth, height);
    if (dibImage == NULL) {
        FREE_AND_RETURN;
    }
    dibImageSize = dibBytesWidth*height;
    memset(dibImage, 0, dibImageSize);

    err = GetDIBits(hMemoryDC, hBitmap, 0, height, dibImage,
                    &bmi, DIB_RGB_COLORS);

    if (err == 0) {        /* GetDIBits failed. */
        FREE_AND_RETURN;
    }

    err = SystemParametersInfo(SPI_GETFONTSMOOTHINGORIENTATION, 0, &orient, 0);
    if (err == 0) {
        FREE_AND_RETURN;
    }
    err = SystemParametersInfo(SPI_GETFONTSMOOTHINGCONTRAST, 0, &gamma, 0);
    if (err == 0) {
        FREE_AND_RETURN;
    }
    igTable = getIGTable(gamma/10);
    if (igTable == NULL) {
        FREE_AND_RETURN;
    }

    /* Now copy glyph image into a GlyphInfo structure and return it.
     * NB the xadvance calculated here may be overwritten by the caller.
     * 1 is subtracted from the bitmap width to get the glyph width, since
     * that extra "1" was added as padding, so the sub-pixel positioning of
     * fractional metrics could index into it.
     */
    glyphInfo = (GlyphInfo*)SAFE_SIZE_STRUCT_ALLOC(malloc, sizeof(GlyphInfo),
            bytesWidth, height);
    if (glyphInfo == NULL) {
        FREE_AND_RETURN;
    }
    imageSize = bytesWidth*height;
    glyphInfo->cellInfo = NULL;
    glyphInfo->rowBytes = bytesWidth;
    glyphInfo->width = width;
    if (fm) {
        glyphInfo->width -= 1; // must subtract 1
    }
    glyphInfo->height = height;
    glyphInfo->advanceX = advanceX;
    glyphInfo->advanceY = advanceY;
    glyphInfo->topLeftX = (float)(topLeftX-1);
    if (fm) {
        glyphInfo->topLeftX -= 1;
    }
    glyphInfo->topLeftY = (float)-topLeftY;
    glyphInfo->image = (unsigned char*)glyphInfo+sizeof(GlyphInfo);
    memset(glyphInfo->image, 0, imageSize);

    /* DIB 24bpp data is always stored in BGR order, but we usually
     * need this in RGB, so we can't just memcpy and need to swap B and R.
     * Also need to apply inverse gamma adjustment here.
     * We re-use the variable "extra" to see if the last pixel is touched
     * at all. If its not we can reduce the glyph image width. This comes
     * into play in some cases where GDI touches more pixels than accounted
     * for by increasing width by two pixels over the B&W image. Whilst
     * the bytes are in the cache, it doesn't affect rendering performance
     * of the hardware pipelines.
     */
    extra = 0;
    if (fm) {
        extra = 1; // always need it.
    }
    dibRowPtr = dibImage;
    rowPtr = glyphInfo->image;
    for (y=0;y<height;y++) {
        pixelPtr = rowPtr;
        dibPixPtr = dibRowPtr;
        for (x=0;x<width;x++) {
            if (orient == FE_FONTSMOOTHINGORIENTATIONRGB) {
                b = *dibPixPtr++;
                g = *dibPixPtr++;
                r = *dibPixPtr++;
            } else {
                r = *dibPixPtr++;
                g = *dibPixPtr++;
                b = *dibPixPtr++;
            }
            *pixelPtr++ = igTable[r];
            *pixelPtr++ = igTable[g];
            *pixelPtr++ = igTable[b];
            if (!fm && (x==(width-1)) && (r|g|b)) {
                extra = 1;
            }
        }
        dibRowPtr += dibBytesWidth;
        rowPtr  += bytesWidth;
    }
    if (!extra) {
        glyphInfo->width -= 1;
    }

    free(dibImage);
    ReleaseDC(hWnd, hDesktopDC);
    DeleteObject(hMemoryDC);
    DeleteObject(hBitmap);

    return ptr_to_jlong(glyphInfo);
}