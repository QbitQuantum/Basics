/**
 * Sets current (default) ICU locale
 *
 * @param loc new locale (a single character string)
 * @return nothing (\code{R_NilValue})
 *
 * @version 0.1-?? (Marek Gagolewski)
 */
SEXP stri_locale_set(SEXP loc)
{
   const char* qloc = stri__prepare_arg_locale(loc, "locale", false); /* this is R_alloc'ed */
   UErrorCode status = U_ZERO_ERROR;
   uloc_setDefault(qloc, &status);
   STRI__CHECKICUSTATUS_RFERROR(status, {/* do nothing special on err */}) // error() allowed here
   return R_NilValue;