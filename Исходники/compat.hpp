_Check_return_ inline bool __isblank(_In_ int _C) 
    { return (MB_CUR_MAX > 1 ? _isctype(_C,_BLANK) : __chvalidchk(_C, _BLANK)); }