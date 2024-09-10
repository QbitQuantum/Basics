int main() {
  // Get command line, go over program name
  char *pCommandLine = GetCommandLine();
  if (*pCommandLine == '"') {
    pCommandLine++;
    while (*pCommandLine && *pCommandLine != '"') pCommandLine++;
    if (*pCommandLine == '"') pCommandLine++;
  } else
    while (*pCommandLine && *pCommandLine != ' ') pCommandLine++;
  while (*pCommandLine == ' ') pCommandLine++;
  // Call
  return WinMain(GetModuleHandle(NULL), 0, pCommandLine, 0);
}