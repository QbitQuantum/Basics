COLORREF CRichEditCtrlExtn::ConvertColourToColorRef(CString &csValue)
{
  // Value is either a colour name or "#RRGGBB"
  // Note COLORREF = 0x00bbggrr but HTML = 0x00rrggbb
  // Values for named colours here are in COLORREF format
  long retval(0L);
  if (csValue.Left(1) == L"#") {
    // Convert HTML to COLORREF
    ASSERT(csValue.GetLength() == 7);
    int icolour;
#if (_MSC_VER >= 1400)
    swscanf_s(csValue.Mid(1), L"%06x", &icolour);
#else
    swscanf(csValue.Mid(1), L"%06x", &icolour);
#endif
    int ired = (icolour & 0xff0000) >> 16;
    int igreen = (icolour & 0xff00);
    int iblue = (icolour & 0xff) << 16;
    return (COLORREF)(iblue + igreen + ired);
  }