// Paint the horizontal handle as a gradient, paint
// the vertical handle as a line.
void QMacSplitterHandle::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setWorldMatrixEnabled(false);
    painter.setViewTransformEnabled(false);

    QColor topColor(145, 145, 145);
    QColor bottomColor(142, 142, 142);
    QColor gradientStart(252, 252, 252);
    QColor gradientStop(223, 223, 223);

    if (orientation() == Qt::Vertical) {
        painter.setPen(topColor);
        painter.drawLine(0, 0, width(), 0);
        painter.setPen(bottomColor);
        painter.drawLine(0, height() - 1, width(), height() - 1);

        QLinearGradient linearGrad(QPointF(0, 0), QPointF(0, height() -3));
        linearGrad.setColorAt(0, gradientStart);
        linearGrad.setColorAt(1, gradientStop);
        painter.fillRect(QRect(QPoint(0,1), size() - QSize(0, 2)), QBrush(linearGrad));
    } else {
        painter.setPen(topColor);
        painter.drawLine(0, 0, 0, height());
    }
}