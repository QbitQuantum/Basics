void InputThread::readTextFile(const String &fileName) {
  FILE *f = FOPEN(fileName, _T("r"));
  TCHAR line[1000];
  while(FGETS(line, ARRAYSIZE(line), f)) {
    m_inputQueue.put(line);
  }
  fclose(f);
}