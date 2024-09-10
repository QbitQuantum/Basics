void CPVRTimerInfoTag::UpdateEpgEvent(bool bClear /* = false */)
{
  CSingleLock lock(m_critSection);
  if (bClear)
  {
    CEpgInfoTag *epgTag = GetEpgInfoTag();
    if (epgTag)
      epgTag->OnTimerDeleted();
  }
  else
  {
    /* already got an epg event set */
    if (m_iEpgId != -1)
      return;

    /* try to get the channel */
    CPVRChannel *channel = (CPVRChannel *) g_PVRChannelGroups->GetByUniqueID(m_iClientChannelUid, m_iClientId);
    if (!channel)
      return;

    /* try to get the EPG table */
    CEpg *epg = channel->GetEPG();
    if (!epg)
      return;

    /* try to set the timer on the epg tag that matches with a 2 minute margin */
    CEpgInfoTag *epgTag = (CEpgInfoTag *) epg->GetTagBetween(StartAsUTC() - CDateTimeSpan(0, 0, 2, 0), EndAsUTC() + CDateTimeSpan(0, 0, 2, 0));
    if (!epgTag)
      epgTag = (CEpgInfoTag *) epg->GetTagAround(StartAsUTC());

    if (epgTag)
    {
      m_iEpgId = epgTag->m_iEpgId;
      m_epgStart = epgTag->StartAsUTC();
      m_genre = epgTag->Genre();
      m_iGenreType = epgTag->GenreType();
      m_iGenreSubType = epgTag->GenreSubType();
      epgTag->SetTimer(this);
    }
  }
}