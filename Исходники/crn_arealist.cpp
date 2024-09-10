   static void area_fatal_error(const char* pFunc, const char* pMsg, ...)
   {
      pFunc;
      va_list args;
      va_start(args, pMsg);

      char buf[512];
#ifdef _MSC_VER
      _vsnprintf_s(buf, sizeof(buf), pMsg, args);
#else
      vsnprintf(buf, sizeof(buf), pMsg, args);
#endif

      va_end(args);

      CRNLIB_FAIL(buf);
   }