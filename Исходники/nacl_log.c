static void NaClLogOutputTag_mu(struct Gio *s) {
  char timestamp[128];
  int  pid;

  if (timestamp_enabled && tag_output) {
    pid = GETPID();
    gprintf(s, "[%d,%u:%s] ",
            pid,
            NaClThreadId(),
            NaClTimeStampString(timestamp, sizeof timestamp));
    tag_output = 0;
  }
}