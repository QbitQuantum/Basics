/*!
    \reimp
 */
void QxtLabel::paintEvent(QPaintEvent* event)
{
    QFrame::paintEvent(event);
    QPainter p(this);
    p.rotate(qxt_d().rot);
    QRect r = contentsRect();
    switch (qxt_d().rot)
    {
    case Qxt::UpsideDown:
        p.translate(-r.width(), -r.height());
        break;

    case Qxt::Clockwise:
        p.translate(0, -r.width());
        break;

    case Qxt::CounterClockwise:
        p.translate(-r.height(), 0);
        break;

    default:
        // nothing to do
        break;
    }

    if (qxt_d().rot & Vertical_Mask)
    {
        QSize s = r.size();
        s.transpose();
        r = QRect(r.topLeft(), s);
    }

    const QString elidedText = fontMetrics().elidedText(qxt_d().text, qxt_d().mode, r.width());
    p.drawText(r, qxt_d().align, elidedText);
}