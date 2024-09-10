void XYVirtualKeyboard::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    int btn_w = 60;
    QPainterPath path;

    path.moveTo(width() - 40, 15);
    path.lineTo(width() - 30, 25);
    path.lineTo(width() - 20, 15);
    painter.setPen(XYSKIN->borderPen);
    if (!XYSKIN->topBKPixmap.isNull())
    {
        painter.setBrush(XYSKIN->topBKPixmap.scaled(width(),
                                                    letterLabel->height() + 8));
    }
    else
    {
        painter.setBrush(XYSKIN->topColor);
    }

    painter.drawRect(rect().x(), rect().y(), rect().width(), letterLabel->height() + 8);
    triangleBtnRect = QRect(rect().width() - btn_w, rect().y(), btn_w, letterLabel->height() + 8);

    if (triangleBtnPressed)
    {
        if (!XYSKIN->triangleBKPressedPixmap.isNull())
        {
            painter.setBrush(XYSKIN->triangleBKPressedPixmap.scaled(triangleBtnRect.size()));
            painter.drawRect(triangleBtnRect);
        }
        else
        {
            painter.setBrush(XYSKIN->trianglePressedBKColor);
            painter.setPen(painter.brush().color());
            painter.drawRect(triangleBtnRect);
            painter.setPen(XYSKIN->trianglePen);
            painter.drawPath(path);
        }
    }
    else
    {
        if (!XYSKIN->triangleBKPixmap.isNull())
        {
            painter.setBrush(XYSKIN->triangleBKPixmap.scaled(triangleBtnRect.size()));
            painter.drawRect(triangleBtnRect);
        }
        else
        {
            painter.setBrush(XYSKIN->topColor);
            painter.setPen(XYSKIN->trianglePen);
            painter.drawPath(path);
        }
    }

    painter.setPen(XYSKIN->borderPen);
    if (stackedWidget->currentWidget() == symbolDragableWidget
            || stackedWidget->currentWidget() == translateVDragableWidget)
    {
        painter.setBrush(XYSKIN->bottomColor1);
    }
    else
    {
        if (!XYSKIN->bottomBKPixmap.isNull())
        {
            painter.setBrush(XYSKIN->bottomBKPixmap.scaled(width(),
                                                           height() -
                                                           letterLabel->height() - 8));
        }
        else
        {
            painter.setBrush(XYSKIN->bottomColor2);
        }
    }

    painter.drawRect(rect().x(),
                     rect().y() + letterLabel->height() + 8,
                     rect().width(),
                     rect().height() - letterLabel->height() - 8);
}