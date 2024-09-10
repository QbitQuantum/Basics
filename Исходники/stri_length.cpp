/**
 * Count the number of characters in a string
 *
 * Note that ICU permits only strings of length < 2^31.
 * @param s R character vector
 * @return integer vector
 * @version 0.1 (Marcin Bujarski)
 * @version 0.2 (Marek Gagolewski) Multiple input encoding support
 * @version 0.3 (Marek Gagolewski, 2013-06-16) make StriException-friendly
 */
SEXP stri_length(SEXP str)
{
   str = stri_prepare_arg_string(str, "str");
   R_len_t ns = LENGTH(str);
   SEXP ret;

   UConverter* uconv = NULL;
   bool uconv_8bit = false;
   bool uconv_utf8 = false;

   STRI__ERROR_HANDLER_BEGIN

/* Note: ICU50 permits only int-size strings in U8_NEXT and U8_FWD_1 */
#define STRI_LENGTH_CALCULATE_UTF8  \
   const char* qc = CHAR(q);        \
   R_len_t j = 0;                   \
   for (R_len_t i = 0; i < nq; j++) \
      U8_FWD_1(qc, i, nq);          \
   retint[k] = j;

   PROTECT(ret = Rf_allocVector(INTSXP, ns));
   int* retint = INTEGER(ret);
   for (R_len_t k = 0; k < ns; k++) {
      SEXP q = STRING_ELT(str, k);
      if (q == NA_STRING)
         retint[k] = NA_INTEGER;
      else {
         R_len_t nq = LENGTH(q);  // O(1) - stored by R

         // We trust (is that a wise assumption?)
         // R encoding marks; However, it there is no mark,
         // the string may have any encoding (ascii, latin1, utf8, native)
         if (IS_ASCII(q) || IS_LATIN1(q))
            retint[k] = nq;
         else if (IS_BYTES(q))
            throw StriException(MSG__BYTESENC);
         else if (IS_UTF8(q)) {
            STRI_LENGTH_CALCULATE_UTF8
         }
         else { // Any encoding - detection needed
//            UTF-8 strings can be fairly reliably recognized as such by a
//            simple algorithm, i.e., the probability that a string of
//            characters in any other encoding appears as valid UTF-8 is low,
//            diminishing with increasing string length.
//            We have two possibilities here:
//            1. Auto detect encoding: Is this ASCII or UTF-8? If not => use Native
//                This won't work correctly in some cases.
//                e.g. (c4,85) represents ("Polish a with ogonek") in UTF-8
//                and ("A umlaut", "Ellipsis") in WINDOWS-1250
//            2. Assume it's Native; this assumes the user working in an 8-bit environment
//                would convert strings to UTF-8 manually if needed - I think is's
//                a more reasonable approach (Native --> input via keyboard)

            if (!uconv) { // open ucnv on demand
               uconv = stri__ucnv_open((const char*)NULL); // native decoder
               if (!uconv) {
                  retint[k] = NA_INTEGER;
                  continue;
               }
               uconv_8bit = ((int)ucnv_getMaxCharSize(uconv) == 1);
               if (!uconv_8bit) {
                  UErrorCode err = U_ZERO_ERROR;
                  const char* name = ucnv_getName(uconv, &err);
                  if (U_FAILURE(err))
                     throw StriException("could not query default converter");
                  uconv_utf8 = !strncmp("UTF-8", name, 5);
               }
            }

            if (uconv_8bit) {
               retint[k] = nq; // it's an 8-bit encoding :-)
            }
            else if (uconv_utf8) { // it's UTF-8
               STRI_LENGTH_CALCULATE_UTF8
            }
            else {  // native encoding which is neither 8-bit, nor UTF-8 (e.g. 'Big5')
               UErrorCode err = U_ZERO_ERROR;
               const char* source = CHAR(q);
               const char* sourceLimit = source + nq;
               R_len_t j;
               for (j = 0; source != sourceLimit; j++) {
                  if (U_FAILURE(err)) break; // error from previous iteration
                  // iterate through each native-encoded character:
                  ucnv_getNextUChar(uconv, &source, sourceLimit, &err);
               }
               if (U_FAILURE(err)) {  // error from last iteration
                  Rf_warning("error determining length for native, neither 8-bit- nor UTF-8-encoded string.");
                  retint[k] = NA_INTEGER;
               }
               else
                  retint[k] = j; // all right, we got it!
            }
         }
      }