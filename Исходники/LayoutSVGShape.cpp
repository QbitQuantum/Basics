FloatRect LayoutSVGShape::calculateStrokeBoundingBox() const
{
    ASSERT(m_path);
    FloatRect strokeBoundingBox = m_fillBoundingBox;

    if (style()->svgStyle().hasStroke()) {
        StrokeData strokeData;
        SVGLayoutSupport::applyStrokeStyleToStrokeData(strokeData, styleRef(), *this);
        if (hasNonScalingStroke()) {
            AffineTransform nonScalingTransform = nonScalingStrokeTransform();
            if (nonScalingTransform.isInvertible()) {
                Path* usePath = nonScalingStrokePath(m_path.get(), nonScalingTransform);
                FloatRect strokeBoundingRect = usePath->strokeBoundingRect(strokeData);
                strokeBoundingRect = nonScalingTransform.inverse().mapRect(strokeBoundingRect);
                strokeBoundingBox.unite(strokeBoundingRect);
            }
        } else {
            strokeBoundingBox.unite(path().strokeBoundingRect(strokeData));
        }
    }

    return strokeBoundingBox;
}