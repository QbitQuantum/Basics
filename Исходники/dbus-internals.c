static inline void
_dbus_verbose_init (void)
{
  if (!verbose_initted)
    {
      const char *p = _dbus_getenv ("DBUS_VERBOSE");
      verbose = p != NULL && *p == '1';
      verbose_initted = TRUE;
#ifdef DBUS_USE_OUTPUT_DEBUG_STRING
      {
        char *last_period, *last_slash;
        GetModuleFileName(0,module_name,sizeof(module_name)-1);
        last_period = _mbsrchr(module_name,'.');
        if (last_period)
          *last_period ='\0';
        last_slash = _mbsrchr(module_name,'\\');
        if (last_slash)
          strcpy(module_name,last_slash+1);
        strcat(module_name,": ");
      }
#endif
    }
}