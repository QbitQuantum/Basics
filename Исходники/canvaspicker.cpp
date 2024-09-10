    CanvasPicker::CanvasPicker(Plot *plot):
        QObject(plot),
        d_selectedCurve(NULL),
        d_selectedPoint(-1)
    {
        qDebug() << __FILE__ << __FUNCTION__;

        QwtPlotCanvas *canvas = (QwtPlotCanvas*) plot->canvas();

        canvas->installEventFilter(this);

        // We want the focus, but no focus rect. The
        // selected point will be highlighted instead.

        canvas->setFocusPolicy(Qt::StrongFocus);
    #ifndef QT_NO_CURSOR
        canvas->setCursor(Qt::PointingHandCursor);
    #endif
        canvas->setFocusIndicator(QwtPlotCanvas::ItemFocusIndicator);
        canvas->setFocus();

        mousePressed = false;

        accelerate = 0;

    }