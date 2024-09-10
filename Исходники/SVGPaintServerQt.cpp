void SVGPaintServer::setPenProperties(const RenderObject* object, const RenderStyle* style, QPen& pen) const
{
    pen.setWidthF(SVGRenderStyle::cssPrimitiveToLength(object, style->svgStyle()->strokeWidth(), 1.0));

    if (style->svgStyle()->capStyle() == ButtCap)
        pen.setCapStyle(Qt::FlatCap);
    else if (style->svgStyle()->capStyle() == RoundCap)
        pen.setCapStyle(Qt::RoundCap);

    if (style->svgStyle()->joinStyle() == MiterJoin) {
        pen.setJoinStyle(Qt::MiterJoin);
        pen.setMiterLimit((qreal) style->svgStyle()->strokeMiterLimit());
    } else if(style->svgStyle()->joinStyle() == RoundJoin)
        pen.setJoinStyle(Qt::RoundJoin);

    const DashArray& dashes = WebCore::dashArrayFromRenderingStyle(style);
    double dashOffset = SVGRenderStyle::cssPrimitiveToLength(object, style->svgStyle()->strokeDashOffset(), 0.0);

    unsigned int dashLength = !dashes.isEmpty() ? dashes.size() : 0;
    if(dashLength) {
        QVector<qreal> pattern;
        unsigned int count = (dashLength % 2) == 0 ? dashLength : dashLength * 2;

        for(unsigned int i = 0; i < count; i++)
            pattern.append(dashes[i % dashLength] / (float)pen.widthF());

        pen.setDashPattern(pattern);

        Q_UNUSED(dashOffset);
        // TODO: dash-offset, does/will qt4 API allow it? (Rob)
    }
}