bool CILSLadderInfo::Load()
{
  ConfigDir *pDir = mainApp::GetConfig();
  wxString sFile = pDir->GetILSLadderFileName();
  _Cleanup();
  m_bIsOK = LoadFile(sFile);
  if(!m_bIsOK)
  {
    m_vKits.Clear();
  }
  return m_bIsOK;
}