void PanWidget::
paintEvent ( QPaintEvent * event )
{
    QPainter painter (this);
    painter.setRenderHints (QPainter::Antialiasing | QPainter::HighQualityAntialiasing);
    painter.fillPath (path_, QColor(220,220,220,200));
    painter.strokePath (path_, QPen(
                            QColor(100,100,100,200),
                            hasFocus () ? 1.6 : .8,
                            Qt::SolidLine,
                            Qt::RoundCap,
                            Qt::RoundJoin));

    QWidget::paintEvent(event);
}