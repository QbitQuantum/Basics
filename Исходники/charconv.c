static int
str2code(char *codestr, unsigned int *code)
{
  if (strmatch(codestr, "euc-jp")
      || strmatch(codestr, "euc")
      || strmatch(codestr, "eucjp")) {
    /* input = Shift_jis (codepage 932) */
    *code = 20932;
  } else if (strmatch(codestr, "ansi")) {
    /* ANSI codepage (MBCS) ex. shift-jis in Windows XP Japanese edition.*/
    *code = CP_ACP;
  } else if (strmatch(codestr, "mac")) {
    /* Macintosh codepage */
    *code = CP_MACCP;
  } else if (strmatch(codestr, "oem")) {
    /* OEM localized default codepage */
    *code = CP_OEMCP;
  } else if (strmatch(codestr, "utf-7")) {
    /* UTF-7 codepage */
    *code = CP_UTF7;
  } else if (strmatch(codestr, "utf-8")) {
    /* UTF-8 codepage */
    *code = CP_UTF8;
  } else if (strmatch(codestr, "sjis")
	     || strmatch(codestr, "sjis-win")
	     || strmatch(codestr, "shift-jis")
	     || strmatch(codestr, "shift_jis")) {
    /* sjis codepage = 932 */
    *code = 932;
  } else if (codestr[0] >= '0' && codestr[0] <= '9') {
    /* codepage number */
    *code = atoi(codestr);
    if (! IsValidCodePage(*code)) {
      jlog("Error: charconv_win32: codepage \"%d\" not found\n", codestr);
      return -1;
    }
  } else {
    fprintf(stderr, "Error: str2code: unknown source codepage \"%s\"\n", codestr);
    fprintf(stderr, "Error: str2code: valids are \"euc-jp\", \"ansi\", \"mac\", \"oem\", \"utf-7\", \"utf-8\", \"sjis\" and codepage number\n");
    return -1;
  }
  
  return 0;
}