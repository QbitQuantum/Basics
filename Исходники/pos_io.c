FILE *open_pos_file (NV_CHAR *path)
{
  FILE                   *fp;
  NV_INT32               i;
  POS_OUTPUT_T           pos;
  time_t                 tv_sec;
  NV_INT32               tv_nsec;
  struct tm              tm;
  static NV_INT32        tz_set = 0;


  NV_INT32 big_endian ();


  /*  Check the file name for following the naming convention as best we can.  */

  if (path[strlen (path) - 16] != '_' || path[strlen (path) - 9] != '_' || path[strlen (path) - 4] != '.')
    {
      fprintf (stderr, "\n\n\nFilename %s does not conform to standard\n", path);
      fprintf (stderr, "Please correct to match _YYMMDD_NNNN.pos or _YYMMDD_NNNN.out standard.\n\n\n");
      fflush (stderr);
      return (NULL);
    }


  sscanf (&path[strlen (path) - 15], "%02d%02d%02d", &year, &month, &day);


  /*  tm struct wants years since 1900!!!  */

  tm.tm_year = year + 100;
  tm.tm_mon = month - 1;
  tm.tm_mday = day;
  tm.tm_hour = 0.0;
  tm.tm_min = 0.0;
  tm.tm_sec = 0.0;
  tm.tm_isdst = -1;

  if (!tz_set)
    {
#ifdef NVWIN3X
  #ifdef __MINGW64__
      putenv("TZ=GMT");
      tzset();
  #else
      _putenv("TZ=GMT");
      _tzset();
  #endif
#else
      putenv("TZ=GMT");
      tzset();
#endif
      tz_set = 1;
    }


  /*  Get seconds from the epoch (01-01-1970) for the date in the filename. 
      This will also give us the day of the week for the GPS seconds of
      week calculation.  */

  tv_sec = mktime (&tm);
  tv_nsec = 0.0;


  /*  Subtract the number of days since Saturday midnight (Sunday morning) in seconds.  */

  tv_sec = tv_sec - (tm.tm_wday * 86400);
  start_week = tv_sec;


  /*  We have to assume that the file is little endian since there is no
      header and no field that we can use to deduce what it is.  */

  swap = (NV_BOOL) big_endian ();


  if ((fp = fopen (path, "rb")) == NULL)
    {
      return ((FILE *) NULL);
    }
  else
    {
      fread (&pos, sizeof (POS_OUTPUT_T), 1, fp);
      if (swap) swap_pos (&pos);
      start_timestamp = (NV_INT64) (((NV_FLOAT64) start_week + pos.gps_time) * 1000000.0);
      start_record = 0;
      start_gps_time = pos.gps_time;


      i = fseek (fp, -sizeof (POS_OUTPUT_T), SEEK_END);

      fread (&pos, sizeof (POS_OUTPUT_T), 1, fp);
      if (swap) swap_pos (&pos);
      end_timestamp = (NV_INT64) (((NV_FLOAT64) start_week + pos.gps_time) * 1000000.0);


      /*  Check for crossing midnight at end of GPS week (stupid f***ing Applanix bozos).  */

      if (end_timestamp < start_timestamp)
        {
          midnight = NVTrue;
          end_timestamp += ((NV_INT64) WEEK_OFFSET * 1000000);
        }


      end_record = ftell (fp) / sizeof (POS_OUTPUT_T);

      fseek (fp, 0, SEEK_SET);
    }

  return (fp);
}