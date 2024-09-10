void qore_date_private::format(QoreString &str, const char *fmt) const {
   qore_time_info i;
   get(i);

   const char *s = fmt;
   while (*s) {
      switch (*s) {
         case 'Y':
            if (s[1] != 'Y') {
               str.concat('Y');
               break;
            }
            s++;
            if ((s[1] == 'Y') && (s[2] == 'Y')) {
               str.sprintf("%04d", i.year);
               s += 2;
            }
            else
               str.sprintf("%02d", i.year - (i.year / 100) * 100);
            break;
         case 'M':
            if (s[1] == 'M') {
               str.sprintf("%02d", i.month);
               s++;
               break;
            }
            if ((s[1] == 'o') && (s[2] == 'n')) {
               s += 2;
               if ((s[1] == 't') && (s[2] == 'h')) {
                  s += 2;
                  if (i.month && (i.month <= 12))
                     str.sprintf("%s", months[(int)i.month - 1].long_name);
                  else
                     str.sprintf("Month%d", i.month - 1);
                  break;
               }
               if (i.month && (i.month <= 12))
                  str.sprintf("%s", months[(int)i.month - 1].abbr);
               else
                  str.sprintf("M%02d", i.month);
               break;
            }
            if ((s[1] == 'O') && (s[2] == 'N')) {
               s += 2;
               if ((s[1] == 'T') && (s[2] == 'H')) {
                  s += 2;
                  if (i.month && (i.month <= 12)) {
                     str.sprintf("%s", months[(int)i.month - 1].upper_long_name);
                  }
                  else
                     str.sprintf("MONTH%d", i.month);
                  break;
               }
               if (i.month && (i.month <= 12)) {
                  str.sprintf("%s", months[(int)i.month - 1].upper_abbr);
               }
               else
                  str.sprintf("M%02d", i.month);
               break;
            }
            str.sprintf("%d", i.month);
            break;
         case 'D':
            if (s[1] == 'D') {
               str.sprintf("%02d", i.day);
               s++;
               break;
            }
            if ((s[1] == 'a') && (s[2] == 'y')) {
               s += 2;
               int wday = qore_date_info::getDayOfWeek(i.year, i.month, i.day);
               str.sprintf("%s", days[wday].long_name);
               break;
            }
            if ((s[1] == 'A') && (s[2] == 'Y')) {
               s += 2;
               int wday = qore_date_info::getDayOfWeek(i.year, i.month, i.day);
               str.sprintf("%s", days[wday].upper_long_name);
               break;
            }
            if ((s[1] == 'y') || (s[1] == 'Y')) {
               s++;
               int wday = qore_date_info::getDayOfWeek(i.year, i.month, i.day);
               str.sprintf("%s", *s == 'Y' ? days[wday].upper_abbr : days[wday].abbr);
               break;
            }
            str.sprintf("%d", i.day);
            break;
         case 'H':
            if (s[1] == 'H') {
               str.sprintf("%02d", i.hour);
               s++;
            }
            else
               str.sprintf("%d", i.hour);
            break;
         case 'h':
            if (s[1] == 'h') {
               str.sprintf("%02d", ampm(i.hour));
               s++;
            }
            else
               str.sprintf("%d", ampm(i.hour));
            break;
         case 'P':
            if (i.hour > 11)
               str.sprintf("PM");
            else
               str.sprintf("AM");
            break;
         case 'p':
            if (i.hour > 11)
               str.sprintf("pm");
            else
               str.sprintf("am");
            break;
         case 'm':
            if (s[1] == 'm') {
               str.sprintf("%02d", i.minute);
               s++;
            }
            else if (s[1] == 's') {
               str.sprintf("%03d", i.us / 1000);
               s++;
            }
            else
               str.sprintf("%d", i.minute);
            break;
         case 'S':
            if (s[1] == 'S') {
               str.sprintf("%02d", i.second);
               s++;
            }
            else
               str.sprintf("%d", i.second);
            break;
         case 'u':
            if (s[1] == 'u') {
               str.sprintf("%03d", i.us / 1000);
               s++;
            }
            else if (s[1] == 's') {
               str.sprintf("%06d", i.us);
               s++;
            }
            else
               str.sprintf("%d", i.us / 1000);
            break;
         case 'x':
            if (s[1] == 'x') {
               str.sprintf("%06d", i.us);
               s++;
            }
            else
               str.sprintf("%d", i.us);
            break;
         case 'y':
            str.sprintf("%06d", i.us);
            str.trim_trailing('0');
            break;
         case 'z':
	    str.sprintf("%s", i.zname);
            break;
	    // add iso8601 UTC offset
	 case 'Z':
	    concatOffset(i.utcoffset, str);
	    break;
         default:
	    str.concat(*s);
            break;
      }
      s++;
   }
}