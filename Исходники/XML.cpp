void
bmt::XML::SaveXML (void)
{
  std::wstring documents_dir = BMT_GetDocumentsDir ();

  wchar_t wszXML [1024];

  wsprintf (wszXML, L"%s\\WB Games\\Batman Arkham Knight\\GFXSettings.BatmanArkhamKnight.xml", documents_dir.c_str ());

  wchar_t* wszOut = new wchar_t [8192];
  wchar_t* wszEnd = print (wszOut, bmak_xml, 0);

  int last_brace = 0;

  // XML parser doesn't like the TM symbol, so get it the hell out of there!
  for (int i = 0; i < 8192; i++) {
    if (wszOut [i] == L'™')
      wszOut [i] = L' ';
    if (wszOut [i] == L'>')
      last_brace = i;
  }

  wszOut [last_brace + 1] = L'\0';

  FILE* fXML;
  errno_t ret = _wfopen_s (&fXML, wszXML, L"w,ccs=UTF-16LE");

  if (ret != 0 || fXML == 0) {
    delete [] wszOut;
    BMT_MessageBox (L"Could not open GFXSettings.BatmanArkhamKnight.xml for writing!\n", L"Unable to save XML settings", MB_OK | MB_ICONSTOP);
    return;
  }

  fputws (L"<?xml version=\"1.0\" encoding=\"UTF-16\" standalone=\"no\"?>\n", fXML);
  fputws (wszOut, fXML);

  delete [] wszOut;

  fflush (fXML);
  fclose (fXML);

  //
  // Windows 10 File Permission Fixes
  //

  // Normalize file ownership and attributes (Win10 fix)
  BMT_SetNormalFileAttribs (wszXML);

  // Now normalize the directory as a whole
  wsprintf (wszXML, L"%s\\WB Games\\Batman Arkham Knight", documents_dir.c_str ());
  BMT_SetNormalFileAttribs (wszXML);
}