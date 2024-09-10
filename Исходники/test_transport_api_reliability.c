static size_t
notify_ready (void *cls, size_t size, void *buf)
{
  static int n;
  char *cbuf = buf;
  struct TestMessage hdr;
  unsigned int s;
  unsigned int ret;

  th = NULL;

  if (buf == NULL)
  {
    test_send_timeout = GNUNET_YES;
    GNUNET_log (GNUNET_ERROR_TYPE_ERROR,
                "Timeout occurred while waiting for transmit_ready for msg %u of %u\n",
                msg_scheduled, TOTAL_MSGS);
    if (NULL != die_task)
      GNUNET_SCHEDULER_cancel (die_task);
    die_task = GNUNET_SCHEDULER_add_now (&end_badly, NULL);
    ok = 42;
    return 0;
  }
  ret = 0;
  s = get_size (n);
  GNUNET_assert (size >= s);
  GNUNET_assert (buf != NULL);
  GNUNET_assert (n < TOTAL_MSGS);
  cbuf = buf;
  do
  {
    GNUNET_assert (n < TOTAL_MSGS);
    hdr.header.size = htons (s);
    hdr.header.type = htons (MTYPE);
    hdr.num = htonl (n);
    msg_sent = n;
    memcpy (&cbuf[ret], &hdr, sizeof (struct TestMessage));
    ret += sizeof (struct TestMessage);
    memset (&cbuf[ret], n, s - sizeof (struct TestMessage));
    ret += s - sizeof (struct TestMessage);

#if VERBOSE
    if (n % 5000 == 0)
    {
      GNUNET_log (GNUNET_ERROR_TYPE_DEBUG,
                  "Sending message %u of size %u\n",
                  n,
                  s);
    }
#endif
    n++;
    s = get_size (n);
    if (0 == GNUNET_CRYPTO_random_u32 (GNUNET_CRYPTO_QUALITY_WEAK, 16))
      break;                    /* sometimes pack buffer full, sometimes not */
  }
  while ((size - ret >= s) && (n < TOTAL_MSGS));
  if (n < TOTAL_MSGS)
  {
    th = GNUNET_TRANSPORT_notify_transmit_ready (p2->th, &p1->id, s,
                                                 TIMEOUT_TRANSMIT,
                                                 &notify_ready, NULL);
    msg_scheduled = n;
  }
  else
  {
    FPRINTF (stderr, "%s",  "\n");
    GNUNET_log (GNUNET_ERROR_TYPE_DEBUG,
                "All messages scheduled to be sent\n");
    if (NULL != die_task)
      GNUNET_SCHEDULER_cancel (die_task);
    die_task = GNUNET_SCHEDULER_add_delayed (TIMEOUT, &end_badly, NULL);
  }
  if (n % 5000 == 0)
  {
    GNUNET_log (GNUNET_ERROR_TYPE_DEBUG,
                "Returning total message block of size %u\n", ret);
  }
  total_bytes += ret;
  return ret;
}