void SkGScalerContext::generateMetrics(SkGlyph* glyph) {
    fProxy->getMetrics(glyph);

    SkVector advance;
    fMatrix.mapXY(SkFloatToScalar(glyph->fAdvanceX),
                  SkFloatToScalar(glyph->fAdvanceY), &advance);
    glyph->fAdvanceX = SkScalarToFloat(advance.fX);
    glyph->fAdvanceY = SkScalarToFloat(advance.fY);

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
    glyph->fMaskFormat = SkMask::kARGB32_Format;
}