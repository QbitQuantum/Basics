int _cdecl isblank (int c)
{return (_isctype(c, _BLANK) || c == '\t');}