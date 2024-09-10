void set_signal_blocking(int sig, int block)
{
  SetConsoleCtrlHandler(blocking_handler, block ? TRUE : FALSE);
}