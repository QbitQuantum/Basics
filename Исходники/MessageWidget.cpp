 QPixmap MessageWidget::_decorateAvatar(QPixmap *avatar)
 {
     QBrush brush(*avatar);
     QPixmap roundedAvatar(avatar->width(), avatar->height());
     roundedAvatar.fill(Qt::transparent);
     QPainter painter;
     painter.begin(&roundedAvatar);
     QPainterPath roundRect;
     roundRect.addRoundedRect(0, 0, roundedAvatar.width(), roundedAvatar.height(), 10, 10, Qt::AbsoluteSize);
     painter.setRenderHint(QPainter::Antialiasing, true);
     painter.fillPath(roundRect, brush);
     painter.setRenderHint(QPainter::Antialiasing, false);
     painter.end();
     return roundedAvatar;
 }