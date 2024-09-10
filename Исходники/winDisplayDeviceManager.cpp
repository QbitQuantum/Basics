  void winDisplayDeviceManager::scanDisplays()
  {
    // TODO mutex for this variable ???
    descMap.clear();
    EnumDisplayMonitors(0,0,winDisplayDeviceManager::EnumDispProc,(LPARAM)this);

    // Add new descriptors
    set<DisplayDeviceDescriptor> tempSet, resultSet;
    for (descMap_t::iterator it = descMap.begin(); it != descMap.end(); it++)
    {
      addDevice(it->second);
      tempSet.insert(it->second);
    }

    // We could just copy the new descriptors, however, we need to call callback functions
    // for old displays, that's why we do this:
    std::set_difference(descriptors.begin(), descriptors.end(), tempSet.begin(), tempSet.end(),
                        std::inserter(resultSet, resultSet.end()));

    set<DisplayDeviceDescriptor>::iterator it = resultSet.begin();
    for (; it != resultSet.end(); it++)
    {
      DisplayDeviceDescriptor desc = *it;
      removeDevice(desc);
    }
  }