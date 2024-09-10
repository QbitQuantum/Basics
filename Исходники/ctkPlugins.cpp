//----------------------------------------------------------------------------
QSharedPointer<ctkPlugin> ctkPlugins::getPlugin(const QString& name, const ctkVersion& version) const
{
  if (!fwCtx)
  { // This ctkPlugins instance has been closed!
    throw std::logic_error("ctkPlugins::getPlugin(name, version) called on closed plugins object.");
  }

  {
    QReadLocker lock(&pluginsLock);

    QHashIterator<QString, QSharedPointer<ctkPlugin> > it(plugins);
    while (it.hasNext())
    {
      QSharedPointer<ctkPlugin> plugin = it.next().value();
      if ((name == plugin->getSymbolicName()) && (version == plugin->getVersion()))
      {
        return plugin;
      }
    }
  }
  return QSharedPointer<ctkPlugin>(0);
}