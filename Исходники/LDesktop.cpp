LDPluginContainer* LDesktop::CreateDesktopPluginContainer(LDPlugin *plug){
  //Verify that a container does not already exist for this plugin
  QList<QMdiSubWindow*> wins = bgDesktop->subWindowList();
  for(int i=0; i<wins.length(); i++){
    if(wins[i]->whatsThis()==plug->ID()){ return 0; }
  }
  //Create a new plugin container
  LDPluginContainer *win = new LDPluginContainer(plug, desktoplocked);
  win->loadInitialSize(); //Sizing should be done before adding the window to the area
  if(desktoplocked){ 
    bgDesktop->addSubWindow(win, Qt::Tool | Qt::FramelessWindowHint);
  }else{ 
    bgDesktop->addSubWindow(win, Qt::Tool | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
  }
  if( !win->hasFixedPosition() ){ 
    //NOTE: This section *only* runs for new plugins - it does not run for re-creations of old plugins
    //Need to determine the location of the plugin (leave size alone)
    if(DEBUG){ qDebug() << " ---  Floating Plugin - find a spot for it"; }
    QPoint pt = findNewPluginLocation(availDPArea, win->size());
    if(pt.x()>=0 && pt.y()>=0){
      win->saveNewPosition(pt); 
      win->move(pt);
      if(DEBUG){ qDebug() << " --- Moving to point:" << pt; }
    }
    //Make sure to remove this plugin from the availability region
    availDPArea = availDPArea.subtracted( QRegion(win->geometry()) );
  }
  QApplication::processEvents();	  
  QTimer::singleShot(300+(5*PLUGINS.length()), win, SLOT(loadInitialPosition()) ); //Now load the position (if one is saved)
  if(DEBUG){ 
    qDebug() << "Initial DP Geom:" << plug->geometry();
    qDebug() << "  - Container Geom:" << win->geometry();
  }
  QApplication::processEvents();
	  
  connect(win, SIGNAL(PluginRemoved(QString)), this, SLOT(DesktopPluginRemoved(QString)) );
  return win;
}