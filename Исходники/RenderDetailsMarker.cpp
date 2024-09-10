Path RenderDetailsMarker::getPath(const LayoutPoint& origin) const
{
    Path result = getCanonicalPath();
    result.transform(AffineTransform().scale(contentWidth().toFloat(), contentHeight().toFloat()));
    result.translate(FloatSize(origin.x().toFloat(), origin.y().toFloat()));
    return result;
}