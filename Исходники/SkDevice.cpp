void SkBaseDevice::drawTextBlob(const SkDraw& draw, const SkTextBlob* blob, SkScalar x, SkScalar y,
                                const SkPaint &paint, SkDrawFilter* drawFilter) {

    SkPaint runPaint = paint;

    SkTextBlobRunIterator it(blob);
    for (;!it.done(); it.next()) {
        size_t textLen = it.glyphCount() * sizeof(uint16_t);
        const SkPoint& offset = it.offset();
        // applyFontToPaint() always overwrites the exact same attributes,
        // so it is safe to not re-seed the paint for this reason.
        it.applyFontToPaint(&runPaint);

        if (drawFilter && !drawFilter->filter(&runPaint, SkDrawFilter::kText_Type)) {
            // A false return from filter() means we should abort the current draw.
            runPaint = paint;
            continue;
        }

        runPaint.setFlags(this->filterTextFlags(runPaint));

        switch (it.positioning()) {
        case SkTextBlob::kDefault_Positioning:
            this->drawText(draw, it.glyphs(), textLen, x + offset.x(), y + offset.y(), runPaint);
            break;
        case SkTextBlob::kHorizontal_Positioning:
            this->drawPosText(draw, it.glyphs(), textLen, it.pos(), 1,
                              SkPoint::Make(x, y + offset.y()), runPaint);
            break;
        case SkTextBlob::kFull_Positioning:
            this->drawPosText(draw, it.glyphs(), textLen, it.pos(), 2,
                              SkPoint::Make(x, y), runPaint);
            break;
        default:
            SkFAIL("unhandled positioning mode");
        }

        if (drawFilter) {
            // A draw filter may change the paint arbitrarily, so we must re-seed in this case.
            runPaint = paint;
        }
    }
}