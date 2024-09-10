void GrAtlasTextBlob::flushRunAsPaths(GrContext* context, GrDrawContext* dc,
                                      const SkSurfaceProps& props,
                                      const SkTextBlobRunIterator& it,
                                      const GrClip& clip, const SkPaint& skPaint,
                                      SkDrawFilter* drawFilter, const SkMatrix& viewMatrix,
                                      const SkIRect& clipBounds, SkScalar x, SkScalar y) {
    SkPaint runPaint = skPaint;

    size_t textLen = it.glyphCount() * sizeof(uint16_t);
    const SkPoint& offset = it.offset();

    it.applyFontToPaint(&runPaint);

    if (drawFilter && !drawFilter->filter(&runPaint, SkDrawFilter::kText_Type)) {
        return;
    }

    runPaint.setFlags(GrTextUtils::FilterTextFlags(props, runPaint));

    switch (it.positioning()) {
        case SkTextBlob::kDefault_Positioning:
            GrTextUtils::DrawTextAsPath(context, dc, clip, runPaint, viewMatrix,
                                        (const char *)it.glyphs(),
                                        textLen, x + offset.x(), y + offset.y(), clipBounds);
            break;
        case SkTextBlob::kHorizontal_Positioning:
            GrTextUtils::DrawPosTextAsPath(context, dc, props, clip, runPaint, viewMatrix,
                                           (const char*)it.glyphs(),
                                           textLen, it.pos(), 1, SkPoint::Make(x, y + offset.y()),
                                           clipBounds);
            break;
        case SkTextBlob::kFull_Positioning:
            GrTextUtils::DrawPosTextAsPath(context, dc, props, clip, runPaint, viewMatrix,
                                           (const char*)it.glyphs(),
                                           textLen, it.pos(), 2, SkPoint::Make(x, y), clipBounds);
            break;
    }
}