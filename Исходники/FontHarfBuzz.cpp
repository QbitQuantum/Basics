void Font::drawGlyphs(GraphicsContext* gc, const SimpleFontData* font,
    const GlyphBuffer& glyphBuffer, unsigned from, unsigned numGlyphs,
    const FloatPoint& point, const FloatRect& textRect) const
{
    SkScalar x = SkFloatToScalar(point.x());
    SkScalar y = SkFloatToScalar(point.y());

    const OpenTypeVerticalData* verticalData = font->verticalData();
    if (font->platformData().orientation() == Vertical && verticalData) {
        SkAutoSTMalloc<32, SkPoint> storage(numGlyphs);
        SkPoint* pos = storage.get();

        AffineTransform savedMatrix = gc->getCTM();
        gc->concatCTM(AffineTransform(0, -1, 1, 0, point.x(), point.y()));
        gc->concatCTM(AffineTransform(1, 0, 0, 1, -point.x(), -point.y()));

        const unsigned kMaxBufferLength = 256;
        Vector<FloatPoint, kMaxBufferLength> translations;

        const FontMetrics& metrics = font->fontMetrics();
        SkScalar verticalOriginX = SkFloatToScalar(point.x() + metrics.floatAscent() - metrics.floatAscent(IdeographicBaseline));
        float horizontalOffset = point.x();

        unsigned glyphIndex = 0;
        while (glyphIndex < numGlyphs) {
            unsigned chunkLength = std::min(kMaxBufferLength, numGlyphs - glyphIndex);

            const Glyph* glyphs = glyphBuffer.glyphs(from + glyphIndex);
            translations.resize(chunkLength);
            verticalData->getVerticalTranslationsForGlyphs(font, &glyphs[0], chunkLength, reinterpret_cast<float*>(&translations[0]));

            x = verticalOriginX;
            y = SkFloatToScalar(point.y() + horizontalOffset - point.x());

            float currentWidth = 0;
            for (unsigned i = 0; i < chunkLength; ++i, ++glyphIndex) {
                pos[i].set(
                    x + SkIntToScalar(lroundf(translations[i].x())),
                    y + -SkIntToScalar(-lroundf(currentWidth - translations[i].y())));
                currentWidth += glyphBuffer.advanceAt(from + glyphIndex);
            }
            horizontalOffset += currentWidth;
            paintGlyphs(gc, font, glyphs, chunkLength, pos, textRect);
        }

        gc->setCTM(savedMatrix);
        return;
    }

    if (!glyphBuffer.hasOffsets()) {
        SkAutoSTMalloc<64, SkScalar> storage(numGlyphs);
        SkScalar* xpos = storage.get();
        const float* adv = glyphBuffer.advances(from);
        for (unsigned i = 0; i < numGlyphs; i++) {
            xpos[i] = x;
            x += SkFloatToScalar(adv[i]);
        }
        const Glyph* glyphs = glyphBuffer.glyphs(from);
        paintGlyphsHorizontal(gc, font, glyphs, numGlyphs, xpos, SkFloatToScalar(y), textRect);
        return;
    }

    // FIXME: text rendering speed:
    // Android has code in their WebCore fork to special case when the
    // GlyphBuffer has no advances other than the defaults. In that case the
    // text drawing can proceed faster. However, it's unclear when those
    // patches may be upstreamed to WebKit so we always use the slower path
    // here.
    SkAutoSTMalloc<32, SkPoint> storage(numGlyphs);
    SkPoint* pos = storage.get();
    const FloatSize* offsets = glyphBuffer.offsets(from);
    const float* advances = glyphBuffer.advances(from);
    SkScalar advanceSoFar = SkFloatToScalar(0);
    for (unsigned i = 0; i < numGlyphs; i++) {
        pos[i].set(
            x + SkFloatToScalar(offsets[i].width()) + advanceSoFar,
            y + SkFloatToScalar(offsets[i].height()));
        advanceSoFar += SkFloatToScalar(advances[i]);
    }

    const Glyph* glyphs = glyphBuffer.glyphs(from);
    paintGlyphs(gc, font, glyphs, numGlyphs, pos, textRect);
}