void tst_QWidget_window::tst_qtbug35600()
{
    QWidget w;
    w.show();

    QWidget *wA = new QWidget;
    QHBoxLayout *layoutA = new QHBoxLayout;

    QWidget *wB = new QWidget;
    layoutA->addWidget(wB);

    QWidget *wC = new QWidget;
    layoutA->addWidget(wC);

    wA->setLayout(layoutA);

    QWidget *wD = new QWidget;
    wD->setAttribute(Qt::WA_NativeWindow);
    wD->setParent(wB);

    QWidget *wE = new QWidget(wC, Qt::Tool | Qt::FramelessWindowHint | Qt::WindowTransparentForInput);
    wE->show();

    wA->setParent(&w);

    // QTBUG-35600: program may crash here or on exit
}