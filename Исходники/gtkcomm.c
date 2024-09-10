static gint timer_trigger(gpointer data)
{
  unsigned long now = GPOINTER_TO_LONG(data);
  unsigned long next, then;
  long ticks;

  /*
   * Destroy the timer we got here on.
   */
  if (timer_id) {
    g_source_remove(timer_id);
    timer_id = 0;
  }

  /*
   * run_timers() may cause a call to timer_change_notify, in which
   * case a new timer will already have been set up and left in
   * timer_id. If it hasn't, and run_timers reports that some timing
   * still needs to be done, we do it ourselves.
   */
  if (run_timers(now, &next) && !timer_id) {
    then = now;
    now = GETTICKCOUNT();
    if (now - then > next - then)
      ticks = 0;
    else
      ticks = next - now;
    timer_id = g_timeout_add(ticks, timer_trigger, LONG_TO_GPOINTER(next));
  }

  /*
   * Returning FALSE means 'don't call this timer again', which
   * _should_ be redundant given that we removed it above, but just
   * in case, return FALSE anyway.
   */
  return FALSE;
}