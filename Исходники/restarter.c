static void log_event(unsigned int event_id, const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  if (event_log != NULL) {
    char message[MESSAGE_SIZE];
    int n = vsnprintf_s(message, MESSAGE_SIZE, _TRUNCATE, format, ap);
    if (n > 0) {
      int severity = event_id >> 30;
      WORD type = (WORD)(severity == 3 ? EVENTLOG_ERROR_TYPE : severity == 2 ? EVENTLOG_WARNING_TYPE : EVENTLOG_INFORMATION_TYPE);
      ReportEventW(event_log, type, 0, event_id, NULL, 0, (DWORD)n, NULL, message);
    }