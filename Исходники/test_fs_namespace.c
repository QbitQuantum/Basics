static void *
progress_cb (void *cls, const struct GNUNET_FS_ProgressInfo *event)
{
  switch (event->status)
  {
  case GNUNET_FS_STATUS_SEARCH_RESULT:
    if (sks_search == event->value.search.sc)
    {
      if (!GNUNET_FS_uri_test_equal
          (sks_expect_uri, event->value.search.specifics.result.uri))
      {
        FPRINTF (stderr, "%s",  "Wrong result for sks search!\n");
        err = 1;
      }
      /* give system 1ms to initiate update search! */
      GNUNET_SCHEDULER_add_delayed (GNUNET_TIME_UNIT_MILLISECONDS,
                                    &abort_sks_search_task, NULL);
    }
    else if (ksk_search == event->value.search.sc)
    {
      if (!GNUNET_FS_uri_test_equal
          (ksk_expect_uri, event->value.search.specifics.result.uri))
      {
        FPRINTF (stderr, "%s",  "Wrong result for ksk search!\n");
        err = 1;
      }
      GNUNET_SCHEDULER_add_now (&abort_ksk_search_task, NULL);
    }
    else
    {
      FPRINTF (stderr, "%s",  "Unexpected search result received!\n");
      GNUNET_break (0);
    }
    break;
  case GNUNET_FS_STATUS_SEARCH_ERROR:
    FPRINTF (stderr, "Error searching file: %s\n",
             event->value.search.specifics.error.message);
    if (sks_search == event->value.search.sc)
      GNUNET_SCHEDULER_add_now (&abort_sks_search_task, NULL);
    else if (ksk_search == event->value.search.sc)
      GNUNET_SCHEDULER_add_now (&abort_ksk_search_task, NULL);
    else
      GNUNET_break (0);
    break;
  case GNUNET_FS_STATUS_SEARCH_START:
    GNUNET_assert ((NULL == event->value.search.cctx) ||
                   (0 == strcmp ("sks_search", event->value.search.cctx)) ||
                   (0 == strcmp ("ksk_search", event->value.search.cctx)));
    if (NULL == event->value.search.cctx)
    {
      GNUNET_assert (0 == strcmp ("sks_search", event->value.search.pctx));
      update_started = GNUNET_YES;
    }
    GNUNET_assert (1 == event->value.search.anonymity);
    break;
  case GNUNET_FS_STATUS_SEARCH_RESULT_STOPPED:
    return NULL;
  case GNUNET_FS_STATUS_SEARCH_STOPPED:
    return NULL;
  default:
    FPRINTF (stderr, "Unexpected event: %d\n", event->status);
    break;
  }
  return event->value.search.cctx;
}