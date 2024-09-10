bool
InstanceAvailabilityStatusChangedEvent::addInstance(
        const CommonAPI::Address &_address,
        const instance_id_t &_instanceId) {
    std::lock_guard<std::mutex> lock(instancesMutex_);
    if (instancesForward_.find(_instanceId) == instancesForward_.end()) {
        instancesForward_[_instanceId] = _address.getInstance();
        instancesBackward_[_address.getInstance()] = _instanceId;
        return true;
    }
    return false;
}