void ConsolePrintWarning(MSGVEC *msgvecP)
{
  TCHAR format[80];
  TCHAR *msgtextP;

  // Print the primary warning message.

  msgtextP = GetMessageText(msgvecP->code);

  StrPrintf (format, msgtextP,
    msgvecP->param[0], msgvecP->param[1], msgvecP->param[2],
    msgvecP->param[3], msgvecP->param[4], msgvecP->param[5],
    msgvecP->param[6], msgvecP->param[7]);

  FPrintf (stderr, _T("\nWarning: %s\n"), format);

  // Print the (optional) secondary warning message.

  if (msgvecP->subcode)
    {
    msgtextP = GetMessageText(msgvecP->subcode);

    StrPrintf (format, msgtextP,
      msgvecP->subparam[0], msgvecP->subparam[1], msgvecP->subparam[2],
      msgvecP->subparam[3], msgvecP->subparam[4], msgvecP->subparam[5],
      msgvecP->subparam[6], msgvecP->subparam[7]);

    FPrintf (stderr, _T("%s\n"), format);
    }
}