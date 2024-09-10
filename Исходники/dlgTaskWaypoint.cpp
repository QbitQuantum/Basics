static void SetValues(bool first=false) {
  WndProperty* wp;

  wp = (WndProperty*)wf->FindByName(TEXT("prpTaskFinishLine"));
  if (wp) {
    DataFieldEnum* dfe;
    dfe = (DataFieldEnum*)wp->GetDataField();
    if (first) {
	// LKTOKEN  _@M210_ = "Cylinder" 
      dfe->addEnumText(gettext(TEXT("_@M210_")));
	// LKTOKEN  _@M393_ = "Line" 
      dfe->addEnumText(gettext(TEXT("_@M393_")));
	// LKTOKEN  _@M274_ = "FAI Sector" 
      dfe->addEnumText(gettext(TEXT("_@M274_")));
    }
    dfe->Set(FinishLine);
    wp->RefreshDisplay();
  }

  wp = (WndProperty*)wf->FindByName(TEXT("prpTaskFinishRadius"));
  if (wp) {
    wp->GetDataField()->SetAsFloat(lround(FinishRadius*DISTANCEMODIFY*DISTANCE_ROUNDING)/DISTANCE_ROUNDING);
    wp->GetDataField()->SetUnits(Units::GetDistanceName());
    wp->RefreshDisplay();
  }

  wp = (WndProperty*)wf->FindByName(TEXT("prpTaskStartLine"));
  if (wp) {
    DataFieldEnum* dfe;
    dfe = (DataFieldEnum*)wp->GetDataField();
    if (first) {
	// LKTOKEN  _@M210_ = "Cylinder" 
      dfe->addEnumText(gettext(TEXT("_@M210_")));
	// LKTOKEN  _@M393_ = "Line" 
      dfe->addEnumText(gettext(TEXT("_@M393_")));
	// LKTOKEN  _@M274_ = "FAI Sector" 
      dfe->addEnumText(gettext(TEXT("_@M274_")));
    }
    dfe->SetDetachGUI(true); // disable call to OnAATEnabled
    dfe->Set(StartLine);
    dfe->SetDetachGUI(false);
    wp->RefreshDisplay();
  }

  wp = (WndProperty*)wf->FindByName(TEXT("prpTaskStartRadius"));
  if (wp) {
    wp->GetDataField()->SetAsFloat(lround(StartRadius*DISTANCEMODIFY*DISTANCE_ROUNDING)/DISTANCE_ROUNDING);
    wp->GetDataField()->SetUnits(Units::GetDistanceName());
    wp->RefreshDisplay();
  }

  wp = (WndProperty*)wf->FindByName(TEXT("prpTaskFAISector"));
  if (wp) {
    // 110223 CAN ANYONE PLEASE CHECK WHAT THE HACK IS A BOOL FOR BILL GATES? BECAUSE IF FALSE IS -1 THEN
    // WE HAVE MANY PROBLEMS! I THINK IT IS TIME TO GO BACK TO bool AND GET RID OF MS BOOLS!!
    wp->SetVisible(AATEnabled==0);
    DataFieldEnum* dfe;
    dfe = (DataFieldEnum*)wp->GetDataField();
    if (first) {
	// LKTOKEN  _@M210_ = "Cylinder" 
      dfe->addEnumText(gettext(TEXT("_@M210_")));
	// LKTOKEN  _@M274_ = "FAI Sector" 
      dfe->addEnumText(gettext(TEXT("_@M274_")));
      dfe->addEnumText(gettext(TEXT("DAe 0.5/10")));
    }
    dfe->SetDetachGUI(true); // disable call to OnAATEnabled
    dfe->Set(SectorType);
    dfe->SetDetachGUI(false);
    wp->RefreshDisplay();
  }

  wp = (WndProperty*)wf->FindByName(TEXT("prpTaskSectorRadius"));
  if (wp) {
    wp->SetVisible(AATEnabled==0);
    wp->GetDataField()->SetAsFloat(lround(SectorRadius*DISTANCEMODIFY*DISTANCE_ROUNDING)/DISTANCE_ROUNDING);
    wp->GetDataField()->SetUnits(Units::GetDistanceName());
    wp->RefreshDisplay();
  }

  wp = (WndProperty*)wf->FindByName(TEXT("prpAutoAdvance"));
  if (wp) {
    DataFieldEnum* dfe;
    dfe = (DataFieldEnum*)wp->GetDataField();
    if (first) {
	// LKTOKEN  _@M418_ = "Manual" 
      dfe->addEnumText(gettext(TEXT("_@M418_")));
	// LKTOKEN _@M897_ "Auto"
      dfe->addEnumText(gettext(TEXT("_@M897_")));
	// LKTOKEN  _@M97_ = "Arm" 
      dfe->addEnumText(gettext(TEXT("_@M97_")));
	// LKTOKEN  _@M96_ = "Arm start" 
      dfe->addEnumText(gettext(TEXT("_@M96_")));
    }
    dfe->Set(AutoAdvance);
    wp->RefreshDisplay();
  }

  wp = (WndProperty*)wf->FindByName(TEXT("prpMinTime"));
  if (wp) {
    wp->SetVisible(AATEnabled>0 && !ISPARAGLIDER);
    wp->GetDataField()->SetAsFloat(AATTaskLength);
    wp->RefreshDisplay();
  }

  wp = (WndProperty*)wf->FindByName(TEXT("prpEnableMultipleStartPoints"));
  if (wp) {
    wp->SetVisible(!ISPARAGLIDER);
    wp->GetDataField()->Set(EnableMultipleStartPoints);
    wp->RefreshDisplay();
  }

  wp = (WndProperty*)wf->FindByName(TEXT("prpAATEnabled"));
  if (wp) {
	if (ISPARAGLIDER) {
		wp->SetVisible(false);
		AATEnabled=TRUE;
		wp->RefreshDisplay(); 
	} else {
		bool aw = (AATEnabled != 0);
		wp->GetDataField()->Set(aw);
		wp->RefreshDisplay(); 
	}
  }

  WndButton* wb;
  wb = (WndButton *)wf->FindByName(TEXT("EditStartPoints"));
  if (wb) {
    wb->SetVisible(EnableMultipleStartPoints!=0 && !ISPARAGLIDER);
  }

}