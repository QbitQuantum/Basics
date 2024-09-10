bool CGUIWindowPVRBase::ShowTimerSettings(const CPVRTimerInfoTagPtr &timer)
{
  CGUIDialogPVRTimerSettings* pDlgInfo = (CGUIDialogPVRTimerSettings*)g_windowManager.GetWindow(WINDOW_DIALOG_PVR_TIMER_SETTING);

  if (!pDlgInfo)
  {
    CLog::Log(LOGERROR, "CGUIWindowPVRBase - %s - unable to get WINDOW_DIALOG_PVR_TIMER_SETTING!", __FUNCTION__);
    return false;
  }

  pDlgInfo->SetTimer(timer);
  pDlgInfo->Open();

  return pDlgInfo->IsConfirmed();
}