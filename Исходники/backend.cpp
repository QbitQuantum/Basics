Process::cb_ret_t Backend::handleProcessExit(ProcControlAPI::Event::const_ptr ev) {
  Process::const_ptr curProcess = ev->getProcess();
  Thread::const_ptr curThread = ev->getThread();

  Err::verbose(true, "Process %d stopped", curProcess->getPid());
  set<Event*>& events = Async::getExitSubscribers();

  Err::verbose(true, "%d events subscribed", events.size());

  set<Event*>::iterator eventIter = events.begin();
  for(;eventIter != events.end(); eventIter++) {
    Event* event = *eventIter;
    if(event) { //&& event->isEnabled(curProcess)) {
      Err::verbose(true, "Enabled");
      handleEvent(curProcess, curThread, event);
    } else {
      Err::verbose(true, "Not enabled");
    }
  }
  
  Backend::enqueueDetach(curProcess);

  return Process::cbProcStop;
}