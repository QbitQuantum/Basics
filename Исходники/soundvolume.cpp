void SoundVolume::paintEvent(QPaintEvent * /*event*/)
{
    Q_D(const SoundVolume);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);
    QPainterPath path;

    auto penWidthf = 1.0;
    auto background =  d->background;
    auto borderColor = d->borderColor;

    const qreal radius = d->radius;;
    const qreal triHeight = 6;
    const qreal triWidth = 8;
    const qreal height = this->height() - triHeight;
    const qreal width = this->width();

    QRectF topRightRect(QPointF(0, 0),
                        QPointF(2 * radius, 2 * radius));
    QRectF bottomRightRect(QPointF(0, height - 2 * radius),
                           QPointF(2 * radius, height));
    QRectF topLeftRect(QPointF(width, 0),
                       QPointF(width - 2 * radius, 2 * radius));
    QRectF bottomLeftRect(QPointF(width, height),
                          QPointF(width - 2 * radius, height - 2 * radius));

    path.moveTo(radius, 0.0);
    path.lineTo(width - radius, 0.0);
    path.arcTo(topLeftRect, 90.0, 90.0);
    path.lineTo(width, height - radius);
    path.arcTo(bottomLeftRect, 180.0, -90.0);
    path.lineTo(width / 2 + triWidth / 2, height);
    path.lineTo(width / 2, height + triHeight);
    path.lineTo(width / 2 - triWidth / 2, height);
    path.lineTo(radius, height);

    path.arcTo(bottomRightRect, 270.0, -90.0);
    path.lineTo(0.0, radius);

    path.arcTo(topRightRect, 180.0, -90.0);
    path.lineTo(radius, 0.0);

    // FIXME: light: white
//    painter.fillPath(path, QColor(49, 49, 49));
    painter.fillPath(path, background);

    // FIXME: light: QColor(0, 0, 0, 51)
//    QPen pen(QColor(0, 0, 0, 0.1 * 255));
    QPen pen(borderColor);
    pen.setWidth(penWidthf);
    painter.strokePath(path, pen);
}