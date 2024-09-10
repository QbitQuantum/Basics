asmlinkage int pthread_create_sys (pthread_t *thread, 
				   const pthread_attr_t *attr,
                                   void *(*startup)(void *),
				   void *(*start_routine)(void *), 
				   void *args) {
  int flags;

  hw_save_flags_and_cli (flags);


  // Check policy & prio
  if (attr) {
    if (attr->policy != SCHED_FIFO) {
      SET_ERRNO(EINVAL);
      return -1;
    } else {

      if (attr -> sched_param.sched_priority > MIN_SCHED_PRIORITY ||
	  attr -> sched_param.sched_priority < MAX_SCHED_PRIORITY) {
	SET_ERRNO(EINVAL);
	return -1;
      }
    }
  }

  // Creating the pthread structure
  if (!(*thread = create_pthread_struct ())) {
    SET_ERRNO (EAGAIN);
    hw_restore_flags (flags);
    return -1;
  }
  
  /* 
   * Configuring the new thread either with attr (if not NULL)
   * or with the default values
   */
  if (attr) {
    (*thread) -> sched_param = attr -> sched_param;    
    (*thread) -> stack_info.stack_size = attr -> stack_size;
    (*thread) -> stack_info.stack_bottom = attr -> stack_addr;
    SET_THREAD_DETACH_STATE((*thread), attr -> detachstate);
    SET_THREAD_POLICY ((*thread), attr -> policy);
  } else {
    (*thread) -> sched_param.sched_priority = MIN_SCHED_PRIORITY;
    (*thread) -> stack_info.stack_size = STACK_SIZE;
    (*thread) -> stack_info.stack_bottom = 0;
    SET_THREAD_DETACH_STATE((*thread), 0);
    SET_THREAD_POLICY ((*thread), SCHED_FIFO);
  }

  if (!((*thread) -> stack_info.stack_bottom)) {
    // Creating the thread stack
    if (alloc_stack (&(*thread) -> stack_info) < 0) {
      SET_ERRNO (EAGAIN);
      hw_restore_flags (flags);
      return -1;
    }
  }

  // This is arhictecture dependent
  (*thread) -> stack = setup_stack ((*thread)->stack_info.stack_bottom +
				    (*thread)->stack_info.stack_size 
				    / sizeof (int),
                                    startup,
                                    start_routine, args);

  activate_thread (*thread);
  pthread_t tmp = *thread;
  printf("pthred_create_sys thread 0x%x state:%d\n", (unsigned long)tmp, GET_THREAD_STATE(tmp));

  // no error at all
  hw_restore_flags (flags);

  // Calling the scheduler
  scheduling ();
  return 0;
}