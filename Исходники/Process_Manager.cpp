pid_t
ACE_Process_Manager::wait (pid_t pid,
                           const ACE_Time_Value &timeout,
                           ACE_exitcode *status)
{
  ACE_TRACE ("ACE_Process_Manager::wait");

  ACE_exitcode local_stat = 0;
  if (status == 0)
    status = &local_stat;

  *status = 0;

  ssize_t idx = -1;
  ACE_Process *proc = 0;

  {
    // fake context after which the lock is released
    ACE_MT (ACE_GUARD_RETURN (ACE_Recursive_Thread_Mutex, ace_mon, this->lock_, -1));

    if (pid != 0)
      {
        idx = this->find_proc (pid);
        if (idx == -1)
          return ACE_INVALID_PID;
        else
          proc = process_table_[idx].process_;
      }
    // release the lock.
  }
  if (proc != 0)
    pid = proc->wait (timeout, status);
  else
    {
      ACE_MT (ACE_GUARD_RETURN (ACE_Recursive_Thread_Mutex, ace_mon, this->lock_, -1));
      // Wait for any Process spawned by this Process_Manager.
#if defined (ACE_WIN32)
      HANDLE *handles = 0;

      ACE_NEW_RETURN (handles,
                      HANDLE[this->current_count_],
                      ACE_INVALID_PID);

      for (size_t i = 0;
           i < this->current_count_;
           ++i)
        handles[i] =
          process_table_[i].process_->gethandle ();

      DWORD handle_count = static_cast<DWORD> (this->current_count_);
      DWORD result = ::WaitForMultipleObjects (handle_count,
                                               handles,
                                               FALSE,
                                               timeout == ACE_Time_Value::max_time
                                               ? INFINITE
                                               : timeout.msec ());
      if (result == WAIT_FAILED)
        pid = ACE_INVALID_PID;
      else if (result == WAIT_TIMEOUT)
        pid = 0;
      else
        {
          // Green Hills produces a warning that result >=
          // WAIT_OBJECT_0 is a pointless comparison because
          // WAIT_OBJECT_0 is zero and DWORD is unsigned long, so this
          // test is skipped for Green Hills.  Same for mingw.
# if defined (ghs) || defined (__MINGW32__) || defined (_MSC_VER)
          ACE_ASSERT (result < WAIT_OBJECT_0 + this->current_count_);
# else
          ACE_ASSERT (result >= WAIT_OBJECT_0
                      && result < WAIT_OBJECT_0 + this->current_count_);
# endif

          idx = this->find_proc (handles[result - WAIT_OBJECT_0]);

          if (idx != -1)
            {
              pid = process_table_[idx].process_->getpid ();
              result = ::GetExitCodeProcess (handles[result - WAIT_OBJECT_0],
                                             status);
              if (result == 0)
                {
                  // <GetExitCodeProcess> failed!
                  this->remove_proc (idx);
                  pid = ACE_INVALID_PID;
                }
            }
          else
            {
              // uh oh...handle removed from process_table_, even though
              // we're holding a lock!
              delete [] handles;
              ACE_ERROR_RETURN ((LM_ERROR,
                                 ACE_TEXT ("Process removed")
                                 ACE_TEXT (" -- somebody's ignoring the lock!\n")),
                                -1);
            }
        }

      delete [] handles;
#else /* !defined(ACE_WIN32) */
      if (timeout == ACE_Time_Value::max_time)
        pid = ACE_OS::waitpid (-1, status, 0);
      else if (timeout == ACE_Time_Value::zero)
        pid = ACE_OS::waitpid (-1, status, WNOHANG);
      else
        {
# if defined (ACE_LACKS_UNIX_SIGNALS)
          pid = 0;
          ACE_Time_Value sleeptm (1);    // 1 msec
          if (sleeptm > timeout)         // if sleeptime > waittime
            sleeptm = timeout;
          ACE_Time_Value tmo (timeout);  // Need one we can change
          for (ACE_Countdown_Time time_left (&tmo); tmo > ACE_Time_Value::zero ; time_left.update ())
            {
              pid = ACE_OS::waitpid (-1, status, WNOHANG);
              if (pid > 0 || pid == ACE_INVALID_PID)
                break;          // Got a child or an error - all done

              // pid 0, nothing is ready yet, so wait.
              // Do a (very) short sleep (only this thread sleeps).
              ACE_OS::sleep (sleeptm);
            }
# else
          // Force generation of SIGCHLD, even though we don't want to
          // catch it - just need it to interrupt the sleep below.
          // If this object has a reactor set, assume it was given at
          // open(), and there's already a SIGCHLD action set, so no
          // action is needed here.
          ACE_Sig_Action old_action;
          if (this->reactor () == 0)
            {
              ACE_Sig_Action do_sigchld ((ACE_SignalHandler)sigchld_nop);
              do_sigchld.register_action (SIGCHLD, &old_action);
            }

          ACE_Time_Value tmo (timeout);  // Need one we can change
          for (ACE_Countdown_Time time_left (&tmo); ; time_left.update ())
            {
              pid = ACE_OS::waitpid (-1, status, WNOHANG);
#   if defined (ACE_VXWORKS) && (ACE_VXWORKS >= 0x600)
              if (pid > 0 || (pid == ACE_INVALID_PID && errno != EINTR))
#   else
                if (pid > 0 || pid == ACE_INVALID_PID)
#   endif
                  break;          // Got a child or an error - all done

              // pid 0, nothing is ready yet, so wait.
              // Do a sleep (only this thread sleeps) til something
              // happens. This relies on SIGCHLD interrupting the sleep.
              // If SIGCHLD isn't delivered, we'll need to do something
              // with sigaction to force it.
              if (-1 == ACE_OS::sleep (tmo) && errno == EINTR)
                continue;
              // Timed out
              pid = 0;
              break;
            }

          // Restore the previous SIGCHLD action if it was changed.
          if (this->reactor () == 0)
            old_action.register_action (SIGCHLD);
# endif /* !ACE_LACKS_UNIX_SIGNALS */
        }
#endif /* !defined (ACE_WIN32) */
    }

  ACE_MT (ACE_GUARD_RETURN (ACE_Recursive_Thread_Mutex, ace_mon, this->lock_, -1));
  if (pid != ACE_INVALID_PID && pid != 0)
    {
      //we always need to get our id, because we could have been moved in the table meanwhile
      idx = this->find_proc (pid);
      if (idx == -1)
        {
          // oops, reaped an unmanaged process!
          ACE_DEBUG ((LM_DEBUG,
                      ACE_TEXT ("(%P|%t) oops, reaped unmanaged %d\n"),
                      pid));
          return pid;
        }
      else
        proc = process_table_[idx].process_;
      if (proc != 0)
        ACE_ASSERT (pid == proc->getpid ());

      this->notify_proc_handler (idx,
                                 *status);
      this->remove (pid);
    }

  return pid;
}