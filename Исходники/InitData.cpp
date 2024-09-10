void InitializeParameters::readTextFile(const String &fileName) {
  FILE *f = FOPEN(fileName, _T("r"));

  TCHAR line[100];
  CompactIntArray data;
  try {
    int lineCount = 0;
    while(FGETS(line, ARRAYSIZE(line), f)) {
      lineCount++;
      if(data.size() >= MAXDATACOUNT) {
        throwException(_T("Too many data. Max = %d"), MAXDATACOUNT);
      }
      double x;
      int i;
      if(_stscanf(line,_T("%le"),&x) == 1 && x >= 0) {
        if(x > INT_MAX) {
          i = INT_MAX;
        } else {
          i = (int)floor(x);
        }
        data.add(i);
      } else {
        throwException(_T("Illegal input in line %d:<%s>. Must be non-negative number."), lineCount, line);
      }
    }
    if(data.size() == 0) {
      throwException(_T("No data read"));
    }
    fclose(f);
    f = NULL;
    m_fileData     = data;
    m_elementCount = m_fileData.size();
    m_fileName     = fileName;
  } catch(...) {
    if(f) {
      fclose(f);
    }
    throw;
  }
}