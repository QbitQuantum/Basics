DataObjectPtr EventMonitorEntry::makeDuplicate() const {
  EventMonitorEntryPtr eventMonitor = store()->createObject<EventMonitorEntry>();

  eventMonitor->setScriptCode(_script);
  eventMonitor->setEvent(_event);
  eventMonitor->setDescription(_description);
  eventMonitor->setLevel(_level);
  eventMonitor->setLogDebug(_logDebug);
  eventMonitor->setLogEMail(_logEMail);
  eventMonitor->setLogELOG(_logELOG);
  eventMonitor->setEMailRecipients(_eMailRecipients);

  if (descriptiveNameIsManual()) {
    eventMonitor->setDescriptiveName(descriptiveName());
  }
  eventMonitor->reparse();

  eventMonitor->writeLock();
  eventMonitor->registerChange();
  eventMonitor->unlock();

  return DataObjectPtr(eventMonitor);
}