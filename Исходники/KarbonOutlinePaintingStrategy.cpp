 virtual void paintBorder(KoShape *shape, QPainter &painter, const KoViewConverter &converter)
 {
     KoShape::applyConversion(painter, converter);
     painter.strokePath(shape->outline(), m_pen);
 }