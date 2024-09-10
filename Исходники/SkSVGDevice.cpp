void SkSVGDevice::drawPoints(const SkDraw& draw, SkCanvas::PointMode mode, size_t count,
                             const SkPoint pts[], const SkPaint& paint) {
    SkPath path;

    switch (mode) {
            // todo
        case SkCanvas::kPoints_PointMode:
            SkDebugf("unsupported operation: drawPoints(kPoints_PointMode)\n");
            break;
        case SkCanvas::kLines_PointMode:
            count -= 1;
            for (size_t i = 0; i < count; i += 2) {
                path.rewind();
                path.moveTo(pts[i]);
                path.lineTo(pts[i+1]);
                AutoElement elem("path", fWriter, fResourceBucket, draw, paint);
                elem.addPathAttributes(path);
            }
            break;
        case SkCanvas::kPolygon_PointMode:
            if (count > 1) {
                path.addPoly(pts, SkToInt(count), false);
                path.moveTo(pts[0]);
                AutoElement elem("path", fWriter, fResourceBucket, draw, paint);
                elem.addPathAttributes(path);
            }
            break;
    }
}