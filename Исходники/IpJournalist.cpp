  void Journalist::Printf( EJournalLevel level, EJournalCategory category,
                           const char* pformat, ... ) const
  {
    // wrap the arguments and pass to VPrintf
    va_list ap;
    va_start(ap, pformat);
    VPrintf(level, category, pformat, ap);
// TODO uncomment when done testing
//   vfprintf( stdout, pformat, ap );

    va_end(ap);
  }