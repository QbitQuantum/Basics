void HttpServletResponse::SetDateHeader(const std::string& name, long long date)
{
  // Sun, 06 Nov 1994 08:49:37 GMT  ; RFC 822, updated by RFC 1123

  const char* months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  const char* days[7] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
  std::time_t timeep = date / 1000;
  std::tm t;
#ifdef US_PLATFORM_WINDOWS
  if (gmtime_s(&t, &timeep) != 0)
#else
  if (gmtime_r(&timeep, &t) != nullptr)
#endif
  {
    char dataStr[30];
    int n = snprintf(dataStr, 30, "%s, %02d %s %d %02d:%02d:%02d GMT", days[t.tm_wday], t.tm_mday, months[t.tm_mon], (1900 + t.tm_year), t.tm_hour, t.tm_min, t.tm_sec);
    if (n < 0) return;
    this->SetHeader(name, dataStr);
  }
}