bool Probe::processRequests() {
  if(requestQueue.empty()) {
    return true;
  }

  pthread_mutex_lock(&requestQueueMutex); 
  vector<ProbeRequest*> queue = requestQueue;
  requestQueue.clear();
  pthread_mutex_unlock(&requestQueueMutex); 

  ProcessSet::ptr continueSet = ProcessSet::newProcessSet();
 
  // Sort queue

  deque<ProbeRequest*> sortedQueue;
  vector<ProbeRequest*>::iterator requestIter = queue.begin();
  for(int i = 0; requestIter != queue.end(); requestIter++) {
    ProbeRequest* request = *requestIter;

    if(!request) {
      DYSECTWARN(true, "Invalid request in request queue");
      break;
    }

    if(request->type == DisableType) {
      sortedQueue.push_back(request);
    } else {
      sortedQueue.push_front(request);
    }
  }

  if (sortedQueue.size() == 0)
    return true;

  DYSECTVERBOSE(true, "Handling %d process requests", sortedQueue.size());

  deque<ProbeRequest*>::iterator sortedRequestIter = sortedQueue.begin();
  for(int i = 0; sortedRequestIter != sortedQueue.end(); sortedRequestIter++) {
    ProbeRequest* request = *sortedRequestIter;

    if(!request) {
      DYSECTWARN(true, "Invalid request in request queue");
      break;
    }

    DYSECTVERBOSE(true, "processRequests() %d", i++);

    Probe* probe = request->probe;
    if(!probe) {
      DYSECTWARN(false, "Probe not found for disable request!");
      break;
    }

    ProcessSet::ptr waitingProcs = request->scope;
    if(waitingProcs && waitingProcs->size() > 0) {
      DYSECTVERBOSE(true, "Adding %d request processes to %d continue set...", waitingProcs->size(), continueSet->size());
      continueSet = continueSet->set_union(waitingProcs);
    }

    ProcessSet::ptr operationSet = ProcessSet::newProcessSet();
    ProcessSet::ptr stopSet = ProcessSet::newProcessSet();

    ProcessSet::ptr scope = request->scope;
    if(scope && scope->size() > 0) {
      DYSECTVERBOSE(true, "Adding processes from scope set (%d) to affected procs (%d)", scope->size(), operationSet->size());
      operationSet = operationSet->set_union(scope);
    }

    //
    // Filter out detached
    //
    operationSet = ProcessMgr::filterDetached(operationSet);
    stopSet = ProcessMgr::filterDetached(stopSet);
    DYSECTVERBOSE(true, "%d procs in op set, %d procs in stop set", operationSet->size(), stopSet->size());

    //
    // Stop processes
    //
  
    stopSet = operationSet->getAnyThreadRunningSubset();
    if(stopSet && stopSet->size() > 0) {
      DYSECTVERBOSE(true, "Stopping %d processes", stopSet->size());
      
      stopSet->stopProcs();
    }

    //
    // Carry out operations
    //

    if(operationSet && operationSet->size() > 0) {
      if(request->type == DisableType) {
        DYSECTVERBOSE(true, "Disabling %d processes", operationSet->size());
        probe->disable(operationSet);
      } else {
        DYSECTVERBOSE(true, "Enabling %d processes", operationSet->size());
        probe->enableChildren(operationSet);
      }
    }
    
    //
    // Processes must be started when all operations have been carried out.
    //
    if(operationSet && operationSet->size() > 0) {
      continueSet = continueSet->set_union(operationSet);
    }

    delete(request);
  }

  continueSet = ProcessMgr::filterDetached(continueSet);

  if(continueSet && continueSet->size() > 0) {
    DYSECTVERBOSE(true, "Continuing %d processes", continueSet->size());
    if(continueSet->size() == 1) {
      ProcessSet::iterator procIter = continueSet->begin();
      Process::ptr process = *procIter;
      DYSECTVERBOSE(true, "Continuing process %d", process->getPid());
    }
    
    continueSet->continueProcs();
  }

  DYSECTVERBOSE(true, "Done handling requests");

  return true;
}