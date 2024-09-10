void GangWorker::run() {
  this->initialize_thread_local_storage();
  assert(_gang != NULL, "No gang to run in");
  Monitor* gang_monitor = gang()->monitor();
  os::set_priority(this, MaxPriority);
  if (TraceWorkGang) {
    tty->print_cr("Running gang worker for gang %s id %d",
		  gang()->name(), id());
  }
  int previous_sequence_number = 0;
  // The VM thread should not execute here because MutexLocker's are used
  // as (opposed to MutexLockerEx's).
  assert(!Thread::current()->is_VM_thread(), "VM thread should not be part"
	 " of a work gang");
  for ( ; /* !terminate() */; ) {
    WorkData data;
    int part;  // Initialized below.
    {
      // Grab the gang mutex.
      MutexLocker ml(gang_monitor);
      // Wait for something to do.
      // Polling outside the while { wait } avoids missed notifies
      // in the outer loop.
      gang()->internal_worker_poll(&data);
      if (TraceWorkGang) {
	tty->print("Polled outside for work in gang %s worker %d",
		   gang()->name(), id());
	tty->print("  terminate: %s",
		   data.terminate() ? "true" : "false");
	tty->print("  sequence: %d (prev: %d)",
		   data.sequence_number(), previous_sequence_number);
	if (data.task() != NULL) {
	  tty->print("  task: %s", data.task()->name());
	} else {
	  tty->print("  task: NULL");
	}
	tty->cr();
      }
      for ( ; /* break or return */; ) {
	// Terminate if requested.
	if (data.terminate()) {
	  gang()->internal_note_finish();
	  gang_monitor->notify_all();
	  return;
	}
	// Check for new work.
	if ((data.task() != NULL) &&
	    (data.sequence_number() != previous_sequence_number)) {
	  gang()->internal_note_start();
	  gang_monitor->notify_all();
	  part = gang()->started_workers() - 1;
	  break;
	}
	// Nothing to do.
	gang_monitor->wait(/* no_safepoint_check */ true);
	gang()->internal_worker_poll(&data);
	if (TraceWorkGang) {
	  tty->print("Polled inside for work in gang %s worker %d",
		     gang()->name(), id());
	  tty->print("  terminate: %s",
		     data.terminate() ? "true" : "false");
	  tty->print("  sequence: %d (prev: %d)",
		     data.sequence_number(), previous_sequence_number);
	  if (data.task() != NULL) {
	    tty->print("  task: %s", data.task()->name());
	  } else {
	    tty->print("  task: NULL");
	  }
	  tty->cr();
	}
      }
      // Drop gang mutex.
    }
    if (TraceWorkGang) {
      tty->print("Work for work gang %s id %d task %s part %d",
		 gang()->name(), id(), data.task()->name(), part);
    }
    assert(data.task() != NULL, "Got null task");
    data.task()->work(part);
    {
      if (TraceWorkGang) {
	tty->print("Finish for work gang %s id %d task %s part %d",
		   gang()->name(), id(), data.task()->name(), part);
      }
      // Grab the gang mutex.
      MutexLocker ml(gang_monitor);
      gang()->internal_note_finish();
      // Tell the gang you are done.
      gang_monitor->notify_all();
      // Drop the gang mutex.
    }
    previous_sequence_number = data.sequence_number();
  }
}