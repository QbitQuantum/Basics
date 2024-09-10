void applyTransformToPaintInfo(RenderObject::PaintInfo& paintInfo, const TransformationMatrix& localToAncestorTransform)
{
    if (localToAncestorTransform.isIdentity())
        return;

    paintInfo.context->concatCTM(localToAncestorTransform);
    paintInfo.rect = localToAncestorTransform.inverse().mapRect(paintInfo.rect);
}