void GLExtras::drawRegion(const SkRegion& region, bool fill, bool drawBorder,
                          const TransformationMatrix* drawMat, Color color)
{
    if (region.isEmpty())
        return;
    if (fill) {
        SkRegion::Iterator rgnIter(region);
        while (!rgnIter.done()) {
            const SkIRect& ir = rgnIter.rect();
            SkRect r;
            r.set(ir.fLeft, ir.fTop, ir.fRight, ir.fBottom);
            drawRing(r, color, drawMat);
            rgnIter.next();
        }
    }
    if (fill && !drawBorder)
        return;
    SkPath path;
    if (!region.getBoundaryPath(&path))
        return;
    SkPath::Iter iter(path, true);
    SkPath::Verb verb;
    SkPoint pts[4];
    SkRegion clip;
    SkIRect startRect;
    while ((verb = iter.next(pts)) != SkPath::kDone_Verb) {
        if (verb == SkPath::kLine_Verb) {
            SkRect r;
            r.set(pts, 2);
            SkIRect line;
            int borderWidth = RING_BORDER_WIDTH;
            if (!fill)
                borderWidth *= 2;
            line.fLeft = r.fLeft - borderWidth;
            line.fRight = r.fRight + borderWidth;
            line.fTop = r.fTop - borderWidth;
            line.fBottom = r.fBottom + borderWidth;
            if (clip.intersects(line)) {
                clip.op(line, SkRegion::kReverseDifference_Op);
                if (clip.isEmpty())
                    continue; // Nothing to draw, continue
                line = clip.getBounds();
                if (SkIRect::Intersects(startRect, line)) {
                    clip.op(startRect, SkRegion::kDifference_Op);
                    if (clip.isEmpty())
                        continue; // Nothing to draw, continue
                    line = clip.getBounds();
                }
            } else {
                clip.setRect(line);
            }
            r.set(line.fLeft, line.fTop, line.fRight, line.fBottom);
            drawRing(r, color, drawMat);
            if (startRect.isEmpty()) {
                startRect.set(line.fLeft, line.fTop, line.fRight, line.fBottom);
            }
        }
        if (verb == SkPath::kMove_Verb) {
            startRect.setEmpty();
        }
    }
}