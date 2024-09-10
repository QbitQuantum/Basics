void do_listen(fsmonitor_t *monitor) {
  HANDLE hChange = FindFirstChangeNotification(U2W(monitor->path), TRUE, FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME | FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_SIZE | FILE_NOTIFY_CHANGE_ATTRIBUTES);
  assert(hChange != INVALID_HANDLE_VALUE);
  printf("Listening to changes in %s\n", monitor->path);
  while (TRUE) {
    DWORD status = WaitForMultipleObjects(1, &hChange, FALSE, INFINITE);
    if (status == WAIT_OBJECT_0) {
      printf("Detected change in %s\n", monitor->path);
      invoke_on_main_thread((INVOKE_LATER_FUNC) fsmonitor_did_detect_change, monitor);
      DWORD result = FindNextChangeNotification(hChange);
      assert(result);
    } else {
      assert(!"WaitForMultipleObjects returned error");
    }
  }
}