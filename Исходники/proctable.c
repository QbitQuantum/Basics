void proctable_exit_process(struct proc *proc_exited, int exitcode) {
  // DEBUG(DB_EXEC, "Exiting PID: %d from proctable\n", getPID(proc_exited));

  KASSERT(proc_exited != NULL);
  KASSERT(proc_exited->p_pid > 0);

  // set the process state to exited
  setState(proc_exited, PROC_EXITED);

  // encode the exit code as per the docs.
  setExitcode(proc_exited, _MKWAIT_EXIT(exitcode));

  // Next we need to evaluate some cases:
  // If proc_exited has living children, they should now have a NULL parent.
  // If proc_exited has dead children, they should now be destroyed.

  int exitedPID = getPID(proc_exited);

  // Find the children of proc_exited.
  for (int i = MIN_PID; i < pidLimit; i++) {
    struct proc* cur = procarray_get(procTable, i);
    if (cur != NULL && getPPID(cur) == exitedPID) {
      // Check state of child
      int state = getState(cur);
      
      // A running child has its parent set to NULL
      if (state == PROC_RUNNING) {
        setPPID(cur, PROC_NO_PID);
      }

      // An exited child can now be completely removed.
      else if (state == PROC_EXITED) {
        proctable_remove_process(cur);
      }
    }
  }

  // If proc_exited has no parent, it can be removed
  if (getPPID(proc_exited) == PROC_NO_PID) {
    proctable_remove_process(proc_exited);
  }

  // Otherwise if proc_exited has a parent
  // then proc_exited must wake its potentially waiting parent
  else {
    cv_signal(proc_exited->wait_cv, procTableLock);
  }
}