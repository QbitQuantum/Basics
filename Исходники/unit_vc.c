UInt VG_(message)(VgMsgKind kind, const HChar* format, ...)
{ UInt ret; va_list vargs; va_start(vargs, format); ret = vprintf(format, vargs); va_end(vargs); printf("\n"); return ret; }