void SkRandomScalerContext::generateMetrics(SkGlyph* glyph) {
    fProxy->getAdvance(glyph);

    SkVector advance;
    fMatrix.mapXY(SkFixedToScalar(glyph->fAdvanceX),
                  SkFixedToScalar(glyph->fAdvanceY), &advance);
    glyph->fAdvanceX = SkScalarToFixed(advance.fX);
    glyph->fAdvanceY = SkScalarToFixed(advance.fY);

    SkPath path;
    fProxy->getPath(*glyph, &path);
    path.transform(fMatrix);

    SkRect storage;
    const SkPaint& paint = fFace->paint();
    const SkRect& newBounds = paint.doComputeFastBounds(path.getBounds(),
                                                        &storage,
                                                        SkPaint::kFill_Style);
    SkIRect ibounds;
    newBounds.roundOut(&ibounds);
    glyph->fLeft = ibounds.fLeft;
    glyph->fTop = ibounds.fTop;
    glyph->fWidth = ibounds.width();
    glyph->fHeight = ibounds.height();

    // Here we will change the mask format of the glyph
    // NOTE this is being overridden by the base class
    SkMask::Format format;
    switch (glyph->getGlyphID() % 6) {
        case 0:
            format = SkMask::kLCD16_Format;
            break;
        case 1:
            format = SkMask::kA8_Format;
            break;
        case 2:
            format = SkMask::kARGB32_Format;
            break;
        default:
            // we will fiddle with these in generate image
            format = (SkMask::Format)MASK_FORMAT_UNKNOWN;
    }

    glyph->fMaskFormat = format;
}