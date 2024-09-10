 bool acquire() {
     mMutex = CreateMutexA(nullptr, FALSE, "TempleofElementalEvilMutex");
     if (GetLastError() == ERROR_ALREADY_EXISTS) {
         MessageBoxA(nullptr, "Temple of Elemental Evil is already running.", "Temple of Elemental Evil", MB_OK | MB_ICONERROR);
         return false;
     }
     return true;
 }