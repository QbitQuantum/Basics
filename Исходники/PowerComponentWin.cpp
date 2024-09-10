bool PowerComponentWin::Suspend()
{
  return SetSuspendState(false, true, false) == TRUE;
}