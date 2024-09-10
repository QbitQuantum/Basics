 //--------
 void FileWatcherWin32::update()
 {
     MsgWaitForMultipleObjectsEx(0, NULL, 0, QS_ALLINPUT, MWMO_ALERTABLE);
 }