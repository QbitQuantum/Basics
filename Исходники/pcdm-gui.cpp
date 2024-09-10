void PCDMgui::retranslateUi(){
  //All the text-setting for the main interface needs to be done here
  //virtual keyboard button
  //if(currentTheme->itemIsEnabled("vkeyboard")){
    virtkeyboardButton->setToolTip(tr("Virtual Keyboard"));
    virtkeyboardButton->setText(tr("Virtual Keyboard"));
  //}
  //locale switcher button
  localeButton->setToolTip(tr("Change locale"));
  localeButton->setText(tr("Locale"));
  //keyboard layout button
  keyboardButton->setToolTip(tr("Change Keyboard Layout"));
  keyboardButton->setText(tr("Keyboard Layout"));
  //system button
  systemButton->defaultAction()->setToolTip(tr("Shutdown the computer"));
  systemButton->defaultAction()->setText(tr("System"));
  //Menu entries for system button
    systemMenu->clear();	
    systemMenu->addAction( tr("Restart"),this, SLOT(slotRestartComputer()) );
    systemMenu->addAction( tr("Shut Down"), this, SLOT(slotShutdownComputer()) );
    if(DEBUG_MODE){systemMenu->addAction( tr("Close PCDM"), this, SLOT(slotClosePCDM()) ); }
    systemButton->setMenu(systemMenu);
  //The main login widget
  if(hostname.isEmpty()){
    if(DEBUG_MODE){ qDebug() << "Finding Hostname..."; }
    //Find the system hostname
    hostname = pcbsd::Utils::runShellCommand("hostname").join(" ").simplified();
    if(DEBUG_MODE){ qDebug() << " - Host:" << hostname; }
    loginW->displayHostName(hostname);	  
  }
  if(DEBUG_MODE){ qDebug() << "Translate Login Widget"; }
  loginW->retranslateUi();
  
  //The desktop switcher
  
    //Get the new desktop list (translated)
    QStringList deList = Backend::getAvailableDesktops(); //priority ordered
    QString lastDE;
    if(!loginW->currentUsername().isEmpty()){ lastDE = Backend::getLastDE(loginW->currentUsername()); }
    if(DEBUG_MODE){ qDebug() << "DE's:" << deList << lastDE; }
    if(lastDE.isEmpty()){ lastDE = deList[0]; }
    //Organize the desktop list alphabetically by filename
    deList.removeDuplicates();
    QStringList DEL;
    for(int i=0; i<deList.length(); i++){
      //Check the icon
        QString deIcon = Backend::getDesktopIcon(deList[i]);
	if( deIcon.isEmpty() ){ deIcon = currentTheme->itemIcon("desktop"); } //set the default icon if none given
        if( !QFile::exists(deIcon) ){ deIcon = ":/images/desktop.png"; }
      QString entry = deList[i] +":::"+deIcon+":::"+Backend::getDesktopComment(deList[i]);
      DEL << entry;
    }
    DEL.sort(); //make it alphabetical
    //Now fill the switcher
    if(!simpleDESwitcher){
      deSwitcher->removeAllItems();
      for(int i=0; i<DEL.length(); i++){
	//Now add the item
	deSwitcher->addItem( DEL[i].section(":::",0,0), DEL[i].section(":::",1,1), DEL[i].section(":::",2,2) );
      }
      if(DEBUG_MODE){ qDebug() << "Last used DE:" << lastDE; }
      //Set the switcher to the last used desktop environment
      if( !lastDE.isEmpty() ){ deSwitcher->setCurrentItem(lastDE); }

    }else{
      //Simple switcher on the login widget
      QStringList deNames, deIcons, deInfo;
      for(int i=0; i<DEL.length(); i++){
        deNames << DEL[i].section(":::",0,0);
	deIcons << DEL[i].section(":::",1,1);
	deInfo << DEL[i].section(":::",2,2);
      }
      if(DEBUG_MODE){ qDebug() << "Loading DE's into the login widget"; }
      loginW->setDesktops(deNames, deIcons, deInfo);
      //Set the switcher to the last used desktop environment
      if(DEBUG_MODE){ qDebug() << "Last used DE:" << lastDE; }
      loginW->setCurrentDE(lastDE);
    }

}