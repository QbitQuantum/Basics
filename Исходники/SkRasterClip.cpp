bool SkRasterClip::op(const SkPath& path, const SkMatrix& matrix, const SkIRect& devBounds,
                      SkRegion::Op op, bool doAA) {
    AUTO_RASTERCLIP_VALIDATE(*this);
    SkIRect bounds(devBounds);
    this->applyClipRestriction(op, &bounds);

    // base is used to limit the size (and therefore memory allocation) of the
    // region that results from scan converting devPath.
    SkRegion base;

    SkPath devPath;
    if (matrix.isIdentity()) {
        devPath = path;
    } else {
        path.transform(matrix, &devPath);
        devPath.setIsVolatile(true);
    }
    if (SkRegion::kIntersect_Op == op) {
        // since we are intersect, we can do better (tighter) with currRgn's
        // bounds, than just using the device. However, if currRgn is complex,
        // our region blitter may hork, so we do that case in two steps.
        if (this->isRect()) {
            // FIXME: we should also be able to do this when this->isBW(),
            // but relaxing the test above triggers GM asserts in
            // SkRgnBuilder::blitH(). We need to investigate what's going on.
            return this->setPath(devPath, this->bwRgn(), doAA);
        } else {
            base.setRect(this->getBounds());
            SkRasterClip clip;
            clip.setPath(devPath, base, doAA);
            return this->op(clip, op);
        }
    } else {
        base.setRect(bounds);

        if (SkRegion::kReplace_Op == op) {
            return this->setPath(devPath, base, doAA);
        } else {
            SkRasterClip clip;
            clip.setPath(devPath, base, doAA);
            return this->op(clip, op);
        }
    }
}