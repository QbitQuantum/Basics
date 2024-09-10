static int
init ()
{
#if LOG_BACKOFF
  killLogFileName = GNUNET_DISK_mktemp ("exponential-backoff-waiting.log");
  if (NULL == (killLogFilePtr = FOPEN (killLogFileName, "w")))
    {
      GNUNET_log_strerror_file (GNUNET_ERROR_TYPE_WARNING, "fopen",
				killLogFileName);
      GNUNET_free (killLogFileName);
      return GNUNET_SYSERR;
    }
#endif
  return GNUNET_OK;
}