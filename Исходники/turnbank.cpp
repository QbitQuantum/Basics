void TurnAndBank::createBall(void){
    QImage _glassImage = QImage(QSize(800,800), QImage::Format_ARGB32);
    _glassImage.fill(0x00ffffff);
    
    QPainter p;
    
    p.setRenderHint(QPainter::Antialiasing, true);
    p.begin(&_glassImage);
    p.translate(400, 400);
    
    // QLinearGradient gradient(0,101,0,199);
    // gradient.setColorAt(0, SKYBLUE);
    // gradient.setColorAt(1, GROUNDBROWN);

    QRadialGradient gradient(0,-4500, 4750, 0, 30000);
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::green);
    gradient.setSpread(QGradient::ReflectSpread);
    
    QBrush gbrush(gradient);
    p.setBrush(gbrush);
    //    p.drawRect(-350, 120, 700, 150);
    
    
    QPainterPath pathBottom;
    pathBottom.moveTo(-310, 150);
    pathBottom.arcTo(-2500+50,-3830-1000,5000,5000, -96, 12);
    //pathBottom.lineTo(310, 250);
    pathBottom.arcTo(-2000,-3700,4000,4000, -81, -18);
    //pathBottom.lineTo(-310, 150);
    
    //    pathBottom.lineTo(-240,0);
    //pathBottom.arcTo(-240,-240,480,480, 180, 180);
    
    //    p.setPen(QPen(QColor(79, 106, 25), 0, Qt::SolidLine,
    //                     Qt::FlatCap, Qt::MiterJoin));
    p.setPen(QPen(Qt::white, 4, Qt::SolidLine,
                  Qt::FlatCap, Qt::MiterJoin));
    p.setPen(Qt::NoPen);
    p.setBrush(gbrush);
    // p.setBrush(GROUNDBROWN);
    
    p.drawPath(pathBottom);
    
    p.setBrush(Qt::black);
    
    
    p.setPen(QPen(Qt::black, 4, Qt::SolidLine,
                  Qt::FlatCap, Qt::MiterJoin));
    p.drawLine(-50,170, -50, 300);
    p.drawLine(50,170, 50, 300);
    
    p.end();
    
    _ball = QPixmap::fromImage(_glassImage, Qt::AutoColor);
    
}    