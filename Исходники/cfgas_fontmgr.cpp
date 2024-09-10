static void FX_EnumGdiFonts(CFX_FontDescriptors& fonts,
                            const FX_WCHAR* pwsFaceName,
                            FX_WCHAR wUnicode) {
  HDC hDC = ::GetDC(nullptr);
  LOGFONTW lfFind;
  FXSYS_memset(&lfFind, 0, sizeof(lfFind));
  lfFind.lfCharSet = DEFAULT_CHARSET;
  if (pwsFaceName) {
    FXSYS_wcsncpy(lfFind.lfFaceName, pwsFaceName, 31);
    lfFind.lfFaceName[31] = 0;
  }
  EnumFontFamiliesExW(hDC, (LPLOGFONTW)&lfFind,
                      (FONTENUMPROCW)FX_GdiFontEnumProc, (LPARAM)&fonts, 0);
  ::ReleaseDC(nullptr, hDC);
}