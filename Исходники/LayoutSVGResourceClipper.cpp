bool LayoutSVGResourceClipper::asPath(const AffineTransform& animatedLocalTransform, const FloatRect& referenceBox, Path& clipPath)
{
    if (!calculateClipContentPathIfNeeded())
        return false;

    clipPath = m_clipContentPath;

    // We are able to represent the clip as a path. Continue with direct clipping,
    // and transform the content to userspace if necessary.
    if (clipPathUnits() == SVGUnitTypes::SVG_UNIT_TYPE_OBJECTBOUNDINGBOX) {
        AffineTransform transform;
        transform.translate(referenceBox.x(), referenceBox.y());
        transform.scaleNonUniform(referenceBox.width(), referenceBox.height());
        clipPath.transform(transform);
    }

    // Transform path by animatedLocalTransform.
    clipPath.transform(animatedLocalTransform);
    return true;
}