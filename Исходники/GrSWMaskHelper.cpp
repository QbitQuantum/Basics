void GrSWMaskHelper::DrawToTargetWithPathMask(GrTexture* texture,
                                              GrDrawContext* drawContext,
                                              const GrPaint* paint,
                                              const GrUserStencilSettings* userStencilSettings,
                                              const GrClip& clip,
                                              GrColor color,
                                              const SkMatrix& viewMatrix,
                                              const SkIRect& rect) {
    SkMatrix invert;
    if (!viewMatrix.invert(&invert)) {
        return;
    }

    SkRect dstRect = SkRect::MakeLTRB(SK_Scalar1 * rect.fLeft,
                                      SK_Scalar1 * rect.fTop,
                                      SK_Scalar1 * rect.fRight,
                                      SK_Scalar1 * rect.fBottom);

    // We use device coords to compute the texture coordinates. We take the device coords and apply
    // a translation so that the top-left of the device bounds maps to 0,0, and then a scaling
    // matrix to normalized coords.
    SkMatrix maskMatrix;
    maskMatrix.setIDiv(texture->width(), texture->height());
    maskMatrix.preTranslate(SkIntToScalar(-rect.fLeft), SkIntToScalar(-rect.fTop));

    GrPipelineBuilder pipelineBuilder(*paint, drawContext->isUnifiedMultisampled());
    pipelineBuilder.setRenderTarget(drawContext->accessRenderTarget());
    pipelineBuilder.setUserStencil(userStencilSettings);

    pipelineBuilder.addCoverageFragmentProcessor(
                         GrSimpleTextureEffect::Create(texture,
                                                       maskMatrix,
                                                       GrTextureParams::kNone_FilterMode,
                                                       kDevice_GrCoordSet))->unref();

    SkAutoTUnref<GrDrawBatch> batch(GrRectBatchFactory::CreateNonAAFill(color, SkMatrix::I(),
                                                                        dstRect, nullptr, &invert));
    drawContext->drawBatch(pipelineBuilder, clip, batch);
}