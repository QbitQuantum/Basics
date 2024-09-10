// Draw a mask using the supplied paint. Since the coverage/geometry
// is already burnt into the mask this boils down to a rect draw.
// Return true if the mask was successfully drawn.
static bool draw_mask(GrDrawContext* drawContext,
                      const GrClip& clip,
                      const SkMatrix& viewMatrix,
                      const SkIRect& maskRect,
                      GrPaint* grp,
                      GrTexture* mask) {
    SkMatrix matrix;
    matrix.setTranslate(-SkIntToScalar(maskRect.fLeft), -SkIntToScalar(maskRect.fTop));
    matrix.postIDiv(mask->width(), mask->height());
    matrix.preConcat(viewMatrix);
    grp->addCoverageFragmentProcessor(GrSimpleTextureEffect::Make(mask, nullptr, matrix));

    SkMatrix inverse;
    if (!viewMatrix.invert(&inverse)) {
        return false;
    }
    drawContext->fillRectWithLocalMatrix(clip, *grp, SkMatrix::I(), SkRect::Make(maskRect),
                                         inverse);
    return true;
}