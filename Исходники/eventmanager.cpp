//----[  terminate  ]----------------------------------------------------------
void EventManager::terminate(double time, EventID event_id) {
  EventInstance* instance = getInstance(event_id);
  if (instance) {
    instance->terminate(time, special_fx_manager_);
    SAFE_DELETE(instance);
    instances_.erase(event_id);
  }
}