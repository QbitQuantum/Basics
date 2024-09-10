  bool CPVRGUIActions::ShowTimerSettings(const CPVRTimerInfoTagPtr &timer) const
  {
    CGUIDialogPVRTimerSettings* pDlgInfo = dynamic_cast<CGUIDialogPVRTimerSettings*>(g_windowManager.GetWindow(WINDOW_DIALOG_PVR_TIMER_SETTING));
    if (!pDlgInfo)
    {
      CLog::Log(LOGERROR, "CPVRGUIActions - %s - unable to get WINDOW_DIALOG_PVR_TIMER_SETTING!", __FUNCTION__);
      return false;
    }

    pDlgInfo->SetTimer(timer);
    pDlgInfo->Open();

    return pDlgInfo->IsConfirmed();
  }