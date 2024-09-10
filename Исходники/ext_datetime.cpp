String c_DateInterval::t_format(CStrRef format) {
  INSTANCE_METHOD_INJECTION_BUILTIN(DateInterval, DateInterval::format);
  StringBuffer s;
  const int LENGTH = 33;
  char buf[LENGTH];
  int l;
  bool hasFormatSpec = false;
  for (int i = 0; i < format.length(); ++i) {
    char c = format.charAt(i);
    if (!hasFormatSpec) {
      if (c == '%') {
        hasFormatSpec = true;
      } else {
        s.append(c);
      }
    } else {
      switch (c) {
      case 'Y': l = snprintf(buf, LENGTH, "%02lld", m_y); break;
      case 'y': l = snprintf(buf, LENGTH, "%lld", m_y); break;

      case 'M': l = snprintf(buf, LENGTH, "%02lld", m_m); break;
      case 'm': l = snprintf(buf, LENGTH, "%lld", m_m); break;

      case 'D': l = snprintf(buf, LENGTH, "%02lld", m_d); break;
      case 'd': l = snprintf(buf, LENGTH, "%lld", m_d); break;

      case 'H': l = snprintf(buf, LENGTH, "%02lld", m_h); break;
      case 'h': l = snprintf(buf, LENGTH, "%lld", m_h); break;

      case 'I': l = snprintf(buf, LENGTH, "%02lld", m_i); break;
      case 'i': l = snprintf(buf, LENGTH, "%lld", m_i); break;

      case 'S': l = snprintf(buf, LENGTH, "%02lld", m_s); break;
      case 's': l = snprintf(buf, LENGTH, "%lld", m_s); break;

      case 'a': {
        if (m_days.isInteger()) {
          l = snprintf(buf, LENGTH, "%lld", m_days.toInt64());
        } else {
          l = snprintf(buf, LENGTH, "(unknown)");
        }
        break;
      }

      case 'r': l = snprintf(buf, LENGTH, "%s", m_invert ? "-" : ""); break;
      case 'R': l = snprintf(buf, LENGTH, "%c", m_invert ? '-' : '+'); break;

      case '%': l = snprintf(buf, 32, "%%"); break;
      default: buf[0] = '%'; buf[1] = c; buf[2] = '\0'; l = 2; break;
      }

      s.append(buf, std::min(l, LENGTH - 1));
      hasFormatSpec = false;
    }
  }
  return s.detach();
}