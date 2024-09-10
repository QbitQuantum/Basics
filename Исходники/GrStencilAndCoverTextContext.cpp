void GrStencilAndCoverTextContext::uncachedDrawTextBlob(GrContext* context,
                                                        GrDrawContext* dc,
                                                        const GrClip& clip,
                                                        const SkPaint& skPaint,
                                                        const SkMatrix& viewMatrix,
                                                        const SkSurfaceProps& props,
                                                        const SkTextBlob* blob,
                                                        SkScalar x, SkScalar y,
                                                        SkDrawFilter* drawFilter,
                                                        const SkIRect& clipBounds) {
    SkPaint runPaint = skPaint;

    SkTextBlobRunIterator it(blob);
    for (;!it.done(); it.next()) {
        size_t textLen = it.glyphCount() * sizeof(uint16_t);
        const SkPoint& offset = it.offset();

        // applyFontToPaint() always overwrites the exact same attributes,
        // so it is safe to not re-seed the paint for this reason.
        it.applyFontToPaint(&runPaint);

        if (drawFilter && !drawFilter->filter(&runPaint, SkDrawFilter::kText_Type)) {
            // A false return from filter() means we should abort the current draw.
            runPaint = skPaint;
            continue;
        }

        runPaint.setFlags(GrTextUtils::FilterTextFlags(props, runPaint));

        GrPaint grPaint;
        if (!SkPaintToGrPaint(context, dc, runPaint, viewMatrix, &grPaint)) {
            return;
        }

        switch (it.positioning()) {
            case SkTextBlob::kDefault_Positioning:
                this->drawText(context, dc, clip, grPaint, runPaint, viewMatrix, props,
                               (const char *)it.glyphs(),
                               textLen, x + offset.x(), y + offset.y(), clipBounds);
                break;
            case SkTextBlob::kHorizontal_Positioning:
                this->drawPosText(context, dc, clip, grPaint, runPaint, viewMatrix, props,
                                  (const char*)it.glyphs(),
                                  textLen, it.pos(), 1, SkPoint::Make(x, y + offset.y()),
                                  clipBounds);
                break;
            case SkTextBlob::kFull_Positioning:
                this->drawPosText(context, dc, clip, grPaint, runPaint, viewMatrix, props,
                                  (const char*)it.glyphs(),
                                  textLen, it.pos(), 2, SkPoint::Make(x, y), clipBounds);
                break;
        }

        if (drawFilter) {
            // A draw filter may change the paint arbitrarily, so we must re-seed in this case.
            runPaint = skPaint;
        }
    }
}