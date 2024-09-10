      static std::string
      str(const char* format, ...)
      {
        char bfr[1024] = {0};
        std::va_list ap;
        va_start(ap, format);

#if defined(DUNE_SYS_HAS_VSNPRINTF)
        vsnprintf(bfr, sizeof(bfr), format, ap);
#elif defined(DUNE_SYS_HAS_VSNPRINTF_S)
        vsnprintf_s(bfr, sizeof(bfr), sizeof(bfr) - 1, format, ap);
#else
        std::vsprintf(bfr, format, ap);
#endif
        va_end(ap);

        return bfr;
      }