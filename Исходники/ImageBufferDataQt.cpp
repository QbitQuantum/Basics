void ImageBufferData::initPainter()
{
    m_painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    // Since ImageBuffer is used mainly for Canvas, explicitly initialize
    // its painter's pen and brush with the corresponding canvas defaults
    // NOTE: keep in sync with CanvasRenderingContext2D::State
    QPen pen = m_painter->pen();
    pen.setColor(Qt::black);
    pen.setWidth(1);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::SvgMiterJoin);
    pen.setMiterLimit(10);
    m_painter->setPen(pen);
    QBrush brush = m_painter->brush();
    brush.setColor(Qt::black);
    m_painter->setBrush(brush);
    m_painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
}