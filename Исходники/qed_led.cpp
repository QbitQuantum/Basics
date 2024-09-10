void QedRoundLED::paintEvent(QPaintEvent *event)
{
    qreal lowerInset, upperInset;
    (void)event;

    QPainterPath baseCirclePath;
    QRectF baseBox(0.0, 0.0, my.bound, my.bound);
    baseCirclePath.arcTo(baseBox, 0.0, 360.0);
    baseCirclePath.closeSubpath();
    QLinearGradient baseGradient(0, 0, 0, 1.33846 * my.bound);
    baseGradient.setColorAt(0.0, Qt::lightGray);
    baseGradient.setColorAt(1.0, Qt::white);

    QPainterPath seatCirclePath;
    lowerInset = 0.06666 * my.bound;
    upperInset = my.bound - (lowerInset * 2.0);
    QRectF seatBox(lowerInset, lowerInset, upperInset, upperInset);
    seatCirclePath.arcTo(seatBox, 0.0, 360.0);
    seatCirclePath.closeSubpath();
    QLinearGradient seatGradient(0, 0, 0, 0.7692 * my.bound);
    seatGradient.setColorAt(0.0, Qt::lightGray);
    seatGradient.setColorAt(1.0, Qt::darkGray);

    QPainterPath mainCirclePath;
    lowerInset = 0.1 * my.bound;
    upperInset = my.bound - (lowerInset * 2.0);
    QRectF mainBox(lowerInset, lowerInset, upperInset, upperInset);
    mainCirclePath.arcTo(mainBox, 0.0, 360.0);
    mainCirclePath.closeSubpath();
    QLinearGradient mainGradient(0, 0, 0, 1.23076 * my.bound);
    mainGradient.setColorAt(0.0, my.color);
    mainGradient.setColorAt(1.0, Qt::white);

    QPainterPath reflectCirclePath;
    QRectF reflectBox(0.18538 * my.bound, 0.12969 * my.bound,
		      0.61384 * my.bound, 0.48615 * my.bound);
    reflectCirclePath.arcTo(reflectBox, 0.0, 360.0);
    reflectCirclePath.closeSubpath();
    QLinearGradient reflectGradient(0, 0, 0, 1.22953 * my.bound);
    reflectGradient.setColorAt(0.0, Qt::white);
    reflectGradient.setColorAt(1.0, my.color);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    painter.setBrush(baseGradient);
    painter.drawPath(baseCirclePath);
    painter.setBrush(seatGradient);
    painter.drawPath(seatCirclePath);
    painter.setBrush(mainGradient);
    painter.drawPath(mainCirclePath);
    painter.setBrush(reflectGradient);
    painter.drawPath(reflectCirclePath);
}