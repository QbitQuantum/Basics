bool SkMatrixImageFilter::onFilterBounds(const SkIRect& src, const SkMatrix& ctm,
                                         SkIRect* dst) const {
    SkMatrix transformInverse;
    if (!fTransform.invert(&transformInverse)) {
        return false;
    }
    SkMatrix matrix;
    if (!ctm.invert(&matrix)) {
        return false;
    }
    matrix.postConcat(transformInverse);
    matrix.postConcat(ctm);
    SkRect floatBounds;
    matrix.mapRect(&floatBounds, SkRect::Make(src));
    SkIRect bounds = floatBounds.roundOut();
    if (getInput(0) && !getInput(0)->filterBounds(bounds, ctm, &bounds)) {
        return false;
    }

    *dst = bounds;
    return true;
}