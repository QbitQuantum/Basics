int main(int argc, char* argv[]) {
  bool resetClipboard = false;
  char *cp;
  for(argv++; *argv && *(cp = *argv) == '-'; argv++) {
    for(cp++; *cp; cp++) {
      switch(*cp) {
      case 'r': resetClipboard = true; continue;
      default: usage();
      }
      break;
    }
  }

  if(OpenClipboard(NULL) == 0) {
    _ftprintf(stderr,_T("%s\n"), getLastErrorText().cstr());
    return -1;
  }
  if(resetClipboard) {
    if(EmptyClipboard() == 0) {
      _ftprintf(stderr,_T("%s\n"), getLastErrorText().cstr());
      return -1;
    }
  } else {
    for(int cf = EnumClipboardFormats(0); cf; cf = EnumClipboardFormats(cf)) {
      TCHAR name[256];
      GetClipboardFormatName(cf,name,ARRAYSIZE(name));
      TCHAR *cfName = findFormatName(cf);
      if(cfName != NULL) {
        _tprintf(_T("format:%-20s:"), cfName);
      } else {
        _tprintf(_T("format:%-20s:"), name);
      }
      HANDLE t = GetClipboardData(cf);
      if(t == NULL) {
        _tprintf(_T("GetClipboardData failed:%s\n"), getLastErrorText().cstr());
      } else {
        TCHAR *str = (TCHAR*)t;
        if(cf == CF_TEXT) {
          _tprintf(_T("<%s>\n"), str);
        }
        try {
          hexdump(str,40,stdout);
        } catch(...) {
        }
      }
    }
  }
  CloseClipboard();
  return 0;
}