Path SVGStyledTransformableElement::toClipPath() const
{
    Path pathData = toPathData();
    // FIXME: How do we know the element has done a layout?
    pathData.transform(animatedLocalTransform());
    return pathData;
}