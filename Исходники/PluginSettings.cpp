bool CPluginSettings::Load(const CURL& url)
{
  m_url = url;  

  // create the users filepath
  m_userFileName.Format("P:\\plugin_data\\%s\\%s", url.GetHostName().c_str(), url.GetFileName().c_str());
  CUtil::RemoveSlashAtEnd(m_userFileName);
  CUtil::AddFileToFolder(m_userFileName, "settings.xml", m_userFileName);
  
  // Create our final path
  CStdString pluginFileName = "Q:\\plugins\\";

  CUtil::AddFileToFolder(pluginFileName, url.GetHostName(), pluginFileName);
  CUtil::AddFileToFolder(pluginFileName, url.GetFileName(), pluginFileName);

  // Replace the / at end, GetFileName() leaves a / at the end
  pluginFileName.Replace("/", "\\");

  CUtil::AddFileToFolder(pluginFileName, "resources", pluginFileName);
  CUtil::AddFileToFolder(pluginFileName, "settings.xml", pluginFileName);

  pluginFileName = _P(pluginFileName);
  m_userFileName = _P(m_userFileName);

  if (!m_pluginXmlDoc.LoadFile(pluginFileName.c_str()))
  {
    CLog::Log(LOGERROR, "Unable to load: %s, Line %d\n%s", pluginFileName.c_str(), m_pluginXmlDoc.ErrorRow(), m_pluginXmlDoc.ErrorDesc());
    return false;
  }
  
  // Make sure that the plugin XML has the settings element
  TiXmlElement *setting = m_pluginXmlDoc.RootElement();
  if (!setting || strcmpi(setting->Value(), "settings") != 0)
  {
    CLog::Log(LOGERROR, "Error loading Settings %s: cannot find root element 'settings'", pluginFileName.c_str());
    return false;
  }  
  
  // Load the user saved settings. If it does not exist, create it
  if (!m_userXmlDoc.LoadFile(m_userFileName.c_str()))
  {
    TiXmlDocument doc;
    TiXmlDeclaration decl("1.0", "UTF-8", "yes");
    doc.InsertEndChild(decl);
    
    TiXmlElement xmlRootElement("settings");
    doc.InsertEndChild(xmlRootElement);
    
    m_userXmlDoc = doc;
    
    // Don't worry about the actual settings, they will be set when the user clicks "Ok"
    // in the settings dialog
  }

  return true;
}