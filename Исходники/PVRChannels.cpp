int CPVRChannels::LoadFromDb(bool bCompress /* = false */)
{
  CPVRDatabase *database = g_PVRManager.GetTVDatabase();
  if (!database || !database->Open())
    return -1;

  int iChannelCount = size();

  if (database->GetChannels(*this, m_bRadio) > 0)
  {
    if (bCompress)
      database->Compress(true);

    Update();
  }

  database->Close();

  return size() - iChannelCount;
}