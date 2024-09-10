void KoPathToolSelection::paint(QPainter &painter, const KoViewConverter &converter)
{
    int handleRadius = m_tool->canvas()->shapeController()->resourceManager()->handleRadius();

    PathShapePointMap::iterator it(m_shapePointMap.begin());
    for (; it != m_shapePointMap.end(); ++it) {
        painter.save();

        painter.setTransform(it.key()->absoluteTransformation(&converter) * painter.transform());
        KoShape::applyConversion(painter, converter);

        foreach(KoPathPoint *p, it.value())
            p->paint(painter, handleRadius, KoPathPoint::All);

        painter.restore();
    }
}