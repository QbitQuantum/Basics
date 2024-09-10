void MountTray::loadSavedSettings(){
  //The saved settings file
  QString filename = QDir::homePath()+"/.mounttray.settings";
  //Set the defaults
  useDiskWatcher=true; useDiskTimerDevd=true;
  diskTimerMaxMS=3600000; //1 hour refresh timer
  useAutoPlay = true;
  //Now load the file
  QFile file(filename);
  if(file.exists()){
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){ 
      qDebug() << "-Could not open settings file: using defaults";
      return; 
    }
    QTextStream in(&file);
    while(!in.atEnd()){
      QString line = in.readLine();
      if(!line.startsWith("#")){ //skip comment lines
        QString var = line.section(")",0,0,QString::SectionSkipEmpty).simplified();
        QString val = line.section(")",1,30,QString::SectionSkipEmpty).simplified();
        if(var=="UseDiskSpaceMonitoring"){ 
          if(val.toLower() == "true"){ useDiskWatcher = true;}
          else{ useDiskWatcher = false; }
        }else if(var=="UseDiskSpaceDevdTiming"){
          if(val.toLower() == "true"){ useDiskTimerDevd = true;}
          else{ useDiskTimerDevd = false; }	
        }else if(var=="DiskSpaceTimingMaxMilliseconds"){
          diskTimerMaxMS = val.toInt();	
        }else if(var=="AutoPlay"){
	  useAutoPlay = (val.toLower()=="true");
	}
      }
    }
    file.close();
  }else{
    qDebug() << "-Creating new settings file with defaults";
    saveCurrentSettings();
  }
}