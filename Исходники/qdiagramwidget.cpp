void QDiagramWidget::init(const GPX_wrapper *gpxmw)
{
    const GPX_wrapper::TrackPointProperty choices[] = {
        GPX_wrapper::none,
        GPX_wrapper::distance,
        GPX_wrapper::leglength,
        GPX_wrapper::speed,
        GPX_wrapper::altitude,
        GPX_wrapper::latitude,
        GPX_wrapper::longitude,
        GPX_wrapper::heading,
        GPX_wrapper::sat,
        GPX_wrapper::magvar,
        GPX_wrapper::hdop,
        GPX_wrapper::vdop,
        GPX_wrapper::pdop,
        GPX_wrapper::ageofdgpsdata,
        GPX_wrapper::dgpsid,
        GPX_wrapper::geoidheight,
        GPX_wrapper::heartrate
    };

    this->gpxmw = gpxmw;

    curveMain = GPX_wrapper::altitude;
    curveSecondary = GPX_wrapper::distance;

    QAction *actCurveMain = new QAction("Main curve", this);
    QAction *actCurveSecondary = new QAction("Secondary curve", this);
    QMenu *submenuCurveMain = new QMenu;
    QMenu *submenuCurveSecondary = new QMenu;
    actCurveMain->setMenu(submenuCurveMain);
    actCurveSecondary->setMenu(submenuCurveSecondary);
    addAction(actCurveMain);
    addAction(actCurveSecondary);
    for (size_t i = 0; i < sizeof(choices)/sizeof(GPX_wrapper::TrackPointProperty); ++i)
    {
        QAction *actCurveMain = new QAction(gpxmw->getTrackPointPropertyLabel(choices[i]), this);
        actCurveMain->setData(choices[i]);
        connect(actCurveMain, SIGNAL(triggered()), this, SLOT(on_actionCurveMain_triggered()));
        submenuCurveMain->addAction(actCurveMain);

        QAction *actCurveSecondary = new QAction(gpxmw->getTrackPointPropertyLabel(choices[i]), this);
        actCurveSecondary->setData(choices[i]);
        connect(actCurveSecondary, SIGNAL(triggered()), this, SLOT(on_actionCurveSecondary_triggered()));
        submenuCurveSecondary->addAction(actCurveSecondary);
    }

    build();
}