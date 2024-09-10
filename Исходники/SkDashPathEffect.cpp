// Attempt to trim the line to minimally cover the cull rect (currently
// only works for horizontal and vertical lines).
// Return true if processing should continue; false otherwise.
static bool cull_line(SkPoint* pts, const SkStrokeRec& rec,
                      const SkMatrix& ctm, const SkRect* cullRect,
                      const SkScalar intervalLength) {
    if (nullptr == cullRect) {
        SkASSERT(false); // Shouldn't ever occur in practice
        return false;
    }

    SkScalar dx = pts[1].x() - pts[0].x();
    SkScalar dy = pts[1].y() - pts[0].y();

    if ((dx && dy) || (!dx && !dy)) {
        return false;
    }

    SkRect bounds = *cullRect;
    outset_for_stroke(&bounds, rec);

    // cullRect is in device space while pts are in the local coordinate system
    // defined by the ctm. We want our answer in the local coordinate system.

    SkASSERT(ctm.rectStaysRect());
    SkMatrix inv;
    if (!ctm.invert(&inv)) {
        return false;
    }

    inv.mapRect(&bounds);

    if (dx) {
        SkASSERT(dx && !dy);
        SkScalar minX = pts[0].fX;
        SkScalar maxX = pts[1].fX;

        if (dx < 0) {
            SkTSwap(minX, maxX);
        }

        SkASSERT(minX < maxX);
        if (maxX <= bounds.fLeft || minX >= bounds.fRight) {
            return false;
        }

        // Now we actually perform the chop, removing the excess to the left and
        // right of the bounds (keeping our new line "in phase" with the dash,
        // hence the (mod intervalLength).

        if (minX < bounds.fLeft) {
            minX = bounds.fLeft - SkScalarMod(bounds.fLeft - minX, intervalLength);
        }
        if (maxX > bounds.fRight) {
            maxX = bounds.fRight + SkScalarMod(maxX - bounds.fRight, intervalLength);
        }

        SkASSERT(maxX > minX);
        if (dx < 0) {
            SkTSwap(minX, maxX);
        }
        pts[0].fX = minX;
        pts[1].fX = maxX;
    } else {
        SkASSERT(dy && !dx);
        SkScalar minY = pts[0].fY;
        SkScalar maxY = pts[1].fY;

        if (dy < 0) {
            SkTSwap(minY, maxY);
        }

        SkASSERT(minY < maxY);
        if (maxY <= bounds.fTop || minY >= bounds.fBottom) {
            return false;
        }

        // Now we actually perform the chop, removing the excess to the top and
        // bottom of the bounds (keeping our new line "in phase" with the dash,
        // hence the (mod intervalLength).

        if (minY < bounds.fTop) {
            minY = bounds.fTop - SkScalarMod(bounds.fTop - minY, intervalLength);
        }
        if (maxY > bounds.fBottom) {
            maxY = bounds.fBottom + SkScalarMod(maxY - bounds.fBottom, intervalLength);
        }

        SkASSERT(maxY > minY);
        if (dy < 0) {
            SkTSwap(minY, maxY);
        }
        pts[0].fY = minY;
        pts[1].fY = maxY;
    }

    return true;
}