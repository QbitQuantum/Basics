/**
 * The destructor
 * Unload the dll if it was loaded
 */
CPluginInfo::~CPluginInfo() {
  if (m_pDll!=NULL) FreeLibrary(m_pDll);
}