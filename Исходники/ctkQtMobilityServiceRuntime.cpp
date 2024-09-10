void ctkQtMobilityServiceRuntime::processPlugin(QSharedPointer<ctkPlugin> plugin)
{
  QHash<QString, QString> headers = plugin->getHeaders();
  QHash<QString, QString>::const_iterator it = headers.find(ctkQtMobilityServiceConstants::SERVICE_DESCRIPTOR);
  ctkLogService* log = ctkQtMobilityServiceActivator::getLogService();
  CTK_DEBUG(log)
      << "Process header " << ctkQtMobilityServiceConstants::SERVICE_DESCRIPTOR
      << " for plugin #" << plugin->getPluginId() << ": " << (it != headers.end() ? it.value() : "[missing]");

  if (it != headers.end())
  {
    QString sd = it.value();
    if (sd.isEmpty())
    {
      QString msg = QString("Header ") + ctkQtMobilityServiceConstants::SERVICE_DESCRIPTOR + " empty.";
      ctkQtMobilityServiceActivator::logError(plugin->getPluginContext(), msg);
      return;
    }

    QByteArray serviceDescription = plugin->getResource(sd);
    QBuffer serviceBuffer(&serviceDescription);
    qServiceManager.addService(&serviceBuffer);
    QServiceManager::Error error = qServiceManager.error();
    if (!(error == QServiceManager::NoError || error == QServiceManager::ServiceAlreadyExists))
    {
      QString msg = QString("Registering the QtMobility service descriptor failed: ") +
          getQServiceManagerErrorString(error);
      ctkQtMobilityServiceActivator::logError(plugin->getPluginContext(), msg);
      return;
    }

    QString serviceName = plugin->getSymbolicName() + "_" + plugin->getVersion().toString();
    QList<QServiceInterfaceDescriptor> descriptors = qServiceManager.findInterfaces(serviceName);

    if (descriptors.isEmpty())
    {
      QString msg = QString("No interfaces found for service name ") + serviceName;
      ctkQtMobilityServiceActivator::logWarning(plugin->getPluginContext(), msg);
      return;
    }

    QListIterator<QServiceInterfaceDescriptor> it(descriptors);
    while (it.hasNext())
    {
      QServiceInterfaceDescriptor descr = it.next();
      CTK_DEBUG(ctkQtMobilityServiceActivator::getLogService()) << "Registering:" << descr.interfaceName();
      QStringList classes;
      ctkDictionary props;

      QStringList customKeys = descr.customAttributes();
      QStringListIterator keyIt(customKeys);
      bool classAttrFound = false;
      while (keyIt.hasNext())
      {
        QString key = keyIt.next();
        if (key == ctkPluginConstants::OBJECTCLASS)
        {
          classAttrFound = true;
          classes << descr.customAttribute(key);
        }
        else
        {
          props.insert(key, descr.customAttribute(key));
        }
      }

      if (!classAttrFound)
      {
        QString msg = QString("The custom attribute \"") + ctkPluginConstants::OBJECTCLASS
            + "\" is missing in the interface description of \"" + descr.interfaceName();
        ctkQtMobilityServiceActivator::logError(plugin->getPluginContext(), msg);
        continue;
      }

      ctkQtMobilityServiceFactory* serviceObject = new ctkQtMobilityServiceFactory(descr, this, plugin);
      ctkServiceRegistration serviceReg = plugin->getPluginContext()->registerService(classes, serviceObject, props);

      if (serviceReg)
      {
        mapPluginToServiceFactory.insert(plugin, serviceObject);
        mapPluginToServiceRegistration.insert(plugin, serviceReg);
      }
      else
      {
        QString msg = QString("Could not register QtMobility service ") + descr.serviceName() + " "
            + descr.interfaceName();
        ctkQtMobilityServiceActivator::logError(plugin->getPluginContext(), msg);
        continue;
      }
    }
  }
}