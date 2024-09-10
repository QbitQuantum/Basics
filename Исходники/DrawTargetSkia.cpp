void
DrawTargetSkia::Mask(const Pattern &aSource,
                     const Pattern &aMask,
                     const DrawOptions &aOptions)
{
    MarkChanged();
    AutoPaintSetup paint(mCanvas.get(), aOptions, aSource);

    SkPaint maskPaint;
    SetPaintPattern(maskPaint, aMask);

    SkLayerRasterizer *raster = new SkLayerRasterizer();
    raster->addLayer(maskPaint);
    SkSafeUnref(paint.mPaint.setRasterizer(raster));

    // Skia only uses the mask rasterizer when we are drawing a path/rect.
    // Take our destination bounds and convert them into user space to use
    // as the path to draw.
    SkPath path;
    path.addRect(SkRect::MakeWH(SkScalar(mSize.width), SkScalar(mSize.height)));

    Matrix temp = mTransform;
    temp.Invert();
    SkMatrix mat;
    GfxMatrixToSkiaMatrix(temp, mat);
    path.transform(mat);

    mCanvas->drawPath(path, paint.mPaint);
}