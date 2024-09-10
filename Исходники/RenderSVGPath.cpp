void RenderSVGPath::strokeShape(GraphicsContext& context) const
{
    if (!style().svgStyle().hasVisibleStroke())
        return;

    RenderSVGShape::strokeShape(context);

    if (m_zeroLengthLinecapLocations.isEmpty())
        return;

    Path* usePath;
    AffineTransform nonScalingTransform;

    if (hasNonScalingStroke())
        nonScalingTransform = nonScalingStrokeTransform();

    GraphicsContextStateSaver stateSaver(context, true);
    useStrokeStyleToFill(context);
    for (size_t i = 0; i < m_zeroLengthLinecapLocations.size(); ++i) {
        usePath = zeroLengthLinecapPath(m_zeroLengthLinecapLocations[i]);
        if (hasNonScalingStroke())
            usePath = nonScalingStrokePath(usePath, nonScalingTransform);
        context.fillPath(*usePath);
    }
}