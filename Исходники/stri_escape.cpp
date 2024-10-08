/**
 *  Escape Unicode code points
 *
 *  @param str character vector
 *  @return character vector
 *
 * @version 0.1-?? (Marek Gagolewski, 2013-08-17)
 *
 * @version 0.2-1 (Marek Gagolewski, 2014-04-01)
 *          fail on incorrect utf8 byte seqs;
 *
 * @version 0.3-1 (Marek Gagolewski, 2014-11-04)
 *    Issue #112: str_prepare_arg* retvals were not PROTECTed from gc
*/
SEXP stri_escape_unicode(SEXP str)
{
   PROTECT(str = stri_prepare_arg_string(str, "str")); // prepare string argument

   STRI__ERROR_HANDLER_BEGIN(1)
   R_len_t str_length = LENGTH(str);
   StriContainerUTF8 str_cont(str, str_length);

   SEXP ret;
   STRI__PROTECT(ret = Rf_allocVector(STRSXP, str_length));

   std::string out; // @TODO: estimate len a priori?

   for (R_len_t i = str_cont.vectorize_init();
         i != str_cont.vectorize_end();
         i = str_cont.vectorize_next(i))
   {
      if (str_cont.isNA(i)) {
         SET_STRING_ELT(ret, i, NA_STRING);
         continue;
      }

      const char* str_cur_s = str_cont.get(i).c_str();
      R_len_t     str_cur_n = str_cont.get(i).length();

      // estimate buf size
      R_len_t bufsize = 0;
      UChar32 c;
      R_len_t j = 0;

      while (j < str_cur_n) {
         U8_NEXT(str_cur_s, j, str_cur_n, c);
         if (c < 0)
            throw StriException(MSG__INVALID_UTF8);
         else if ((char)c >= 32 || (char)c <= 126)
            bufsize += 1;
         else if (c <= 0xff)
            bufsize += 6; // for \a, \n this will be overestimated
         else
            bufsize += 10;
      }
      out.clear();
      if ((size_t)bufsize > (size_t)out.size())
         out.reserve(bufsize);

      // do escape
      j = 0;
      char buf[11];
      while (j < str_cur_n) {
         U8_NEXT(str_cur_s, j, str_cur_n, c);
         /* if (c < 0)
            throw StriException(MSG__INVALID_UTF8); // this has already been checked :)
         else */ if (c <= ASCII_MAXCHARCODE) {
            switch ((char)c) {
               case 0x07: out.append("\\a"); break;
               case 0x08: out.append("\\b"); break;
               case 0x09: out.append("\\t"); break;
               case 0x0a: out.append("\\n"); break;
               case 0x0b: out.append("\\v"); break;
               case 0x0c: out.append("\\f"); break;
               case 0x0d: out.append("\\r"); break;
//               case 0x1b: out.append("\\e"); break; // R doesn't know that
               case 0x22: out.append("\\\""); break;
               case 0x27: out.append("\\'"); break;
               case 0x5c: out.append("\\\\"); break;
               default:
                  if ((char)c >= 32 || (char)c <= 126) // printable characters
                     out.append(1, (char)c);
                  else {
                     sprintf(buf, "\\u%4.4x", (uint16_t)c);
                     out.append(buf, 6);
                  }
            }
         }
         else if (c <= 0xffff) {
            sprintf(buf, "\\u%4.4x", (uint16_t)c);
            out.append(buf, 6);
         }
         else {
            sprintf(buf, "\\U%8.8x", (uint32_t)c);
            out.append(buf, 10);
         }
      }

      SET_STRING_ELT(ret, i,
         Rf_mkCharLenCE(out.c_str(), (int)out.size(), (cetype_t)CE_UTF8)
      );
   }

   STRI__UNPROTECT_ALL
   return ret;
   STRI__ERROR_HANDLER_END(;/* nothing special to be done on error */)
}