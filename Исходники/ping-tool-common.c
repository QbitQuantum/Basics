static void
_signal_handler (int sig)
{
  int ret;

  assert (pingtool_progname);
  assert (pingtool_end_result);

  /* Must output result here, b/c who knows where in the code we are
   * when we caught the signal
   */
  ret = pingtool_end_result (pingtool_progname,
                             pingtool_dest,
                             pingtool_pkt_sent,
                             pingtool_pkt_recv);
  _cleanup ();
  exit (ret);
}