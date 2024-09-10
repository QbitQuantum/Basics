bool RenderForeignObject::nodeAtPoint(const HitTestRequest& request, HitTestResult& result, int x, int y, int tx, int ty, HitTestAction hitTestAction)
{
    TransformationMatrix totalTransform = absoluteTransform();
    totalTransform *= translationForAttributes();
    double localX, localY;
    totalTransform.inverse().map(x, y, &localX, &localY);
    return RenderBlock::nodeAtPoint(request, result, static_cast<int>(localX), static_cast<int>(localY), tx, ty, hitTestAction);
}