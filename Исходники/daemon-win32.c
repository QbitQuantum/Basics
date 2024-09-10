bool
dtr_daemon (const dtr_callbacks  * cb,
            void                 * cb_arg,
            bool                   foreground,
            int                  * exit_code,
            tr_error            ** error)
{
  callbacks = cb;
  callback_arg = cb_arg;

  *exit_code = 1;

  if (foreground)
    {
      if (!SetConsoleCtrlHandler (&handle_console_ctrl, TRUE))
        {
          set_system_error (error, GetLastError (), "SetConsoleCtrlHandler() failed");
          return false;
        }

      *exit_code = cb->on_start (cb_arg, true);
    }
  else
    {
      const SERVICE_TABLE_ENTRY service_table[] =
        {
          { (LPWSTR) service_name, &service_main },
          { NULL, NULL }
        };

      if (!StartServiceCtrlDispatcherW (service_table))
        {
          set_system_error (error, GetLastError (), "StartServiceCtrlDispatcher() failed");
          return false;
        }

      *exit_code = 0;
    }

  return true;
}