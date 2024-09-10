/*!
  Loads the plugin info.
  \param name The plugin name.
  \param path the plugin xml descriptor path.
 */
PluginInfo*
PluginsManager::loadInfo (Server* server, string &name, string &path)
{
  PluginInfo* pinfo = getPluginInfo (name);
  auto_ptr<PluginInfo> pinfoAutoPtr (NULL);
  if (!pinfo)
    pinfoAutoPtr.reset (pinfo = new PluginInfo (name));
  else if (pinfo->getVersion () != 0)
    return NULL;

  XmlParser xml;

  if (xml.open (path, true))
    {
      server->log (MYSERVER_LOG_MSG_ERROR,
                          _("Error loading plugin `%s'"), name.c_str ());
      return NULL;
    }

  auto_ptr<XmlXPathResult> xpathResPlugin = auto_ptr<XmlXPathResult>
    (xml.evaluateXpath ("/PLUGIN"));
  xmlNodeSetPtr nodes = xpathResPlugin->getNodeSet ();

  int size = (nodes) ? nodes->nodeNr : 0;
  if (size != 1)
    {
      server->log (MYSERVER_LOG_MSG_ERROR,
                          _("Error loading plugin `%s': invalid plugin.xml"),
                          name.c_str ());
      return NULL;
    }

  if (xmlHasProp (nodes->nodeTab[0], (const xmlChar*) "min-version"))
    {
      xmlChar *minVersion = xmlGetProp (nodes->nodeTab[0],
                                        (const xmlChar*) "min-version");

      string sMinVer ((char*) minVersion);
      pinfo->setMyServerMinVersion (PluginInfo::convertVersion (sMinVer));
    }
  else
    {
      server->log (MYSERVER_LOG_MSG_ERROR,
                          _("Error loading plugin `%s': invalid plugin.xml"),
                          name.c_str ());
      return NULL;
    }

  if (xmlHasProp (nodes->nodeTab[0], (const xmlChar*) "max-version"))
    {
      xmlChar* maxVersion = xmlGetProp (nodes->nodeTab[0],
                                        (const xmlChar*) "max-version");

      string sMaxVer ((char*)maxVersion);
      pinfo->setMyServerMaxVersion (PluginInfo::convertVersion (sMaxVer));
    }
  else
    {
      server->log (MYSERVER_LOG_MSG_ERROR,
                          _("Error loading plugin `%s': invalid plugin.xml"),
                          name.c_str ());
      return NULL;
    }

  auto_ptr<XmlXPathResult> xpathResPluginName = auto_ptr<XmlXPathResult>
    (xml.evaluateXpath ("/PLUGIN/NAME/text ()"));
  nodes = xpathResPluginName->getNodeSet ();
  size = (nodes) ? nodes->nodeNr : 0;

  if (size != 1)
    {
      server->log (MYSERVER_LOG_MSG_ERROR,
                          _("Error loading plugin `%s': invalid plugin.xml"),
                          name.c_str ());
      return NULL;
    }

  const char* cname = (const char*) nodes->nodeTab[0]->content;
  if (strcmp (name.c_str (), cname))
    return NULL;

  auto_ptr<XmlXPathResult> xpathResPluginVersion = auto_ptr<XmlXPathResult>
    (xml.evaluateXpath ("/PLUGIN/VERSION/text ()"));
  nodes = xpathResPluginVersion->getNodeSet ();
  size = (nodes) ? nodes->nodeNr : 0;

  if (size != 1)
    {
      server->log (MYSERVER_LOG_MSG_ERROR,
                          _("Error loading plugin `%s': invalid plugin.xml"),
                          name.c_str ());
      return NULL;
    }

  string verStr ((char*) nodes->nodeTab[0]->content);
  int version = PluginInfo::convertVersion (verStr);

  if (version != -1)
    pinfo->setVersion (version);
  else
    {
      server->log (MYSERVER_LOG_MSG_ERROR,
                          _("Error loading plugin `%s': invalid plugin.xml"),
                          name.c_str ());
      return NULL;
    }

  auto_ptr<XmlXPathResult> xpathResDeps = auto_ptr<XmlXPathResult>
    (xml.evaluateXpath ("/PLUGIN/DEPENDS"));
  nodes = xpathResDeps->getNodeSet ();
  size = (nodes) ? nodes->nodeNr : 0;

  for (int i = 0; i < size; i++)
    {
      const char* depends = (const char*) nodes->nodeTab[i]->children->content;

      string nameDep (depends);

      if (!xmlHasProp (nodes->nodeTab[i], (const xmlChar*) "min-version") ||
          !xmlHasProp (nodes->nodeTab[i], (const xmlChar*) "max-version"))
        {
          server->log (MYSERVER_LOG_MSG_ERROR,
                              _("Error loading plugin `%s': invalid plugin.xml"),
                              name.c_str ());
          return NULL;
        }

      string minVerStr = ((char*) xmlGetProp (nodes->nodeTab[i],
                                              (const xmlChar*) "min-version"));
      string maxVerStr = ((char*) xmlGetProp (nodes->nodeTab[i],
                                              (const xmlChar*) "max-version"));

      int minVersion = PluginInfo::convertVersion (minVerStr);
      int maxVersion = PluginInfo::convertVersion (maxVerStr);

      if (minVersion == -1 || maxVersion == -1)
        {
          server->log (MYSERVER_LOG_MSG_ERROR,
                              _("Error loading plugin `%s': invalid plugin.xml"),
                              name.c_str ());
          return NULL;
        }

      pinfo->addDependence (nameDep, minVersion, maxVersion);
    }

  pinfoAutoPtr.release ();
  return pinfo;
}