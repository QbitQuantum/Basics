CPVRClientPtr CPVRManager::GetClient(const CFileItem &item) const
{
  int iClientID = PVR_INVALID_CLIENT_ID;

  if (item.HasPVRChannelInfoTag())
    iClientID = item.GetPVRChannelInfoTag()->ClientID();
  else if (item.HasPVRRecordingInfoTag())
    iClientID = item.GetPVRRecordingInfoTag()->m_iClientId;
  else if (item.HasPVRTimerInfoTag())
    iClientID = item.GetPVRTimerInfoTag()->m_iClientId;
  else if (item.HasEPGInfoTag())
    iClientID = item.GetEPGInfoTag()->ClientID();
  else if (URIUtils::IsPVRChannel(item.GetPath()))
  {
    const std::shared_ptr<CFileItem> channelItem = m_channelGroups->GetByPath(item.GetPath());
    if (channelItem)
      iClientID = channelItem->GetPVRChannelInfoTag()->ClientID();
  }
  else if (URIUtils::IsPVRRecording(item.GetPath()))
  {
    const std::shared_ptr<CFileItem> recordingItem = m_recordings->GetByPath(item.GetPath());
    if (recordingItem)
      iClientID = recordingItem->GetPVRRecordingInfoTag()->ClientID();
  }
  return GetClient(iClientID);
}