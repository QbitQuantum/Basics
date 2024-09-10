/*
 * Terminate cleanly on interrupt.
 */
static void InteruptSignal(int signo) {
  ss.Terminate();
  (void) signo;
}