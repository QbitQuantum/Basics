void Win32WindowManager::buildMonitorsList()
{
   // Clear the list
   mMonitors.clear();

   // Enumerate all monitors
   EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, (U32)(void*)&mMonitors);
}