/**
 * Parse the zoneinfo file structure (see tzfile.h) into a ZoneInfo
 */
static ZoneInfo*
zone_info_parser(unsigned char **input, gboolean is64bitData, gint *version)
{
  gint32 i = 0;
  unsigned char *buf = NULL;
  ZoneInfo *info = NULL;
  gint64 *transition_times = NULL;
  guint8 *transition_types = NULL;
  gint32 *gmt_offsets = NULL;
  gint64 isgmtcnt, isdstcnt, leapcnt, timecnt, typecnt, charcnt;
  gboolean insertInitial = FALSE;

  buf = *input;
  *input += 4;

  if (strncmp((gchar*)buf, TZ_MAGIC, 4) != 0)
    {
      msg_error("Error while processing the time zone file", 
                evt_tag_str("message", TZ_MAGIC" signature is missing"), 
                NULL);
      goto error;
    }
  
  /* read the version byte */
  buf = *input;
  *input += 1;

  /*
   * if '\0', we have just one copy of data,
   * if '2', there is additional 64 bit version at the end.
   */
  if (buf[0] != 0 && buf[0] != '2' && buf[0] != '3')
    {
      msg_error("Error in the time zone file", 
                evt_tag_str("message", "Bad Olson version info"), 
                NULL);
      goto error;
    }
  else 
    {
      if (buf[0] != 0)
        *version = buf[0] - '0';
      else
        *version = 0;
    }

  /* Read reserved bytes */
  *input += 15;

  /* Read array sizes */
  isgmtcnt = readcoded32(input, 0, G_MAXINT64);
  isdstcnt = readcoded32(input, 0, G_MAXINT64);
  leapcnt  = readcoded32(input, 0, G_MAXINT64);
  timecnt  = readcoded32(input, 0, G_MAXINT64);
  typecnt  = readcoded32(input, 0, G_MAXINT64);
  charcnt  = readcoded32(input, 0, G_MAXINT64);

  /* 
   * Confirm sizes that we assume to be equal.  These assumptions
   * are drawn from a reading of the zic source (2003a), so they
   * should hold unless the zic source changes. 
   */

  if (isgmtcnt != typecnt || 
      isdstcnt != typecnt) 
    {
      msg_warning("Error in the time zone file", 
                   evt_tag_str("message", "Count mismatch between tzh_ttisgmtcnt, tzh_ttisdstcnt, tth_typecnt"), 
                   NULL);
    }

  /* 
   * Used temporarily to store transition times and types.  We need
   * to do this because the times and types are stored in two
   * separate arrays.
   */
  transition_times = g_new0(gint64, timecnt);
  transition_types = g_new0(guint8, timecnt);
  gmt_offsets      = g_new0(gint32, typecnt);

  /* Read transition times */
  for (i = 0; i < timecnt; ++i)
    {
      if (is64bitData) 
        {
          transition_times[i] = readcoded64(input, G_MININT64, G_MAXINT64);
        }
      else
        {
          transition_times[i] = readcoded32(input, G_MININT64, G_MAXINT64);
        }
    }
  
  /* Read transition types */
  for (i = 0; i < timecnt; ++i)
    {
      guint8 t = (guint8)readchar(input);
      if (t >= typecnt)
        {
          msg_warning("Error in the time zone file", 
                      evt_tag_str("message", "Illegal type number"), 
                      evt_tag_printf("val", "%ld", (long) t), 
                      evt_tag_printf("expected", "[0, %" G_GINT64_FORMAT "]", typecnt-1), 
                      NULL);
          goto error;
        }
      transition_types[i] = t;
    }

 /* Read types (except for the isstd and isgmt flags, which come later (why??)) */
  for (i = 0; i<typecnt; ++i)
    {
      gint offs = 24;

      if (*version == 3)
        offs = 167;

      gmt_offsets[i] = readcoded32(input, G_MININT64, G_MAXINT64);
      if (gmt_offsets[i] > offs * 60 * 60 || gmt_offsets[i] < -1 * offs * 60 * 60)
        {
          msg_warning("Error in the time zone file", 
                      evt_tag_str("message", "Illegal gmtoffset number"), 
                      evt_tag_int("val", gmt_offsets[i]), 
                      evt_tag_printf("expected", "[%d, %d]", -1 * offs * 60 * 60, offs * 60 * 60), 
                      NULL);
          goto error;
        }
      /* ignore isdst flag */ 
      readbool(input);
      /* ignore abbr index */
      readchar(input);
    }

  /* allocate a new ZoneInfo structure */
  if (typecnt > 0 && timecnt == 0)
    {
      /* only one type info is in the time zone file so add it with 1901 */
      info = zone_info_new(1);
      info->transitions[0].time = LOWEST_TIME32;
      info->transitions[0].gmtoffset = gmt_offsets[0];
    }
  else
    {
      info = zone_info_new(timecnt);
    }
 
  /* Build transitions vector out of corresponding times and types. */
  insertInitial = FALSE;
  if (is64bitData)
    {
      if (timecnt > 0)
        {
          gint32 minidx = -1;
          gint32 last_transition_index = 0;
          for (i = 0; i < timecnt; ++i)
            {
              if (transition_times[i] < LOWEST_TIME32)
                {
                  if (minidx == -1 || transition_times[i] > transition_times[minidx])
                    {
                      /* Preserve the latest transition before the 32bit minimum time */
                      minidx = i;
                    }
                }
              else
                {
                  info->transitions[last_transition_index].time = transition_times[i];
                  info->transitions[last_transition_index].gmtoffset = gmt_offsets[transition_types[i]];
                  last_transition_index++;
                }
            }

          if (minidx != -1)
            {
              /* 
               * If there are any transitions before the 32bit minimum time,
               * put the type information with the 32bit minimum time
               */
              memmove(&info->transitions[1], &info->transitions[0], sizeof(Transition) * (timecnt-1));
              info->transitions[0].time = LOWEST_TIME32;
              info->transitions[0].gmtoffset = gmt_offsets[transition_types[minidx]];
              info->timecnt -= minidx;
            }
          else
            {
              /* Otherwise, we need insert the initial type later */
              insertInitial = TRUE;
            }
        }
    }
  else
    {
      for (i = 0; i < timecnt; ++i)
        {
          info->transitions[i].time = transition_times[i];        
          info->transitions[i].gmtoffset = gmt_offsets[transition_types[i]];
        }
    }

  if (insertInitial)
    {
      g_assert(timecnt > 0);
      g_assert(typecnt > 0);

      /* reallocate the transitions vector to be able to store a new entry */
      info->timecnt ++;
      timecnt ++;
      info->transitions = g_renew(Transition, info->transitions, timecnt);

      /* Add the initial type associated with the lowest int32 time */
      memmove(&info->transitions[1], &info->transitions[0], sizeof(Transition) * (timecnt-1));
      info->transitions[0].time = LOWEST_TIME32;
      info->transitions[0].gmtoffset = gmt_offsets[0];
    }

  /* ignore the abbreviation string */
  if (charcnt)
    *input += charcnt;

  /* ignore leap second info, if any */
  for (i=0; i<leapcnt; ++i)
    {
      if(is64bitData)
        readcoded64(input, G_MININT64, G_MAXINT64);/* leap second transition time */
      else
        readcoded32(input, G_MININT64, G_MAXINT64);/* leap second transition time */
      readcoded32(input, G_MININT64, G_MAXINT64);/* total correction after above */
    }

  /* http://osdir.com/ml/time.tz/2006-02/msg00041.html */
  /* We dont nead this flags to compute the wall time of the timezone*/

  /* Ignore isstd flags */
  for (i=0;i<typecnt;i++)
    readbool(input);

  /* Ignore isgmt flags */
  for (i=0;i<typecnt;i++)
    readbool(input);

error:
  g_free(transition_times);
  g_free(transition_types);
  g_free(gmt_offsets);
  *version = 0;
  return info;
}