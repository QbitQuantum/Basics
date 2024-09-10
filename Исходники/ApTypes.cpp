String Apollo::TimeValue::toRFC2822()
{
  // "Thu, 19 Nov 1981 08:52:00 GMT"
  // "Thu, 19 Nov 1981 08:52:00 +0100
  time_t tSec = Sec();
  struct tm tms = *(::localtime(&tSec));

  int nMaxSize = 1000;
  Flexbuf<TCHAR> buf(nMaxSize);
  _tcsftime((TCHAR*) buf, nMaxSize-1, _T("%a, %d %b %Y %H:%M:%S"), &tms);

  String s = (TCHAR*) buf;

  long gmtoff = 0;
  if (_get_timezone(&gmtoff) == 0) {
    gmtoff -= tms.tm_isdst ? 3600 : 0;
    s.appendf(" %+03d%02d", -(gmtoff / (60 * 60)), (gmtoff % (60 * 60)));
  }

  return s;
}