void initialize_FramepaC(int max_symbols)
{
   if (!Initialized)
      {
      FrShutdown = shutdown_FramepaC ;
      FrSymbolTable::current()->expandTo(max_symbols) ;
      void FramepaC_init_inheritance_setting_func() ;
      FramepaC_init_inheritance_setting_func() ;
      initialize_FrReadTable() ;
#if defined(__SUNOS__) && !defined(__SOLARIS__)
      // SunOS 4.x has on_exit() instead of the standard atexit(); Solaris
      // has atexit() but no on_exit()....
      on_exit(shutdown_FramepaC_sun,(caddr_t) 0) ;
#elif defined(_MSC_VER)
      atexit(shutdown_FramepaC_VC) ;
      _set_new_mode(1) ;		// do GC if malloc() fails
#else
      atexit(shutdown_FramepaC) ;
#endif /* __SUNOS__ && !__SOLARIS__ */
      Initialized = true ;
      }
   return ;
}