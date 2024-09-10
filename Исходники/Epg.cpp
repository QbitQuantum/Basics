bool CEpg::UpdateEntries(const CEpg &epg, bool bStoreInDb /* = true */)
{
  bool bReturn(false);
  CEpgDatabase *database = g_EpgContainer.GetDatabase();

  if (epg.m_tags.size() > 0)
  {
    if (bStoreInDb)
    {
      if (!database || !database->IsOpen())
      {
        CLog::Log(LOGERROR, "%s - could not open the database", __FUNCTION__);
        return bReturn;
      }
      database->BeginTransaction();
    }

    {
      CSingleLock lock(m_critSection);
      CLog::Log(LOGDEBUG, "%s - %zu entries in memory before merging", __FUNCTION__, m_tags.size());
      /* copy over tags */
      for (map<CDateTime, CEpgInfoTagPtr>::const_iterator it = epg.m_tags.begin(); it != epg.m_tags.end(); it++)
        UpdateEntry(*it->second, bStoreInDb, false);

      CLog::Log(LOGDEBUG, "%s - %zu entries in memory after merging and before fixing", __FUNCTION__, m_tags.size());
      FixOverlappingEvents(bStoreInDb);
      CLog::Log(LOGDEBUG, "%s - %zu entries in memory after fixing", __FUNCTION__, m_tags.size());
      /* update the last scan time of this table */
      m_lastScanTime = CDateTime::GetCurrentDateTime().GetAsUTCDateTime();

      SetChanged();
    }
    /* persist changes */
    if (bStoreInDb)
    {
      bReturn = database->CommitTransaction();
      if (bReturn)
        Persist(true);
    }
    else
      bReturn = true;
  }
  else
  {
    if (bStoreInDb)
      bReturn = Persist(true);
    else
      bReturn = true;
  }

  NotifyObservers(ObservableMessageEpg);

  return bReturn;
}