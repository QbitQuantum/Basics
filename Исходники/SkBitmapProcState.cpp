/**
 *  For the purposes of drawing bitmaps, if a matrix is "almost" translate
 *  go ahead and treat it as if it were, so that subsequent code can go fast.
 */
static bool just_trans_clamp(const SkMatrix& matrix, const SkPixmap& pixmap) {
    SkASSERT(matrix_only_scale_translate(matrix));

    if (matrix.getType() & SkMatrix::kScale_Mask) {
        SkRect dst;
        SkRect src = SkRect::Make(pixmap.bounds());

        // Can't call mapRect(), since that will fix up inverted rectangles,
        // e.g. when scale is negative, and we don't want to return true for
        // those.
        matrix.mapPoints(SkTCast<SkPoint*>(&dst),
                         SkTCast<const SkPoint*>(&src),
                         2);

        // Now round all 4 edges to device space, and then compare the device
        // width/height to the original. Note: we must map all 4 and subtract
        // rather than map the "width" and compare, since we care about the
        // phase (in pixel space) that any translate in the matrix might impart.
        SkIRect idst;
        dst.round(&idst);
        return idst.width() == pixmap.width() && idst.height() == pixmap.height();
    }
    // if we got here, we're either kTranslate_Mask or identity
    return true;
}