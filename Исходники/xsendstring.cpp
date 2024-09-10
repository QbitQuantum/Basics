 wchar2bytes(wchar_t wc):  bytes(new char[MB_CUR_MAX*2 + sizeof(wchar_t)*2 + 2 + 1]) {
   mbstate_t ps;
   memset(&ps, 0, sizeof(ps));//initialize mbstate
   size_t n;
   if ((n = wcrtomb(bytes, wc, &ps)) == size_t(-1))
     snprintf(bytes, NumberOf(bytes), "U+%04X", int(wc));
   else
     bytes[n] = 0;
 }