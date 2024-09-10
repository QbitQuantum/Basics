void AbstrDebugOut::Message(const char* source, const char* format, ...)
{
  if (!m_bShowMessages) return;
  char buff[16384];

  va_list args;
  va_start(args, format);
#ifdef DETECTED_OS_WINDOWS
  _vsnprintf_s(buff, 16384, sizeof(buff), format, args);
#else
  vsnprintf(buff, sizeof(buff), format, args);
#endif
  va_end(args);

  this->printf(CHANNEL_MESSAGE, source, buff);
}