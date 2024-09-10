void GrDistanceFieldTextContext::onDrawText(GrRenderTarget* rt, const GrClip& clip,
                                            const GrPaint& paint,
                                            const SkPaint& skPaint, const SkMatrix& viewMatrix,
                                            const char text[], size_t byteLength,
                                            SkScalar x, SkScalar y,
                                            const SkIRect& regionClipBounds) {
    SkASSERT(byteLength == 0 || text != NULL);

    // nothing to draw
    if (text == NULL || byteLength == 0) {
        return;
    }

    fViewMatrix = viewMatrix;
    SkDrawCacheProc          glyphCacheProc = skPaint.getDrawCacheProc();
    SkAutoGlyphCache         autoCache(skPaint, &fDeviceProperties, NULL);
    SkGlyphCache*            cache = autoCache.getCache();

    SkTArray<SkScalar> positions;

    const char* textPtr = text;
    SkFixed stopX = 0;
    SkFixed stopY = 0;
    SkFixed origin;
    switch (skPaint.getTextAlign()) {
        case SkPaint::kRight_Align: origin = SK_Fixed1; break;
        case SkPaint::kCenter_Align: origin = SK_FixedHalf; break;
        case SkPaint::kLeft_Align: origin = 0; break;
        default: SkFAIL("Invalid paint origin"); return;
    }

    SkAutoKern autokern;
    const char* stop = text + byteLength;
    while (textPtr < stop) {
        // don't need x, y here, since all subpixel variants will have the
        // same advance
        const SkGlyph& glyph = glyphCacheProc(cache, &textPtr, 0, 0);

        SkFixed width = glyph.fAdvanceX + autokern.adjust(glyph);
        positions.push_back(SkFixedToScalar(stopX + SkFixedMul(origin, width)));

        SkFixed height = glyph.fAdvanceY;
        positions.push_back(SkFixedToScalar(stopY + SkFixedMul(origin, height)));

        stopX += width;
        stopY += height;
    }
    SkASSERT(textPtr == stop);

    // now adjust starting point depending on alignment
    SkScalar alignX = SkFixedToScalar(stopX);
    SkScalar alignY = SkFixedToScalar(stopY);
    if (skPaint.getTextAlign() == SkPaint::kCenter_Align) {
        alignX = SkScalarHalf(alignX);
        alignY = SkScalarHalf(alignY);
    } else if (skPaint.getTextAlign() == SkPaint::kLeft_Align) {
        alignX = 0;
        alignY = 0;
    }
    x -= alignX;
    y -= alignY;
    SkPoint offset = SkPoint::Make(x, y);

    this->onDrawPosText(rt, clip, paint, skPaint, viewMatrix, text, byteLength, positions.begin(),
                        2, offset, regionClipBounds);
}