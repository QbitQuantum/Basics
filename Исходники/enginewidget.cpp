enginewidget::enginewidget() : QWidget() {
    setFixedSize(200, 200);
    
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(updatewindow()));
    timer->start(10);
    
    throttle = 0.0;
}