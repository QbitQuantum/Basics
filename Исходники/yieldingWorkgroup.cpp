///////////////////////////////
// YieldingFlexibleGangWorker
///////////////////////////////
void YieldingFlexibleGangWorker::loop() {
  int previous_sequence_number = 0;
  Monitor* gang_monitor = gang()->monitor();
  MutexLockerEx ml(gang_monitor, Mutex::_no_safepoint_check_flag);
  WorkData data;
  int id;
  while (true) {
    // Check if there is work to do or if we have been asked
    // to terminate
    gang()->internal_worker_poll(&data);
    if (data.terminate()) {
      // We have been asked to terminate.
      assert(gang()->task() == NULL, "No task binding");
      // set_status(TERMINATED);
      return;
    } else if (data.task() != NULL &&
               data.sequence_number() != previous_sequence_number) {
      // There is work to be done.
      // First check if we need to become active or if there
      // are already the requisite number of workers
      if (gang()->started_workers() == yf_gang()->active_workers()) {
        // There are already enough workers, we do not need to
        // to run; fall through and wait on monitor.
      } else {
        // We need to pitch in and do the work.
        assert(gang()->started_workers() < yf_gang()->active_workers(),
               "Unexpected state");
        id = gang()->started_workers();
        gang()->internal_note_start();
        // Now, release the gang mutex and do the work.
        {
          MutexUnlockerEx mul(gang_monitor, Mutex::_no_safepoint_check_flag);
          data.task()->work(id);   // This might include yielding
        }
        // Reacquire monitor and note completion of this worker
        gang()->internal_note_finish();
        // Update status of task based on whether all workers have
        // finished or some have yielded
        assert(data.task() == gang()->task(), "Confused task binding");
        if (gang()->finished_workers() == yf_gang()->active_workers()) {
          switch (data.yf_task()->status()) {
            case ABORTING: {
              data.yf_task()->set_status(ABORTED);
              break;
            }
            case ACTIVE:
            case COMPLETING: {
              data.yf_task()->set_status(COMPLETED);
              break;
            }
            default:
              ShouldNotReachHere();
          }
          gang_monitor->notify_all();  // Notify overseer
        } else { // at least one worker is still working or yielded
          assert(gang()->finished_workers() < yf_gang()->active_workers(),
                 "Counts inconsistent");
          switch (data.yf_task()->status()) {
            case ACTIVE: {
              // first, but not only thread to complete
              data.yf_task()->set_status(COMPLETING);
              break;
            }
            case YIELDING: {
              if (gang()->finished_workers() + yf_gang()->yielded_workers()
                  == yf_gang()->active_workers()) {
                data.yf_task()->set_status(YIELDED);
                gang_monitor->notify_all();  // notify overseer
              }
              break;
            }
            case ABORTING:
            case COMPLETING: {
              break; // nothing to do
            }
            default: // everything else: INACTIVE, YIELDED, ABORTED, COMPLETED
              ShouldNotReachHere();
          }
        }
      }
    }
    // Remember the sequence number
    previous_sequence_number = data.sequence_number();
    // Wait for more work
    gang_monitor->wait(Mutex::_no_safepoint_check_flag);
  }
}