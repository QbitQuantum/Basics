/**
 *  Convert case (TitleCase)
 *
 *
 *  @param str character vector
 *  @param opts_brkiter list
 *  @return character vector
 *
 * @version 0.4-1 (Marek Gagolewski, 2014-12-03)
 *    separated from stri_trans_casemap;
 *    use StriUBreakIterator
 */
SEXP stri_trans_totitle(SEXP str, SEXP opts_brkiter) {
   StriBrkIterOptions opts_brkiter2(opts_brkiter, "word");
   PROTECT(str = stri_prepare_arg_string(str, "str")); // prepare string argument

// version 0.2-1 - Does not work with ICU 4.8 (but we require ICU >= 50)
   UCaseMap* ucasemap = NULL;

   STRI__ERROR_HANDLER_BEGIN(1)
   StriUBreakIterator brkiter(opts_brkiter2);

   UErrorCode status = U_ZERO_ERROR;
   ucasemap = ucasemap_open(brkiter.getLocale(), U_FOLD_CASE_DEFAULT, &status);
   STRI__CHECKICUSTATUS_THROW(status, {/* do nothing special on err */})

   status = U_ZERO_ERROR;
   ucasemap_setBreakIterator(ucasemap, brkiter.getIterator(), &status);
   STRI__CHECKICUSTATUS_THROW(status, {/* do nothing special on err */})
   brkiter.free(false);
   // ucasemap_setOptions(ucasemap, U_TITLECASE_NO_LOWERCASE, &status); // to do?
   // now briter is owned by ucasemap.
   // it will be released on ucasemap_close
   // (checked with ICU man & src code)

   R_len_t str_n = LENGTH(str);
   StriContainerUTF8 str_cont(str, str_n);
   SEXP ret;
   STRI__PROTECT(ret = Rf_allocVector(STRSXP, str_n));


   // STEP 1.
   // Estimate the required buffer length
   // Notice: The resulting number of codepoints may be larger or smaller than
   // the number before casefolding
   R_len_t bufsize = str_cont.getMaxNumBytes();
   bufsize += 10; // a small margin
   String8buf buf(bufsize);

   // STEP 2.
   // Do case folding
   for (R_len_t i = str_cont.vectorize_init();
         i != str_cont.vectorize_end();
         i = str_cont.vectorize_next(i))
   {
      if (str_cont.isNA(i)) {
         SET_STRING_ELT(ret, i, NA_STRING);
         continue;
      }

      R_len_t str_cur_n     = str_cont.get(i).length();
      const char* str_cur_s = str_cont.get(i).c_str();

      status = U_ZERO_ERROR;
      int buf_need = ucasemap_utf8ToTitle(ucasemap, buf.data(), buf.size(),
               (const char*)str_cur_s, str_cur_n, &status);

      if (U_FAILURE(status)) {
         buf.resize(buf_need, false/*destroy contents*/);
         status = U_ZERO_ERROR;
         buf_need = ucasemap_utf8ToTitle(ucasemap, buf.data(), buf.size(),
               (const char*)str_cur_s, str_cur_n, &status);

         STRI__CHECKICUSTATUS_THROW(status, {/* do nothing special on err */}) // this shouldn't happen
                                             // we do have the buffer size required to complete this op
      }

      SET_STRING_ELT(ret, i, Rf_mkCharLenCE(buf.data(), buf_need, CE_UTF8));
   }

   if (ucasemap) { ucasemap_close(ucasemap); ucasemap = NULL;}
   STRI__UNPROTECT_ALL
   return ret;

   STRI__ERROR_HANDLER_END({
      if (ucasemap) { ucasemap_close(ucasemap); ucasemap = NULL; }
   })
}