void GrTextUtils::DrawDFText(GrAtlasTextBlob* blob, int runIndex,
                             GrBatchFontCache* fontCache, const SkSurfaceProps& props,
                             const SkPaint& skPaint, GrColor color,
                             const SkMatrix& viewMatrix,
                             const char text[], size_t byteLength,
                             SkScalar x, SkScalar y) {
    SkASSERT(byteLength == 0 || text != nullptr);

    // nothing to draw
    if (text == nullptr || byteLength == 0) {
        return;
    }

    SkPaint::GlyphCacheProc glyphCacheProc = skPaint.getGlyphCacheProc(true);
    SkAutoDescriptor desc;
    skPaint.getScalerContextDescriptor(&desc, props, SkPaint::FakeGamma::Off, nullptr);
    SkGlyphCache* origPaintCache = SkGlyphCache::DetachCache(skPaint.getTypeface(),
                                                             desc.getDesc());

    SkTArray<SkScalar> positions;

    const char* textPtr = text;
    SkFixed stopX = 0;
    SkFixed stopY = 0;
    SkFixed origin = 0;
    switch (skPaint.getTextAlign()) {
        case SkPaint::kRight_Align: origin = SK_Fixed1; break;
        case SkPaint::kCenter_Align: origin = SK_FixedHalf; break;
        case SkPaint::kLeft_Align: origin = 0; break;
    }

    SkAutoKern autokern;
    const char* stop = text + byteLength;
    while (textPtr < stop) {
        // don't need x, y here, since all subpixel variants will have the
        // same advance
        const SkGlyph& glyph = glyphCacheProc(origPaintCache, &textPtr);

        SkFixed width = glyph.fAdvanceX + autokern.adjust(glyph);
        positions.push_back(SkFixedToScalar(stopX + SkFixedMul(origin, width)));

        SkFixed height = glyph.fAdvanceY;
        positions.push_back(SkFixedToScalar(stopY + SkFixedMul(origin, height)));

        stopX += width;
        stopY += height;
    }
    SkASSERT(textPtr == stop);

    SkGlyphCache::AttachCache(origPaintCache);

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

    DrawDFPosText(blob, runIndex, fontCache, props, skPaint, color, viewMatrix, text, byteLength,
                  positions.begin(), 2, offset);
}