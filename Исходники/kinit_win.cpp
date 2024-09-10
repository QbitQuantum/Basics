 ~ProcessListEntry()
 {
     freeSid(owner);
     CloseHandle(handle);
 }