void GrBitmapTextContext::onDrawPosText(GrRenderTarget* rt, const GrClip& clip,
                                        const GrPaint& paint, const SkPaint& skPaint,
                                        const SkMatrix& viewMatrix,
                                        const char text[], size_t byteLength,
                                        const SkScalar pos[], int scalarsPerPosition,
                                        const SkPoint& offset) {
    SkASSERT(byteLength == 0 || text != NULL);
    SkASSERT(1 == scalarsPerPosition || 2 == scalarsPerPosition);

    // nothing to draw
    if (text == NULL || byteLength == 0/* || fRC->isEmpty()*/) {
        return;
    }

    this->init(rt, clip, paint, skPaint);

    SkDrawCacheProc glyphCacheProc = fSkPaint.getDrawCacheProc();

    SkAutoGlyphCache    autoCache(fSkPaint, &fDeviceProperties, &viewMatrix);
    SkGlyphCache*       cache = autoCache.getCache();
    GrFontScaler*       fontScaler = GetGrFontScaler(cache);

    // if we have RGB, then we won't have any SkShaders so no need to use a localmatrix, but for
    // performance reasons we just invert here instead
    if (!viewMatrix.invert(&fLocalMatrix)) {
        SkDebugf("Cannot invert viewmatrix\n");
        return;
    }

    int numGlyphs = fSkPaint.textToGlyphs(text, byteLength, NULL);
    fTotalVertexCount = kVerticesPerGlyph*numGlyphs;

    const char*        stop = text + byteLength;
    SkTextAlignProc    alignProc(fSkPaint.getTextAlign());
    SkTextMapStateProc tmsProc(viewMatrix, offset, scalarsPerPosition);
    SkScalar halfSampleX = 0, halfSampleY = 0;

    if (cache->isSubpixel()) {
        // maybe we should skip the rounding if linearText is set
        SkAxisAlignment baseline = SkComputeAxisAlignmentForHText(viewMatrix);

        SkFixed fxMask = ~0;
        SkFixed fyMask = ~0;
        if (kX_SkAxisAlignment == baseline) {
            fyMask = 0;
            halfSampleY = SK_ScalarHalf;
        } else if (kY_SkAxisAlignment == baseline) {
            fxMask = 0;
            halfSampleX = SK_ScalarHalf;
        }

        if (SkPaint::kLeft_Align == fSkPaint.getTextAlign()) {
            while (text < stop) {
                SkPoint tmsLoc;
                tmsProc(pos, &tmsLoc);
                Sk48Dot16 fx = SkScalarTo48Dot16(tmsLoc.fX + halfSampleX);
                Sk48Dot16 fy = SkScalarTo48Dot16(tmsLoc.fY + halfSampleY);

                const SkGlyph& glyph = glyphCacheProc(cache, &text,
                                                      fx & fxMask, fy & fyMask);

                if (glyph.fWidth) {
                    this->appendGlyph(GrGlyph::Pack(glyph.getGlyphID(),
                                                    glyph.getSubXFixed(),
                                                    glyph.getSubYFixed(),
                                                    GrGlyph::kCoverage_MaskStyle),
                                      Sk48Dot16FloorToInt(fx),
                                      Sk48Dot16FloorToInt(fy),
                                      fontScaler);
                }
                pos += scalarsPerPosition;
            }
        } else {
            while (text < stop) {
                const char* currentText = text;
                const SkGlyph& metricGlyph = glyphCacheProc(cache, &text, 0, 0);

                if (metricGlyph.fWidth) {
                    SkDEBUGCODE(SkFixed prevAdvX = metricGlyph.fAdvanceX;)
                    SkDEBUGCODE(SkFixed prevAdvY = metricGlyph.fAdvanceY;)
                    SkPoint tmsLoc;
                    tmsProc(pos, &tmsLoc);
                    SkPoint alignLoc;
                    alignProc(tmsLoc, metricGlyph, &alignLoc);

                    Sk48Dot16 fx = SkScalarTo48Dot16(alignLoc.fX + halfSampleX);
                    Sk48Dot16 fy = SkScalarTo48Dot16(alignLoc.fY + halfSampleY);

                    // have to call again, now that we've been "aligned"
                    const SkGlyph& glyph = glyphCacheProc(cache, &currentText,
                                                          fx & fxMask, fy & fyMask);
                    // the assumption is that the metrics haven't changed
                    SkASSERT(prevAdvX == glyph.fAdvanceX);
                    SkASSERT(prevAdvY == glyph.fAdvanceY);
                    SkASSERT(glyph.fWidth);

                    this->appendGlyph(GrGlyph::Pack(glyph.getGlyphID(),
                                                    glyph.getSubXFixed(),
                                                    glyph.getSubYFixed(),
                                                    GrGlyph::kCoverage_MaskStyle),
                                      Sk48Dot16FloorToInt(fx),
                                      Sk48Dot16FloorToInt(fy),
                                      fontScaler);
                }