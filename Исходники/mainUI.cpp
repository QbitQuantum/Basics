bool MainUI::fillVerticalAppArea( QScrollArea* area, QStringList applist, bool filter){
  //clear the scroll area first
  clearScrollArea(area);
  bool ok = false; //returns whether any apps were shown after filtering
  //Re-create the layout
  QVBoxLayout *layout = new QVBoxLayout;
    QList<NGApp> apps = PBI->AppInfo(applist);
    for(int i=0; i<apps.length(); i++){
	bool goodApp = false;
	if(apps[i].type.toLower()=="graphical"){goodApp = ui->actionGraphical_Apps->isChecked(); }
	else if(apps[i].type.toLower()=="text"){goodApp = ui->actionText_Apps->isChecked(); }
	else if(apps[i].type.toLower()=="server"){goodApp = ui->actionServer_Apps->isChecked(); }
	else{goodApp = ui->actionRaw_Packages->isChecked(); }
	if( !filter || goodApp){
          LargeItemWidget *item = new LargeItemWidget(this,apps[i], checkIcon(apps[i].icon, apps[i].type) );
          connect(item,SIGNAL(appClicked(QString)),this,SLOT(slotGoToApp(QString)) );
          layout->addWidget(item); 
	  ok = true;
	}
    }
    layout->addStretch();
    area->widget()->setLayout(layout);
    return ok;
}