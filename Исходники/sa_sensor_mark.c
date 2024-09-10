EXTERN_C gboolean sa_Sensor_mark_start(sa_Sensor_mark* self, GError** error)
{
  if (!sa_Sensor_mark_is_active(self)) {
    //logt("START MARK");
    if (!log_db_log_mark(self->log, "start", error)) // begin mark
      return FALSE;

    if (!setTimer(self, error))
      return FALSE;
  }
  return TRUE;
}