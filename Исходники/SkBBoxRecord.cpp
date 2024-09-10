void SkBBoxRecord::onDrawText(const void* text, size_t byteLength, SkScalar x, SkScalar y,
                              const SkPaint& paint) {
    SkRect bbox;
    paint.measureText(text, byteLength, &bbox);
    SkPaint::FontMetrics metrics;
    paint.getFontMetrics(&metrics);

    // Vertical and aligned text need to be offset
    if (paint.isVerticalText()) {
        SkScalar h = bbox.fBottom - bbox.fTop;
        if (paint.getTextAlign() == SkPaint::kCenter_Align) {
            bbox.fTop    -= h / 2;
            bbox.fBottom -= h / 2;
        }
        // Pad top and bottom with max extents from FontMetrics
        bbox.fBottom += metrics.fBottom;
        bbox.fTop += metrics.fTop;
    } else {
        SkScalar w = bbox.fRight - bbox.fLeft;
        if (paint.getTextAlign() == SkPaint::kCenter_Align) {
            bbox.fLeft  -= w / 2;
            bbox.fRight -= w / 2;
        } else if (paint.getTextAlign() == SkPaint::kRight_Align) {
            bbox.fLeft  -= w;
            bbox.fRight -= w;
        }
        // Set vertical bounds to max extents from font metrics
        bbox.fTop = metrics.fTop;
        bbox.fBottom = metrics.fBottom;
    }

    // Pad horizontal bounds on each side by half of max vertical extents (this is sort of
    // arbitrary, but seems to produce reasonable results, if there were a way of getting max
    // glyph X-extents to pad by, that may be better here, but FontMetrics fXMin and fXMax seem
    // incorrect on most platforms (too small in Linux, never even set in Windows).
    SkScalar pad = (metrics.fBottom - metrics.fTop) / 2;
    bbox.fLeft  -= pad;
    bbox.fRight += pad;

    bbox.fLeft += x;
    bbox.fRight += x;
    bbox.fTop += y;
    bbox.fBottom += y;
    if (this->transformBounds(bbox, &paint)) {
        INHERITED::onDrawText(text, byteLength, x, y, paint);
    }
}