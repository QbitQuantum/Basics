/**
 * Create & set up an ICU Collator
 *
 * WARNING: this fuction is allowed to call the error() function.
 * Use before STRI__ERROR_HANDLER_BEGIN (with other prepareargs).
 *
 * @param opts_collator named R list
 * @return a Collator object that should be closed with ucol_close() after use
 *
 *
 * @version 0.1-?? (Marek Gagolewski)
 *
 * @version 0.2-1 (Marek Gagolewski, 2014-04-17)
 *          allow for NULL opts_collator (identical to list())
 *
 * @version 0.2-3 (Marek Gagolewski, 2014-05-09)
 *          disallow NA as opts_collator
 *
 * @version 0.3-1 (Marek Gagolewski, 2014-11-05)
 *    Issue #112: str_prepare_arg* retvals were not PROTECTed from gc;
 *    + many other bugs in settings establishment
 *
 * @version 0.3-1 (Marek Gagolewski, 2014-11-06)
 *    Fetch opts vals first to avoid memleaks (missing ucol_close calls on Rf_error)
 *
 * @version 0.4-1 (Marek Gagolewski, 2014-12-08)
 *    #23: add `overlap` option
 */
UCollator* stri__ucol_open(SEXP opts_collator)
{
   if (!isNull(opts_collator) && !Rf_isVectorList(opts_collator))
      Rf_error(MSG__INCORRECT_COLLATOR_OPTION_SPEC); // error() allowed here

   R_len_t narg = isNull(opts_collator)?0:LENGTH(opts_collator);

   if (narg <= 0) { // no custom settings - use default Collator
      UErrorCode status = U_ZERO_ERROR;
      UCollator* col = ucol_open(NULL, &status);
      STRI__CHECKICUSTATUS_RFERROR(status, {/* do nothing special on err */}) // error() allowed here
      return col;