void
MIFrfile::skipImport()
{
  int ch;

  skipLine();

  while ((ch = getChar()) != EOF) {
    switch (ch) {
      case '&':
      case '=':
        skipLine();
        break;
      case '\n':
      case '\r':
      case ' ':
        break;
      default:
        ungetChar(ch);
        return;
    }
  }
}