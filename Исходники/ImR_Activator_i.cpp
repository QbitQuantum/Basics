ImR_Activator_i::ImR_Activator_i (void)
  : registration_token_(0)
  , debug_(0)
  , notify_imr_ (false)
  , induce_delay_ (0)
  , name_ (getHostName ())
  , env_buf_len_ (Activator_Options::ENVIRONMENT_BUFFER)
  , max_env_vars_ (Activator_Options::ENVIRONMENT_MAX_VARS)
  , detach_child_ (false)
  , active_check_pid_ (ACE_INVALID_PID)
{
}