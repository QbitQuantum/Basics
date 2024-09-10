SkLinearBitmapPipeline::SkLinearBitmapPipeline(
    const SkMatrix& inverse,
    SkFilterQuality filterQuality,
    SkShader::TileMode xTile, SkShader::TileMode yTile,
    SkColor paintColor,
    const SkPixmap& srcPixmap)
{
    SkISize dimensions = srcPixmap.info().dimensions();
    const SkImageInfo& srcImageInfo = srcPixmap.info();

    SkMatrix adjustedInverse = inverse;
    if (filterQuality == kNone_SkFilterQuality) {
        if (inverse.getScaleX() >= 0.0f) {
            adjustedInverse.setTranslateX(
                nextafterf(inverse.getTranslateX(), std::floor(inverse.getTranslateX())));
        }
        if (inverse.getScaleY() >= 0.0f) {
            adjustedInverse.setTranslateY(
                nextafterf(inverse.getTranslateY(), std::floor(inverse.getTranslateY())));
        }
    }

    SkScalar dx = adjustedInverse.getScaleX();

    // If it is an index 8 color type, the sampler converts to unpremul for better fidelity.
    SkAlphaType alphaType = srcImageInfo.alphaType();
    if (srcPixmap.colorType() == kIndex_8_SkColorType) {
        alphaType = kUnpremul_SkAlphaType;
    }

    float postAlpha = SkColorGetA(paintColor) * (1.0f / 255.0f);
    // As the stages are built, the chooser function may skip a stage. For example, with the
    // identity matrix, the matrix stage is skipped, and the tilerStage is the first stage.
    auto blenderStage = choose_blender_for_shading(alphaType, postAlpha, &fBlenderStage);
    auto samplerStage = choose_pixel_sampler(
        blenderStage, filterQuality, xTile, yTile,
        srcPixmap, paintColor, &fSampleStage, &fAccessor);
    auto tilerStage   = choose_tiler(samplerStage, dimensions, xTile, yTile,
                                     filterQuality, dx, &fTileStage);
    fFirstStage       = choose_matrix(tilerStage, adjustedInverse, &fMatrixStage);
    fLastStage        = blenderStage;
}