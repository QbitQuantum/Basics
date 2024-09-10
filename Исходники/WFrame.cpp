void WFrame::manageConnections() {
    
    QObject::connect(c,SIGNAL(exitProgram()),this,SLOT(onExit()));
    QObject::connect(c,SIGNAL(FileLoadedSignal(int)),this,SLOT(FileLoaded(int)));
    QObject::connect(c,SIGNAL(closeMap()),this,SLOT(onCloseMap()));
    QObject::connect(this,SIGNAL(closeMapButtonClicked()),c,SLOT(closeMapClicked()));
    QObject::connect(c,SIGNAL(loadMapSignal()),this,SLOT(loadMap()));
    QObject::connect(c,SIGNAL(noNodesSignal()),this,SLOT(errorNodes()));
    QObject::connect(c,SIGNAL(noOSMSignal()),this,SLOT(errorOSM()));
    QObject::connect(c,SIGNAL(multipleDropSignal()),this,SLOT(multipleDrop()));
    
    //ACTION CONNECTS
    QObject::connect(open,SIGNAL(triggered()),this,SLOT(getFile()));
    QObject::connect(exit,SIGNAL(triggered()),c,SLOT(exitClicked()));
    QObject::connect(closeFile,SIGNAL(triggered()),this,SLOT(checkMap()));
    QObject::connect(about,SIGNAL(triggered()),this,SLOT(showAbout()));
    QObject::connect(links,SIGNAL(triggered()),this,SLOT(showLinks()));
    
}