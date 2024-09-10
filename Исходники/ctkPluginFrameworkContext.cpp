void ctkPluginFrameworkContext::init()
{
  log() << "initializing";

  if (firstInit && ctkPluginConstants::FRAMEWORK_STORAGE_CLEAN_ONFIRSTINIT
      == props[ctkPluginConstants::FRAMEWORK_STORAGE_CLEAN])
  {
    deleteFWDir();
    firstInit = false;
  }

  ctkPluginFrameworkPrivate* const systemPluginPrivate = systemPlugin->d_func();
  systemPluginPrivate->initSystemPlugin();

  storage = new ctkPluginStorage(this);
  dataStorage = ctkPluginFrameworkUtil::getFileStorage(this, "data");
  services = new ctkServices(this);
  plugins = new ctkPlugins(this);

  plugins->load();

  log() << "inited";
  initialized = true;

  log() << "Installed plugins:";
  // Use the ordering in the plugin storage to get a sorted list of plugins.
  QList<ctkPluginArchive*> allPAs = storage->getAllPluginArchives();
  for (int i = 0; i < allPAs.size(); ++i)
  {
    ctkPluginArchive* pa = allPAs[i];
    QSharedPointer<ctkPlugin> plugin = plugins->getPlugin(pa->getPluginLocation().toString());
    log() << " #" << plugin->getPluginId() << " " << plugin->getSymbolicName() << ":"
        << plugin->getVersion() << " location:" << plugin->getLocation();
  }
}