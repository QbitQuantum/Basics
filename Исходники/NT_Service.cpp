void
ACE_NT_Service::wait_for_service_state (DWORD desired_state,
                                        ACE_Time_Value *wait_time)
{
  DWORD last_state = 0;
  DWORD last_check_point = 0;
  int first_time = 1;
  int service_ok;

  ACE_Time_Value time_out = ACE_OS::gettimeofday ();
  if (wait_time != 0)
    time_out += *wait_time;

  // Poll until the service reaches the desired state.
  for (;;)
    {
      service_ok = 0 != QueryServiceStatus (this->svc_sc_handle_,
                                            &this->svc_status_);

      // If we cannot query the service, we are done.
      if (!service_ok)
        break;

      // If the service has the desired state, we are done.
      if (desired_state == this->svc_status_.dwCurrentState)
        break;

      // If we time-out, we are done
      if (wait_time != 0 && ACE_OS::gettimeofday () > time_out )
        {
          errno = ETIME;
          break;
        }

      if (first_time)
        {
          // remember the service state, the first time we wait
          last_state       = this->svc_status_.dwCurrentState;
          last_check_point = this->svc_status_.dwCheckPoint;
          first_time = 0;
        }
      else
        {
          // update the state change.
          if (last_state != this->svc_status_.dwCurrentState)
            {
              last_state       = this->svc_status_.dwCurrentState;
              last_check_point = this->svc_status_.dwCheckPoint;
            }
          else
            {
              // The check-point should have increased
              if (this->svc_status_.dwCheckPoint > last_check_point)
                last_check_point = this->svc_status_.dwCheckPoint;
              else
                {
                  // Service control failure, we are done.
                  service_ok = 0;
                  break;
                }
            }
        }

      ::Sleep (this->svc_status_.dwWaitHint);
    }

  return;
}