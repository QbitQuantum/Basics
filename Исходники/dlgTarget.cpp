static void RefreshCalculator(void) {
  WndProperty* wp;

  RefreshTask();
  RefreshTaskStatistics();
  target_point = max(target_point,ActiveWayPoint);

  bool nodisplay = !AATEnabled 
    || (target_point==0) 
    || !ValidTaskPoint(target_point+1);

  if (btnMove) {
    if (nodisplay) {
      btnMove->SetVisible(false);
      TargetMoveMode = false;
    } else {
      btnMove->SetVisible(true);
    }
  } 

  nodisplay = nodisplay || TargetMoveMode;

  wp = (WndProperty*)wf->FindByName(TEXT("prpTaskPoint"));
  if (wp) {
    if (TargetMoveMode) {
      wp->SetVisible(false);
    } else {
      wp->SetVisible(true);
    }
  }

  WindowControl* wc = (WindowControl*)wf->FindByName(TEXT("btnOK"));
  if (wc) {
    if (TargetMoveMode) {
      wc->SetVisible(false);
    } else {
      wc->SetVisible(true);
    }
  }

  wp = (WndProperty*)wf->FindByName(TEXT("prpAATTargetLocked"));
  if (wp) {
    wp->GetDataField()->Set(Task[target_point].AATTargetLocked);
    wp->RefreshDisplay();
    if (nodisplay) {
      wp->SetVisible(false);
    } else {
      wp->SetVisible(true);
    }
  }

  wp = (WndProperty*)wf->FindByName(TEXT("prpRange"));
  if (wp) {
    wp->GetDataField()->SetAsFloat(Range*100.0);
    wp->RefreshDisplay();
    if (nodisplay) {
      wp->SetVisible(false);
    } else {
      wp->SetVisible(true);
    }
  }

  wp = (WndProperty*)wf->FindByName(TEXT("prpRadial"));
  if (wp) {
    wp->GetDataField()->SetAsFloat(Radial);
    wp->RefreshDisplay();
    if (nodisplay) {
      wp->SetVisible(false);
    } else {
      wp->SetVisible(true);
    }
  }

  // update outputs
  double dd = CALCULATED_INFO.TaskTimeToGo;
  if ((CALCULATED_INFO.TaskStartTime>0.0)&&(CALCULATED_INFO.Flying)) {
    dd += GPS_INFO.Time-CALCULATED_INFO.TaskStartTime;
  }
  dd= min(24.0*60.0,dd/60.0);
  wp = (WndProperty*)wf->FindByName(TEXT("prpAATEst"));
  if (wp) {
    wp->GetDataField()->SetAsFloat(dd);
    wp->RefreshDisplay();
  }
  wp = (WndProperty*)wf->FindByName(TEXT("prpAATDelta"));
  if (wp) {
    wp->GetDataField()->SetAsFloat(dd-AATTaskLength);
    if (AATEnabled) {
      wp->SetVisible(true);
    } else {
      wp->SetVisible(false);
    }
    wp->RefreshDisplay();
  }

  double v1;
  if (CALCULATED_INFO.TaskTimeToGo>0) {
    v1 = CALCULATED_INFO.TaskDistanceToGo/
      CALCULATED_INFO.TaskTimeToGo;
  } else {
    v1 = 0;
  }

  wp = (WndProperty*)wf->FindByName(TEXT("prpSpeedRemaining"));
  if (wp) {
    wp->GetDataField()->SetAsFloat(v1*TASKSPEEDMODIFY);
    wp->GetDataField()->SetUnits(Units::GetTaskSpeedName());
    wp->RefreshDisplay();
  }

  wp = (WndProperty*)wf->FindByName(TEXT("prpSpeedAchieved"));
  if (wp) {
    wp->GetDataField()->SetAsFloat(CALCULATED_INFO.TaskSpeed*TASKSPEEDMODIFY);
    wp->GetDataField()->SetUnits(Units::GetTaskSpeedName());
    wp->RefreshDisplay();
  }

}