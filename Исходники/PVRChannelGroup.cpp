void CPVRChannelGroup::SearchAndSetChannelIcons(bool bUpdateDb /* = false */)
{
  if (g_guiSettings.GetString("pvrmenu.iconpath").IsEmpty())
    return;

  CPVRDatabase *database = GetPVRDatabase();
  if (!database)
    return;

  CSingleLock lock(m_critSection);

  for (unsigned int ptr = 0; ptr < size(); ptr++)
  {
    PVRChannelGroupMember groupMember = at(ptr);

    /* skip if an icon is already set */
    if (!groupMember.channel->IconPath().IsEmpty())
      continue;

    CStdString strBasePath = g_guiSettings.GetString("pvrmenu.iconpath");
    CStdString strChannelName = groupMember.channel->ClientChannelName();

    CStdString strIconPath = strBasePath + groupMember.channel->ClientChannelName();
    CStdString strIconPathLower = strBasePath + strChannelName.ToLower();
    CStdString strIconPathUid;
    strIconPathUid.Format("%s/%08d", strBasePath, groupMember.channel->UniqueID());

    groupMember.channel->SetIconPath(strIconPath      + ".tbn", bUpdateDb) ||
    groupMember.channel->SetIconPath(strIconPath      + ".jpg", bUpdateDb) ||
    groupMember.channel->SetIconPath(strIconPath      + ".png", bUpdateDb) ||

    groupMember.channel->SetIconPath(strIconPathLower + ".tbn", bUpdateDb) ||
    groupMember.channel->SetIconPath(strIconPathLower + ".jpg", bUpdateDb) ||
    groupMember.channel->SetIconPath(strIconPathLower + ".png", bUpdateDb) ||

    groupMember.channel->SetIconPath(strIconPathUid   + ".tbn", bUpdateDb) ||
    groupMember.channel->SetIconPath(strIconPathUid   + ".jpg", bUpdateDb) ||
    groupMember.channel->SetIconPath(strIconPathUid   + ".png", bUpdateDb);

    /* TODO: start channel icon scraper here if nothing was found */
  }
}