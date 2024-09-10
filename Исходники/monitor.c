static int StartProcess(Process *proc) {
  pid_t pid;
  char *msg, *p;
  int i;
  size_t size;

retry:
  if ((pid = fork()) > 0) {
    proc->pid = pid;
    proc->state = STATE_RUN;

    if (getenv("MONITOR_START_PROCESS_LOGGING") != NULL) {
      size = 0;
      for (i = 0; proc->argv[i] != NULL; i++) {
        size += strlen(proc->argv[i]) + 1;
      }
      msg = malloc(size + 10);
      memset(msg, 0, size + 10);
      p = msg;
      sprintf(p, "(%d) ", pid);
      p += strlen(p);
      for (i = 0; proc->argv[i] != NULL; i++) {
        memcpy(p, proc->argv[i], strlen(proc->argv[i]));
        p += strlen(proc->argv[i]);
        memcpy(p, " ", 1);
        p += 1;
      }
      Warning(msg);
      free(msg);
    }
  } else if (pid == 0) {
    _execv(proc->argv[0], proc->argv);
  } else {
    Message("can't start process");
    goto retry;
  }
  return (pid);
}