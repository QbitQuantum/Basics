bool SkLayerRasterizer::onRasterize(const SkPath& path, const SkMatrix& matrix,
                                    const SkIRect* clipBounds,
                                    SkMask* mask, SkMask::CreateMode mode) const {
    SkASSERT(fLayers);
    if (fLayers->empty()) {
        return false;
    }

    if (SkMask::kJustRenderImage_CreateMode != mode) {
        if (!compute_bounds(*fLayers, path, matrix, clipBounds, &mask->fBounds))
            return false;
    }

    if (SkMask::kComputeBoundsAndRenderImage_CreateMode == mode) {
        mask->fFormat   = SkMask::kA8_Format;
        mask->fRowBytes = mask->fBounds.width();
        size_t size = mask->computeImageSize();
        if (0 == size) {
            return false;   // too big to allocate, abort
        }
        mask->fImage = SkMask::AllocImage(size);
        memset(mask->fImage, 0, size);
    }

    if (SkMask::kJustComputeBounds_CreateMode != mode) {
        SkBitmap        device;
        SkRasterClip    rectClip;
        SkDraw          draw;
        SkMatrix        translatedMatrix;  // this translates us to our local pixels
        SkMatrix        drawMatrix;        // this translates the path by each layer's offset

        rectClip.setRect(SkIRect::MakeWH(mask->fBounds.width(), mask->fBounds.height()));

        translatedMatrix = matrix;
        translatedMatrix.postTranslate(-SkIntToScalar(mask->fBounds.fLeft),
                                       -SkIntToScalar(mask->fBounds.fTop));

        device.installMaskPixels(*mask);

        draw.fBitmap    = &device;
        draw.fMatrix    = &drawMatrix;
        draw.fRC        = &rectClip;
        draw.fClip      = &rectClip.bwRgn();
        // we set the matrixproc in the loop, as the matrix changes each time (potentially)

        SkDeque::F2BIter        iter(*fLayers);
        SkLayerRasterizer_Rec*  rec;

        while ((rec = (SkLayerRasterizer_Rec*)iter.next()) != NULL) {
            drawMatrix = translatedMatrix;
            drawMatrix.preTranslate(rec->fOffset.fX, rec->fOffset.fY);
            draw.drawPath(path, rec->fPaint);
        }
    }
    return true;
}