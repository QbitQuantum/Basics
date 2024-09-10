void WWIV_make_abs_cmd(std::string& out) {
  // pszOutBuffer must be at least MAX_PATH in size.
  char s[MAX_PATH], s1[MAX_PATH], s2[MAX_PATH], *ss1;
  char szTempBuf[MAX_PATH];

  strncpy(s1, out.c_str(), MAX_PATH);

  if (s1[1] == ':') {
    if (s1[2] != '\\') {
      _getdcwd(wwiv::UpperCase<char>(s1[0]) - 'A' + 1, s, MAX_PATH);
      if (s[0]) {
        _snprintf(s1, sizeof(s1), "%c:\\%s\\%s", s1[0], s, out.substr(2).c_str());
      } else {
        _snprintf(s1, sizeof(s1), "%c:\\%s", s1[0], out.substr(2).c_str());
      }
    }
  } else if (s1[0] == '\\') {
    _snprintf(s1, sizeof(s1), "%c:%s", GetApplication()->GetHomeDir()[0], out.c_str());
  } else {
    strncpy(s2, s1, sizeof(s2));
    strtok(s2, " \t");
    if (strchr(s2, '\\')) {
      _snprintf(s1, sizeof(s1), "%s%s", GetApplication()->GetHomeDir().c_str(), out.c_str());
    }
  }

  char* ss = strchr(s1, ' ');
  if (ss) {
    *ss = '\0';
    _snprintf(s2, sizeof(s2), " %s", ss + 1);
  } else {
    s2[0] = '\0';
  }
  for (int i = 0; exts[i]; i++) {
    if (i == 0) {
      ss1 = strrchr(s1, '\\');
      if (!ss1) {
        ss1 = s1;
      }
      if (strchr(ss1, '.') == 0) {
        continue;
      }
    }
    _snprintf(s, sizeof(s), "%s%s", s1, exts[i]);
    if (s1[1] == ':') {
      if (WFile::Exists(s)) {
        std::ostringstream os;
        os << s << s2;
        out = os.str();
        return;
      }
    } else {
      if (WFile::Exists(s)) {
        std::ostringstream os;
        os << GetApplication()->GetHomeDir() << s << s2;
        out = os.str();
      } else {
        _searchenv(s, "PATH", szTempBuf);
        ss1 = szTempBuf;
        if (ss1 && strlen(ss1) > 0) {
          std::ostringstream os;
          os << ss1 << s2;
          out = os.str();
          return;
        }
      }
    }
  }

  std::ostringstream os;
  os << GetApplication()->GetHomeDir() << s1 << s2;
  out = os.str();
}