static int NaClDebugExceptionHandlerStandaloneMain(int argc, char **argv) {
  int target_pid;
  NaClHandle socket;
  char *rest1;
  char *rest2;
  void *info;
  size_t info_size;
  HANDLE process_handle;
  DWORD written;

  if (argc != 3) {
    NaClLog(LOG_FATAL, "NaClDebugExceptionHandlerStandaloneMain: "
            "Expected 3 arguments: target_pid, socket, data\n");
  }

  target_pid = strtol(argv[0], &rest1, 0);
  socket = (NaClHandle)(uintptr_t) strtol(argv[1], &rest2, 0);
  if (*rest1 != '\0' || *rest2 != '\0') {
    NaClLog(LOG_FATAL, "NaClDebugExceptionHandlerStandaloneMain: "
            "Bad string argument\n");
  }

  info_size = strlen(argv[2]);
  if (info_size % 2 != 0) {
    NaClLog(LOG_FATAL, "NaClDebugExceptionHandlerStandaloneMain: "
            "Odd string length\n");
  }
  info_size /= 2;
  info = malloc(info_size);
  if (info == NULL) {
    NaClLog(LOG_FATAL, "NaClDebugExceptionHandlerStandaloneMain: "
            "malloc() failed\n");
  }
  DecodeHexString((uint8_t *) info, argv[2], info_size);

  if (!DebugActiveProcess(target_pid)) {
    NaClLog(LOG_FATAL, "NaClDebugExceptionHandlerStandaloneMain: "
            "Failed to attach with DebugActiveProcess()\n");
  }

  process_handle = OpenProcess(PROCESS_QUERY_INFORMATION |
                               PROCESS_SUSPEND_RESUME |
                               PROCESS_TERMINATE |
                               PROCESS_VM_OPERATION |
                               PROCESS_VM_READ |
                               PROCESS_VM_WRITE |
                               PROCESS_DUP_HANDLE |
                               SYNCHRONIZE,
                               /* bInheritHandle= */ FALSE,
                               target_pid);
  if (process_handle == NULL) {
    NaClLog(LOG_FATAL, "NaClDebugExceptionHandlerStandaloneMain: "
            "Failed to get process handle with OpenProcess()\n");
  }

  /* Send message to indicate that we attached to the process successfully. */
  if (!WriteFile(socket, "k", 1, &written, NULL) || written != 1) {
    NaClLog(LOG_FATAL, "NaClDebugExceptionHandlerStandaloneMain: "
            "Failed to send reply\n");
  }

  NaClDebugExceptionHandlerRun(process_handle, info, info_size);
  return 0;
}