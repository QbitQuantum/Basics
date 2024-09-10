static BSTR
CopyBSTR(BSTR aSrc)
{
  return SysAllocStringLen(aSrc, SysStringLen(aSrc));
}