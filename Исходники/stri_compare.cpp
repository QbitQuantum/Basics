/**
 * Compare elements in 2 character vectors, with collation
 *
 * @param e1 character vector
 * @param e2 character vector
 * @param opts_collator passed to stri__ucol_open()
 * @param type [internal] vector of length 2,
 * type[0]: 0 for ==, -1 for < and 1 for >,
 * type[1]: 0 or 1 (whether to negate the results)
 *
 * @return logical vector
 *
 * @version 0.2-1  (Marek Gagolewski, 2014-03-19)
 *
 * @version 0.2-3 (Marek Gagolewski, 2014-05-07)
 *          opts_collator == NA no longer allowed
 *
 * @version 0.3-1 (Marek Gagolewski, 2014-11-04)
 *    Issue #112: str_prepare_arg* retvals were not PROTECTed from gc
 */
SEXP stri_cmp_logical(SEXP e1, SEXP e2, SEXP opts_collator, SEXP type)
{
   // we'll perform a collator-based cmp
   // type is an internal arg, check manually, error() allowed here
   if (!Rf_isInteger(type) || LENGTH(type) != 2)
      Rf_error(MSG__INCORRECT_INTERNAL_ARG);
   int _type = INTEGER(type)[0];
   int _negate = INTEGER(type)[1];
   if (_type > 1 || _type < -1 || _negate < 0 || _negate > 1)
      Rf_error(MSG__INCORRECT_INTERNAL_ARG);

   PROTECT(e1 = stri_prepare_arg_string(e1, "e1")); // prepare string argument
   PROTECT(e2 = stri_prepare_arg_string(e2, "e2")); // prepare string argument

   // call stri__ucol_open after prepare_arg:
   // if prepare_arg had failed, we would have a mem leak
   UCollator* col = NULL;
   col = stri__ucol_open(opts_collator);

   STRI__ERROR_HANDLER_BEGIN(2)

   R_len_t vectorize_length = stri__recycling_rule(true, 2, LENGTH(e1), LENGTH(e2));

   StriContainerUTF8 e1_cont(e1, vectorize_length);
   StriContainerUTF8 e2_cont(e2, vectorize_length);

   SEXP ret;
   STRI__PROTECT(ret = Rf_allocVector(LGLSXP, vectorize_length));
   int* ret_tab = LOGICAL(ret);

   for (R_len_t i = 0; i < vectorize_length; ++i)
   {
      if (e1_cont.isNA(i) || e2_cont.isNA(i)) {
         ret_tab[i] = NA_LOGICAL;
         continue;
      }

      R_len_t     cur1_n = e1_cont.get(i).length();
      const char* cur1_s = e1_cont.get(i).c_str();
      R_len_t     cur2_n = e2_cont.get(i).length();
      const char* cur2_s = e2_cont.get(i).c_str();

      // with collation
      UErrorCode status = U_ZERO_ERROR;
      ret_tab[i] = (_type == (int)ucol_strcollUTF8(col,
         cur1_s, cur1_n, cur2_s, cur2_n, &status
      ));
      STRI__CHECKICUSTATUS_THROW(status, {/* do nothing special on err */})

      if (_negate)
         ret_tab[i] = !ret_tab[i];
   }