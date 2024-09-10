/**
 * Convert character vector between given encodings
 *
 * @param str     input character vector or list of raw vectors
 * @param from  source encoding, \code{NULL} or \code{""} for default enc
 * @param to    target encoding, \code{NULL} or \code{""} for default enc
 * @param to_raw single logical, should list of raw vectors be returned?
 * @return a converted character vector or list of raw vectors
 *
 * @version 0.1 (Marek Gagolewski)
 * @version 0.2 (Marek Gagolewski) arg to_raw_added, encoding marking
 * @version 0.3 (Marek Gagolewski, 2013-06-16) make StriException-friendly
 * @version 0.4 (Marek Gagolewski, 2013-08-08) use StriContainerListRaw
 * @version 0.5 (Marek Gagolewski, 2013-11-20) BUGFIX call stri_encode_from_marked if necessary
 */
SEXP stri_encode(SEXP str, SEXP from, SEXP to, SEXP to_raw)
{
   const char* selected_from = stri__prepare_arg_enc(from, "from", true);
   if (!selected_from && Rf_isVectorAtomic(str))
      return stri_encode_from_marked(str, to, to_raw);

   str = stri_prepare_arg_list_raw(str, "str");
   const char* selected_to   = stri__prepare_arg_enc(to, "to", true);
   bool to_raw_logical = stri__prepare_arg_logical_1_notNA(to_raw, "to_raw");

   UConverter* uconv_from = NULL;
   UConverter* uconv_to = NULL;

   STRI__ERROR_HANDLER_BEGIN
   StriContainerListRaw str_cont(str);
   R_len_t str_n = str_cont.get_n();

   // get the number of strings to convert; if == 0, then you know what's the result
   if (str_n <= 0) return Rf_allocVector(to_raw_logical?VECSXP:STRSXP, 0);

   // Open converters
   uconv_from = stri__ucnv_open(selected_from);
   uconv_to = stri__ucnv_open(selected_to);


   // Get target encoding mark
   UErrorCode err = U_ZERO_ERROR;
   const char* uconv_to_name = ucnv_getName(uconv_to, &err);
   if (U_FAILURE(err))
      throw StriException(err);
   cetype_t encmark_to = CE_BYTES; // all other cases than the below ones
      // - bytes enc (this is reasonable, isn't it?)
   if (!to_raw_logical) { // otherwise not needed
      if (!strcmp(uconv_to_name, "US-ASCII") || !strcmp(uconv_to_name, "UTF-8"))
         encmark_to = CE_UTF8; // no CE for ASCII, will be auto-detected by mkCharLenCE
      else if (!strcmp(uconv_to_name, "ISO-8859-1"))
         encmark_to = CE_LATIN1;
      else if (!strcmp(uconv_to_name, ucnv_getDefaultName()))
         encmark_to = CE_NATIVE;
   }

   // Prepare out val
   SEXP ret;
   PROTECT(ret = Rf_allocVector(to_raw_logical?VECSXP:STRSXP, str_n));

   String8 buf(0); // will be extended in a moment

   for (R_len_t i=0; i<str_n; ++i) {
      if (str_cont.isNA(i)) {
         if (to_raw_logical) SET_VECTOR_ELT(ret, i, R_NilValue);
         else                SET_STRING_ELT(ret, i, NA_STRING);
         continue;
      }

      const char* curd = str_cont.get(i).c_str();
      R_len_t curn     = str_cont.get(i).length();

      err = U_ZERO_ERROR;
      UnicodeString encs(curd, curn, uconv_from, err); // FROM -> UTF-16 [this is the slow part]
      if (U_FAILURE(err))
         throw StriException(err);

      R_len_t curn_tmp = encs.length();
      const UChar* curs_tmp = encs.getBuffer(); // The buffer contents is (probably) not NUL-terminated.
      if (!curs_tmp)
         throw StriException(MSG__INTERNAL_ERROR);

      R_len_t bufneed = UCNV_GET_MAX_BYTES_FOR_STRING(curn_tmp, ucnv_getMaxCharSize(uconv_to));
      // "The calculated size is guaranteed to be sufficient for this conversion."
      buf.resize(bufneed);

      err = U_ZERO_ERROR;
//      bufneed = encs.extract(buf.data(), buf.size(), uconv_to, err); // UTF-16 -> TO
      ucnv_resetFromUnicode(uconv_to);
      bufneed = ucnv_fromUChars(uconv_to, buf.data(), buf.size(), curs_tmp, curn_tmp, &err);
      if (bufneed <= buf.size()) {
         if (U_FAILURE(err))
            throw StriException(err);
      }
      else {// larger buffer needed [this shouldn't happen?]
//         warning("buf extending");
         buf.resize(bufneed);
         err = U_ZERO_ERROR;
         bufneed = ucnv_fromUChars(uconv_to, buf.data(), buf.size(), curs_tmp, curn_tmp, &err);
         if (U_FAILURE(err))
            throw StriException(err);
         if (bufneed > buf.size())
            throw StriException(MSG__INTERNAL_ERROR);
      }

      if (to_raw_logical) {
         SEXP outobj = Rf_allocVector(RAWSXP, bufneed);
         memcpy(RAW(outobj), buf.data(), (size_t)bufneed);
         SET_VECTOR_ELT(ret, i, outobj);
      }
      else {
         SET_STRING_ELT(ret, i, Rf_mkCharLenCE(buf.data(), bufneed, encmark_to));
      }
   }

   if (uconv_from) {
      ucnv_close(uconv_from);
      uconv_from = NULL;
   }
   if (uconv_to) {
      ucnv_close(uconv_to);
      uconv_to = NULL;
   }

   UNPROTECT(1);
   return ret;

   STRI__ERROR_HANDLER_END({
      if (uconv_from)
         ucnv_close(uconv_from);
      if (uconv_to)
         ucnv_close(uconv_to);
   })
}