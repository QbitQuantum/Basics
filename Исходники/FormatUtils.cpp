UnicodeString FmtLoadStr(intptr_t Id, fmt::ArgList args)
{
  UnicodeString Fmt = GetGlobals()->GetMsg(Id);
  if (!Fmt.IsEmpty())
  {
    UnicodeString Result = Sprintf(Fmt, args);
    return Result;
  }
  DEBUG_PRINTF("Unknown resource string id: %d\n", Id);
  return UnicodeString();
}