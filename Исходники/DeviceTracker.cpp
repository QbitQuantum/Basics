DeviceTracker* DeviceTracker::getDevice(const Name& name) {
    return getDevice(getDeviceID(name));
}