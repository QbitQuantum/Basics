//Reset current screen config to match previously-saved settings
void RRSettings::ApplyPrevious(){
  QSettings set("lumina-desktop","lumina-xconfig");
  set.beginGroup("MonitorSettings");
  //Setup a couple lists
  QStringList devs = set.childGroups(); //known/saved devices
  QList<ScreenInfo> screens = RRSettings::CurrentScreens();
  QStringList lastactive = set.value("lastActive",QStringList()).toStringList();
  //Now go through all the saved settings and put that info into the array
  QString primary;
  QStringList avail;
  for(int i=0; i<screens.length(); i++){
    //if(screens[i].order>=0){screens[i].order = -1; } //reset all screen orders (need to re-check all)
    if(devs.contains(screens[i].ID) && screens[i].isavailable){ //only load settings for monitors which are currently attached
      set.beginGroup(screens[i].ID);
        screens[i].geom = set.value("geometry", QRect()).toRect();
        screens[i].isprimary = set.value("isprimary", false).toBool();
        if(screens[i].isprimary){ primary = screens[i].ID; }
        screens[i].isactive = lastactive.contains(screens[i].ID);
        screens[i].order = (screens[i].isactive ? -1 : -3); //check/ignore
      set.endGroup();
    }else if(screens[i].isavailable){
      screens[i].order = -2; //needs activation/placement
    }else{
      screens[i].order = -3; //ignored
    }
    //Now clean up the list as needed
    if(screens[i].order < -2){ screens.removeAt(i); i--; } //just remove it (less to loop through later)
    else{ avail << screens[i].ID; } //needed for some checks later - make it simple
  }
  //NOTE ABOUT orders: -1: check geom, -2: auto-add to end, -3: ignored
  
  //Quick checks for simple systems - just use current X config as-is
  if(devs.isEmpty() && (avail.filter("LVDS").isEmpty() || screens.length()==1) ){ return; } 

  //Typical ID's: LVDS-[], DVI-I-[], DP-[], HDMI-[], VGA-[]
  //"LVDS" is the built-in laptop display normally
  if(primary.isEmpty()){
    QStringList priority; priority << "LVDS" << "DP" << "HDMI" << "DVI" << "VGA";
    for(int i=0; i<priority.length() && primary.isEmpty(); i++){
      QStringList filter = avail.filter(priority[i]);
      if(!filter.isEmpty()){ filter.sort(); primary = filter.first(); }
    }
    if(primary.isEmpty()){ primary = avail.first(); }
  }
  //Ensure only one monitor is primary, and reset a few flags
  for(int i=0; i<screens.length(); i++){  
    if(screens[i].ID!=primary){ screens[i].isprimary = false; }  
    screens[i].isactive = true; //we want all these monitors to be active eventually
  }
  // Handle all the available monitors
  int handled = 0;
  int cx = 0; //current x point
  while(handled<screens.length()){
    //Go through horizontally and place monitors (TO-DO: Vertical placement not handled yet)
    int next = -1;
    int diff = -1;
    for(int i=0; i<screens.length(); i++){
      if(screens[i].order==-1){
        if(diff<0 || ((screens[i].geom.x()-cx) < diff)){
          diff = screens[i].geom.x()-cx;
          next = i;
        }
      }
    }//end loop over screens
    if(next<0){
      //Go through and start adding the non-assigned screens to the end
      for(int i=0; i<screens.length(); i++){
        if(screens[i].order==-2){
          if(diff<0 || ((screens[i].geom.x()-cx) < diff)){
            diff = screens[i].geom.x()-cx;
            next = i;
          }
        }
      } //end loop over screens
    }
    if(next>=0){ 
      cx+=screens[next].geom.width();
      screens[next].order = handled; handled++; 
    }else{
      //Still missing monitors (vertical alignment?)
      qDebug() << "Unhandled Monitors:" << screens.length()-handled;
      break;
    }
  }
  //Now reset the display with xrandr
  RRSettings::Apply(screens);
}