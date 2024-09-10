static QPainterPath getPathStroke(const QPainterPath &path, const RenderObject* object, const RenderStyle* style)
{ 
    QPainterPathStroker s;
    s.setWidth(KSVGPainterFactory::cssPrimitiveToLength(object, style->svgStyle()->strokeWidth(), 1.0));

    if (style->svgStyle()->capStyle() == ButtCap)
        s.setCapStyle(Qt::FlatCap);
    else if (style->svgStyle()->capStyle() == RoundCap)
        s.setCapStyle(Qt::RoundCap);

    if (style->svgStyle()->joinStyle() == MiterJoin) {
        s.setJoinStyle(Qt::MiterJoin);
        s.setMiterLimit((qreal) style->svgStyle()->strokeMiterLimit());
    } else if(style->svgStyle()->joinStyle() == RoundJoin)
        s.setJoinStyle(Qt::RoundJoin);

    const KCDashArray& dashes = KSVGPainterFactory::dashArrayFromRenderingStyle(style);
    double dashOffset = KSVGPainterFactory::cssPrimitiveToLength(object, style->svgStyle()->strokeDashOffset(), 0.0);

    unsigned int dashLength = !dashes.isEmpty() ? dashes.size() : 0;
    if(dashLength) {
        QVector<qreal> pattern;
        unsigned int count = (dashLength % 2) == 0 ? dashLength : dashLength * 2;

        for(unsigned int i = 0; i < count; i++)
            pattern.append(dashes[i % dashLength] / (float)s.width());

        s.setDashPattern(pattern);
    
        Q_UNUSED(dashOffset);
        // TODO: dash-offset, does/will qt4 API allow it? (Rob)
    }

    return s.createStroke(path);
}