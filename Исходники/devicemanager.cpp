DeviceManager::~DeviceManager()
{
    if (initialized())
        uninitialize();
    if (_watcher)
        delete _watcher;
}