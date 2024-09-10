void PrintManager::Printf(const HashedString& Category, int Level,
                          const char* Format, ...) {
  Map<HashedString, int>::Iterator CatIter;
  if (Category) {
    CatIter = sPrintLevels.Search(Category);
  }
  // If we don't have a level defined for the given category, use the default
  if (CatIter.IsNull()) {
    CatIter = sPrintLevels.Search(HashedString::NullString);
  }
  int PrintLevel = CatIter.IsNull() ? 0 : *CatIter;

  if (Level <= PrintLevel) {
    va_list Args;

    va_start(Args, Format);
    VSPRINTF(m_StringBuffer, STRINGBUFFERSIZE, Format, Args);

    // Now send string wherever I want it to go...

    if (m_Channels & PRINTCHANNEL_Console) {
      fputs(m_StringBuffer, stdout);  // puts appends an \n
    }

#if BUILD_DEV
    if (m_Channels & PRINTCHANNEL_Output) {
#if BUILD_WINDOWS
      OutputDebugString(m_StringBuffer);
#else
// TODO PORT LATER: Output to debugger on other platforms.
#endif
    }
#endif

    // Handle logging differently in Debug and Release
    if (m_Channels & PRINTCHANNEL_Log) {
#if OPENLOGFILE
      if (m_LogFilename) {
        FileStream LogStream(m_LogFilename,
                             FileStream::EFM_Append);  // Append files for every
                                                       // separate print; slow.
        LogStream.PrintF(m_StringBuffer);
      }
#else
      if (m_LogStream) {
        m_LogStream->PrintF(m_StringBuffer);
      }
#endif
    }
  }
}