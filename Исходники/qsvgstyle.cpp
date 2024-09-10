void QSvgStrokeStyle::apply(QPainter *p, const QSvgNode *, QSvgExtraStates &states)
{
    m_oldStroke = p->pen();
    m_oldStrokeOpacity = states.strokeOpacity;
    m_oldStrokeDashOffset = states.strokeDashOffset;
    m_oldVectorEffect = states.vectorEffect;

    QPen pen = p->pen();

    qreal oldWidth = pen.widthF();
    qreal width = m_stroke.widthF();
    if (oldWidth == 0)
        oldWidth = 1;
    if (width == 0)
        width = 1;
    qreal scale = oldWidth / width;

    if (m_strokeOpacitySet)
        states.strokeOpacity = m_strokeOpacity;

    if (m_vectorEffectSet)
        states.vectorEffect = m_vectorEffect;

    if (m_strokeSet) {
        if (m_style)
            pen.setBrush(m_style->brush(p, states));
        else
            pen.setBrush(m_stroke.brush());
    }

    if (m_strokeWidthSet)
        pen.setWidthF(m_stroke.widthF());

    bool setDashOffsetNeeded = false;

    if (m_strokeDashOffsetSet) {
        states.strokeDashOffset = m_strokeDashOffset;
        setDashOffsetNeeded = true;
    }

    if (m_strokeDashArraySet) {
        if (m_stroke.style() == Qt::SolidLine) {
            pen.setStyle(Qt::SolidLine);
        } else if (m_strokeWidthSet || oldWidth == 1) {
            // If both width and dash array was set, the dash array is already scaled correctly.
            pen.setDashPattern(m_stroke.dashPattern());
            setDashOffsetNeeded = true;
        } else {
            // If dash array was set, but not the width, the dash array has to be scaled with respect to the old width.
            QVector<qreal> dashes = m_stroke.dashPattern();
            for (int i = 0; i < dashes.size(); ++i)
                dashes[i] /= oldWidth;
            pen.setDashPattern(dashes);
            setDashOffsetNeeded = true;
        }
    } else if (m_strokeWidthSet && pen.style() != Qt::SolidLine && scale != 1) {
        // If the width was set, but not the dash array, the old dash array must be scaled with respect to the new width.
        QVector<qreal> dashes = pen.dashPattern();
        for (int i = 0; i < dashes.size(); ++i)
            dashes[i] *= scale;
        pen.setDashPattern(dashes);
        setDashOffsetNeeded = true;
    }

    if (m_strokeLineCapSet)
        pen.setCapStyle(m_stroke.capStyle());
    if (m_strokeLineJoinSet)
        pen.setJoinStyle(m_stroke.joinStyle());
    if (m_strokeMiterLimitSet)
        pen.setMiterLimit(m_stroke.miterLimit());

    // You can have dash offset on solid strokes in SVG files, but not in Qt.
    // QPen::setDashOffset() will set the pen style to Qt::CustomDashLine,
    // so don't call the method if the pen is solid.
    if (setDashOffsetNeeded && pen.style() != Qt::SolidLine) {
        qreal currentWidth = pen.widthF();
        if (currentWidth == 0)
            currentWidth = 1;
        pen.setDashOffset(states.strokeDashOffset / currentWidth);
    }

    pen.setCosmetic(states.vectorEffect);

    p->setPen(pen);
}