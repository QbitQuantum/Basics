QT_FT_Outline *QOutlineMapper::convertPath(const QVectorPath &path)
{
    int count = path.elementCount();

#ifdef QT_DEBUG_CONVERT
    printf("QOutlineMapper::convertPath(VP), size=%d\n", count);
#endif
    beginOutline(path.hasWindingFill() ? Qt::WindingFill : Qt::OddEvenFill);

    if (path.elements()) {
        // TODO: if we do closing of subpaths in convertElements instead we
        // could avoid this loop
        const QPainterPath::ElementType *elements = path.elements();
        const QPointF *points = reinterpret_cast<const QPointF *>(path.points());

        for (int index = 0; index < count; ++index) {
            switch (elements[index]) {
                case QPainterPath::MoveToElement:
                    if (index == count - 1)
                        continue;
                    moveTo(points[index]);
                    break;

                case QPainterPath::LineToElement:
                    lineTo(points[index]);
                    break;

                case QPainterPath::CurveToElement:
                    curveTo(points[index], points[index+1], points[index+2]);
                    index += 2;
                    break;

                default:
                    break; // This will never hit..
            }
        }

    } else {
        // ### We can kill this copying and just use the buffer straight...

        m_elements.resize(count);
        if (count)
            memcpy(m_elements.data(), path.points(), count* sizeof(QPointF));

        m_element_types.resize(0);
    }

    endOutline();
    return outline();
}