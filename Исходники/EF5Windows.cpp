static void threadProc(PVOID params) {
  _putenv("TZ=UTC");
  _tzset();
  ExecuteTasks();
  addConsoleText(NORMAL, "%s", "Done!\n");
}