bool CActiveAEDSPDatabase::GetActiveDSPSettings(const CFileItem &item, CAudioSettings &settings)
{
  try
  {
    if (NULL == m_pDB.get()) return false;
    if (NULL == m_pDS.get()) return false;
    string strPath, strFileName;
    URIUtils::Split(item.GetPath(), strPath, strFileName);
    string strSQL=PrepareSQL("SELECT * FROM settings WHERE settings.strPath='%s' and settings.strFileName='%s'", strPath.c_str() , strFileName.c_str());

    m_pDS->query( strSQL.c_str() );
    if (m_pDS->num_rows() > 0)
    { // get the audio dsp settings info
      settings.m_MasterStreamTypeSel      = m_pDS->fv("MasterStreamTypeSel").get_asInt();
      int type                            = m_pDS->fv("MasterStreamType").get_asInt();
      int base                            = m_pDS->fv("MasterBaseType").get_asInt();
      settings.m_MasterStreamType         = type;
      settings.m_MasterStreamBase         = base;
      settings.m_MasterModes[type][base]  = m_pDS->fv("MasterModeId").get_asInt();

      /*! if auto mode is selected, copy the identifier of previous used processor to the auto mode entry */
      settings.m_MasterModes[settings.m_MasterStreamTypeSel][base] = settings.m_MasterModes[type][base];

      m_pDS->close();
      return true;
    }
    m_pDS->close();
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "%s failed", __FUNCTION__);
  }
  return false;
}