void GLabel::paintEvent(QPaintEvent *e)
{
    if (people == GLabel::She) {
        QRectF rectangle(50.0, 10.0, this->width() - 20 - 40, this->height() - 20);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setBrush(QBrush(QColor(255, 255, 255)));
        painter.drawRoundedRect(rectangle, 10, 10);

        QPointF points[3] = {
           QPointF(40, 33),
           QPointF(51, 29),
           QPointF(50, 38),
       };

       QPen pen;
       pen.setColor(QColor(255, 255, 255));
       painter.setPen(pen);
       painter.drawPolygon(points, 3);

       QPen pen1;
       pen1.setColor(Qt::black);
       painter.setRenderHint(QPainter::Antialiasing, true);
       painter.setPen(pen1);
       painter.drawLine(points[0], points[1]);
       painter.drawLine(points[0], points[2]);
    }
    else if(people == GLabel::Me)
    {
        QRectF rectangle;
//        if (this->width() > 300) {
//            rectangle.setRect(10.0, 10.0, 300, this->height() - 20);
//        } else {
//            rectangle.setRect(10.0, 10.0, this->width() - 20 - 40, this->height() - 20);
//        }
        rectangle.setRect(10.0, 10.0, this->width() - 20 - 40, this->height() - 20);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setBrush(QBrush(QColor(0, 255, 0)));
        painter.drawRoundedRect(rectangle, 10, 10);

        QPointF points[3] = {
           QPointF(this->width()-40, 33),
           QPointF(this->width()-51, 28),
           QPointF(this->width()-51, 38),
       };

       QPen pen;
       pen.setColor(QColor(0, 255, 0));
       painter.setPen(pen);
       painter.drawPolygon(points, 3);

       QPen pen1;
       pen.setColor(Qt::black);
       painter.setPen(pen1);
       painter.setRenderHint(QPainter::Antialiasing, true);
       painter.drawLine(points[0], points[1]);
       painter.drawLine(points[0], points[2]);

       label_people->setGeometry(this->width() - 30, 18, 30, 30);

//       if (this->width() > 300) {
//           this->setGeometry(((QWidget*)this->parent())->width()- 15 - this->width(), this->y(), 360, (this->height()));
//       } else {
//           this->setGeometry(((QWidget*)this->parent())->width()- 15 - this->width(), this->y(), this->width(), (this->height()));
//       }
       this->setGeometry(((QWidget*)this->parent())->width()- 15 - this->width(), this->y(), this->width(), (this->height()));
    }
}