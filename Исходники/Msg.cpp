static int ShowMsgVA(UINT type, const char *pFmt, va_list va)
{
  char buf[1024];

  VSNPRINTF(buf, sizeof(buf)/sizeof(buf[0]), pFmt, va);

  return ShowMsg(buf, type);
}