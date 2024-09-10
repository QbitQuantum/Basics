void CGridDlg::OnBnClickedButtonDiagram() {
  if(!validate()) return;

  windowToValue();
  const GridParameters v = getCurrentValue();
  PearlDiagram diagram;
  PixRect *tmp = v.calculateImage(getImage(), &diagram);
  SAFEDELETE(tmp);

  const String dumpFileName = createTempFileName(_T("txt"));
  FILE *f = NULL;
  try {
    const String dstr = diagram.toString();
    f = MKFOPEN(dumpFileName,_T("w"));

    _ftprintf(f, _T("%s"), dstr.cstr());
    fclose(f); f = NULL;

    ExternProcess::run(false, _T("c:\\windows\\system32\\notepad.exe"), dumpFileName.cstr(), NULL);
    UNLINK(dumpFileName);
  } catch (Exception e) {
    if(f) { fclose(f); f = NULL; }
    showException(e);
  }
}