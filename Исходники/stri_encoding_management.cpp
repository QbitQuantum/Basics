/**
 * Sets current (default) ICU charset
 *
 * If given charset is unavailable, an error is raised
 *
 * @param enc new charset (single string)
 * @return nothing (\code{R_NilValue})
 *
 * @version 0.1-?? (Marek Gagolewski)
 *
 * @version 0.2-1 (Marek Gagolewski)
 *          use StriUcnv; make StriException-friendly
 *
 * @version 0.3-1 (Marek Gagolewski, 2014-11-04)
 *    Issue #112: str_prepare_arg* retvals were not PROTECTed from gc
 */
SEXP stri_enc_set(SEXP enc)
{
   // here, the default encoding may not be requested:
   const char* selected_enc
      = stri__prepare_arg_enc(enc, "enc", false/*no default*/); /* this is R_alloc'ed */

   STRI__ERROR_HANDLER_BEGIN(0)

   StriUcnv uconv_obj(selected_enc);
   // this will generate an error if selected_enc is not supported:
   UConverter* uconv = uconv_obj.getConverter();

   UErrorCode status = U_ZERO_ERROR;
   // get "official" encoding name:
   const char* name = ucnv_getName(uconv, &status);
   STRI__CHECKICUSTATUS_THROW(status, {/* do nothing special on err */})
   ucnv_setDefaultName(name); // set as default

   return R_NilValue;

   STRI__ERROR_HANDLER_END({/* no special action on error */})
}