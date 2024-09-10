altitudewidget::altitudewidget() : QWidget() {
    setFixedSize(100, 200);
    
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(updatewindow()));
    timer->start(10);
    
    altitude = 0.0;
}