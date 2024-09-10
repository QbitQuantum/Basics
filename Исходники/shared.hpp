 // Raises that an error happened
 void Raise()
 {
     MessageBoxA(0, "Fatal error on ControllerBlockManager", "Plugin SDK", MB_ICONERROR);
     ExitProcess(222);
 }