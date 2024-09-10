/* Match one character. Doesn't modify txtIt, returns length of regexp char in *length  */
bool matchcharacter(char *regexp, JsvStringIterator *txtIt, int *length, matchInfo *info) {
  *length = 1;
  char ch = jsvStringIteratorGetChar(txtIt);
  if (regexp[0]=='.') return true;
  if (regexp[0]=='[') { // Character set (any char inside '[]')
    info->rangeMatch = true;
    bool inverted = regexp[1]=='^';
    if (inverted) (*length)++;
    bool matchAny = false;
    while (regexp[*length] && regexp[*length]!=']') {
      int matchLen;
      matchAny |= matchcharacter(&regexp[*length], txtIt, &matchLen, info);
      (*length) += matchLen;
    }
    if (regexp[*length]==']') {
      (*length)++;
    } else {
      jsExceptionHere(JSET_ERROR, "Unfinished character set in RegEx");
      return false;
    }
    info->rangeMatch = false;
    return matchAny != inverted;
  }
  char cH = regexp[0];
  if (cH=='\\') { // escape character
    *length = 2;
    // fallback to the quoted character (e.g. /,-,? etc.)
    cH = regexp[1];
    // missing quite a few here
    // https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Regular_Expressions
    if (cH=='d') return isNumeric(ch);
    if (cH=='D') return !isNumeric(ch);
    if (cH=='f') { cH=0x0C; goto haveCode; }
    if (cH=='n') { cH=0x0A; goto haveCode; }
    if (cH=='r') { cH=0x0D; goto haveCode; }
    if (cH=='s') return isWhitespace(ch);
    if (cH=='S') return !isWhitespace(ch);
    if (cH=='t') { cH=0x09; goto haveCode; }
    if (cH=='v') { cH=0x0B; goto haveCode; }
    if (cH=='w') return isNumeric(ch) || isAlpha(ch) || ch=='_';
    if (cH=='W') return !(isNumeric(ch) || isAlpha(ch) || ch=='_');
    if (cH>='0' && cH<='9') { cH-='0'; goto haveCode; }
    if (cH=='x' && regexp[2] && regexp[3]) {
      *length = 4;
      cH = (char)((chtod(regexp[2])<<4) | chtod(regexp[3]));
      goto haveCode;
    }
  }
haveCode:
  if (info->rangeMatch && regexp[*length] == '-') { // Character set range start
    info->rangeFirstChar = cH;
    (*length)++;
    int matchLen;
    bool match = matchcharacter(&regexp[*length], txtIt, &matchLen, info);
    (*length)+=matchLen;
    return match;
  }
  if (info->ignoreCase) {
    ch = jsvStringCharToLower(ch);
    cH = jsvStringCharToLower(cH);
  }
  if (info->rangeFirstChar != NO_RANGE) { // Character set range
    char cL = (char)info->rangeFirstChar;
    if (info->ignoreCase) {
      cL = jsvStringCharToLower(cL);
    }
    info->rangeFirstChar = NO_RANGE;
    return (ch >= cL && ch <= cH && cL < cH);
  }
  return cH==ch;
}