/* This could be interesting to expose in public API */
static void
_g_test_watcher_add_pid (GPid pid)
{
  static gsize started = 0;
  HANDLE job;

  if (g_once_init_enter (&started))
    {
      JOBOBJECT_EXTENDED_LIMIT_INFORMATION info;

      job = CreateJobObjectW (NULL, NULL);
      memset (&info, 0, sizeof (info));
      info.BasicLimitInformation.LimitFlags = 0x2000 /* JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE */;

      if (!SetInformationJobObject(job, JobObjectExtendedLimitInformation, &info, sizeof (info)))
	g_warning ("Can't enable JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE: %s", g_win32_error_message (GetLastError()));

      g_once_init_leave (&started,(gsize)job);
    }

  job = (HANDLE)started;

  if (!AssignProcessToJobObject(job, pid))
    g_warning ("Can't assign process to job: %s", g_win32_error_message (GetLastError()));
}