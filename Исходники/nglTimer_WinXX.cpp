void nglTimer::FreeMainTimer()
{
  if (mTimers.empty())
  {
    DeleteTimerQueueTimer(mTimerQueueHandle, mTimerHandle, NULL);
//    DeleteTimerQueueEx(mTimerQueueHandle, NULL);
    while (working)
    {
      MSG msg;
      HWND hwnd = App->GetHWnd();

      PeekMessage(&msg, hwnd, WM_NGLTIMER, WM_NGLTIMER, PM_REMOVE);
      Sleep(2);
    }
   DeleteTimerQueueEx(mTimerQueueHandle, INVALID_HANDLE_VALUE);
    mTimerHandle = NULL;
    mTimerQueueHandle = NULL;
  }
}