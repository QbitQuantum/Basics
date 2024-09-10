void TimeFmt::printHourMinSec(int sec, char *buf, int buflen, int hoursonlyifneeded) {
  int hours, minutes, seconds;
  int negative = sec < 0;

  sec = ABS(sec);
  if (buf == NULL) return;

  if (sec == -1) {
    *buf = 0;
    return;
  }

  hours = sec / 3600;
  sec -= hours * 3600;
  seconds = sec % 60;
  sec /= 60;
  minutes = sec;

  String sp;
  if (hoursonlyifneeded && hours == 0)
    sp = StringPrintf("%s%d:%02d", (minutes == 0 && negative) ? "-" : "", minutes, seconds);
  else
    sp = StringPrintf("%s%d:%02d:%02d", (minutes == 0 && negative) ? "-" : "", hours, minutes, seconds);

  STRNCPY(buf, sp, buflen);
}