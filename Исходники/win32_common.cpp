void win32_monitor_init(void)
{
#ifndef _XBOX
   win32_monitor_count = 0;
   EnumDisplayMonitors(NULL, NULL, win32_monitor_enum_proc, 0);
#endif

   g_quit              = false;
}