// ===========
//  PRIVATE SLOTS
// ===========
void LScreenSaver::ShowScreenSaver(){
  if(DEBUG){ qDebug() << "Showing Screen Saver:" << QDateTime::currentDateTime().toString(); }
  SSRunning = true;
  updating = true;
  //Now remove any current Base widgets (prevent any lingering painting between sessions)
  for(int i=0; i<BASES.length(); i++){
    if(DEBUG){ qDebug() << " - Removing SS Base"; }
    delete BASES.takeAt(i); i--;
  }
  //Now go through and create/show all the various widgets
  QList<QScreen*> SCREENS = QApplication::screens();
  QRect bounds;
  cBright = LOS::ScreenBrightness();
  if(cBright>0){ LOS::setScreenBrightness(cBright/2); } //cut to half while the screensaver is active
  for(int i=0; i<SCREENS.length(); i++){
    bounds = bounds.united(SCREENS[i]->geometry());
    if(DEBUG){ qDebug() << " - New SS Base:" << i; }
    BASES << new SSBaseWidget(this, settings);
    connect(BASES[i], SIGNAL(InputDetected()), this, SLOT(newInputEvent()) );
    //Setup the geometry of the base to match the screen
    BASES[i]->setGeometry(SCREENS[i]->geometry());  //match this screen geometry
    BASES[i]->setPlugin(settings->value("screenplugin"+QString::number(i+1), settings->value("defaultscreenplugin","random").toString() ).toString() );
  }
  //Now set the overall parent widget geometry and show everything
  this->setGeometry(bounds); //overall background widget
  if(!this->isActiveWindow()){
    this->raise();
    this->show();
    this->activateWindow(); 
  }
  for(int i=0; i<BASES.length(); i++){
    BASES[i]->show();
    BASES[i]->startPainting();
  }
  updating = false;
  UpdateTimers();
}