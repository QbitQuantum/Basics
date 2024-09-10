static void
gdk_frame_clock_idle_end_updating (GdkFrameClock *clock)
{
  GdkFrameClockIdle *clock_idle = GDK_FRAME_CLOCK_IDLE (clock);
  GdkFrameClockIdlePrivate *priv = clock_idle->priv;

  g_return_if_fail (priv->updating_count > 0);

  priv->updating_count--;
  maybe_stop_idle (clock_idle);

#ifdef G_OS_WIN32
  if (priv->updating_count == 0 && priv->begin_period)
    {
      timeEndPeriod(1);
      priv->begin_period = FALSE;
    }
#endif
}