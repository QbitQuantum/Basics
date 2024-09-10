bool CPVRTimers::UpdateEntries(CPVRTimers *timers)
{
  bool bChanged(false);
  bool bAddedOrDeleted(false);

  CSingleLock lock(m_critSection);

  /* go through the timer list and check for updated or new timers */
  for (unsigned int iTimerPtr = 0; iTimerPtr < timers->size(); iTimerPtr++)
  {
    const CPVRTimerInfoTag *timer = timers->at(iTimerPtr);

    /* check if this timer is present in this container */
    CPVRTimerInfoTag *existingTimer = (CPVRTimerInfoTag *) GetByClient(timer->m_iClientId, timer->m_iClientIndex);
    if (existingTimer)
    {
      /* if it's present, update the current tag */
      bool bStateChanged(existingTimer->m_state != timer->m_state);
      if (existingTimer->UpdateEntry(*timer))
      {
        bChanged = true;

        if (bStateChanged && g_PVRManager.IsStarted())
          existingTimer->QueueNotification();

        CLog::Log(LOGINFO,"PVRTimers - %s - updated timer %d on client %d",
            __FUNCTION__, timer->m_iClientIndex, timer->m_iClientId);
      }
    }
    else
    {
      /* new timer */
      CPVRTimerInfoTag *newTimer = new CPVRTimerInfoTag;
      newTimer->UpdateEntry(*timer);
      push_back(newTimer);
      bChanged = true;
      bAddedOrDeleted = true;

      if (g_PVRManager.IsStarted())
        newTimer->QueueNotification();

      CLog::Log(LOGINFO,"PVRTimers - %s - added timer %d on client %d",
          __FUNCTION__, timer->m_iClientIndex, timer->m_iClientId);
    }
  }

  /* check for deleted timers */
  unsigned int iSize = size();
  for (unsigned int iTimerPtr = 0; iTimerPtr < iSize; iTimerPtr++)
  {
    CPVRTimerInfoTag *timer = (CPVRTimerInfoTag *) at(iTimerPtr);
    if (!timer)
      continue;
    if (timers->GetByClient(timer->m_iClientId, timer->m_iClientIndex) == NULL)
    {
      /* timer was not found */
      CLog::Log(LOGINFO,"PVRTimers - %s - deleted timer %d on client %d",
          __FUNCTION__, timer->m_iClientIndex, timer->m_iClientId);

      if (g_PVRManager.IsStarted() && g_guiSettings.GetBool("pvrrecord.timernotifications"))
      {
        CStdString strMessage;
        strMessage.Format("%s: '%s'", g_localizeStrings.Get(19228), timer->m_strTitle.c_str());
        g_application.m_guiDialogKaiToast.QueueNotification(CGUIDialogKaiToast::Info, g_localizeStrings.Get(19166), strMessage);
      }

      CPVREpgInfoTag *epgTag = (CPVREpgInfoTag *) at(iTimerPtr)->m_epgInfo;
      if (epgTag)
        epgTag->SetTimer(NULL);

      delete at(iTimerPtr);
      erase(begin() + iTimerPtr);
      iTimerPtr--;
      iSize--;
      bChanged = true;
      bAddedOrDeleted = true;
    }
  }

  m_bIsUpdating = false;
  if (bChanged)
  {
    Sort();
    SetChanged();
    lock.Leave();

    NotifyObservers(bAddedOrDeleted ? "timers-reset" : "timers", false);
  }

  return bChanged;
}