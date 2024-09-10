Bool
CodeSet_GenericToGenericDb(const char *codeIn,  // IN
                           const char *bufIn,   // IN
                           size_t sizeIn,       // IN
                           const char *codeOut, // IN
                           unsigned int flags,  // IN
                           DynBuf *db)          // IN/OUT
{
#if defined(NO_ICU)
   return CodeSetOld_GenericToGenericDb(codeIn, bufIn, sizeIn, codeOut,
                                        flags, db);
#else
   Bool result = FALSE;
   UErrorCode uerr;
   const char *bufInCur;
   const char *bufInEnd;
   UChar bufPiv[1024];
   UChar *bufPivSource;
   UChar *bufPivTarget;
   UChar *bufPivEnd;
   char *bufOut;
   char *bufOutCur;
   char *bufOutEnd;
   size_t newSize;
   size_t bufOutSize;
   size_t bufOutOffset;
   UConverter *cvin = NULL;
   UConverter *cvout = NULL;
   UConverterToUCallback toUCb;
   UConverterFromUCallback fromUCb;

   ASSERT(codeIn);
   ASSERT(sizeIn == 0 || bufIn);
   ASSERT(codeOut);
   ASSERT(db);
   ASSERT((CSGTG_NORMAL == flags) || (CSGTG_TRANSLIT == flags) ||
          (CSGTG_IGNORE == flags));

   if (dontUseIcu) {
      // fall back
      return CodeSetOld_GenericToGenericDb(codeIn, bufIn, sizeIn, codeOut,
                                           flags, db);
   }

   /*
    * Trivial case.
    */

   if ((0 == sizeIn) || (NULL == bufIn)) {
      result = TRUE;
      goto exit;
   }

   /*
    * Open converters.
    */

   uerr = U_ZERO_ERROR;
   cvin = ucnv_open(codeIn, &uerr);
   if (!cvin) {
      goto exit;
   }

   uerr = U_ZERO_ERROR;
   cvout = ucnv_open(codeOut, &uerr);
   if (!cvout) {
      goto exit;
   }

   /*
    * Set callbacks according to flags.
    */

   switch (flags) {
   case CSGTG_NORMAL:
      toUCb = UCNV_TO_U_CALLBACK_STOP;
      fromUCb = UCNV_FROM_U_CALLBACK_STOP;
      break;

   case CSGTG_TRANSLIT:
      toUCb = UCNV_TO_U_CALLBACK_SUBSTITUTE;
      fromUCb = UCNV_FROM_U_CALLBACK_SUBSTITUTE;
      break;

   case CSGTG_IGNORE:
      toUCb = UCNV_TO_U_CALLBACK_SKIP;
      fromUCb = UCNV_FROM_U_CALLBACK_SKIP;
      break;

   default:
      NOT_IMPLEMENTED();
      break;
   }

   uerr = U_ZERO_ERROR;
   ucnv_setToUCallBack(cvin, toUCb, NULL, NULL, NULL, &uerr);
   if (U_ZERO_ERROR != uerr) {
      goto exit;
   }

   uerr = U_ZERO_ERROR;
   ucnv_setFromUCallBack(cvout, fromUCb, NULL, NULL, NULL, &uerr);
   if (U_ZERO_ERROR != uerr) {
      goto exit;
   }

   /*
    * Convert using ucnv_convertEx().
    * As a starting guess, make the output buffer the same size as
    * the input string (with a fudge constant added in to avoid degen
    * cases).
    */

   bufInCur = bufIn;
   bufInEnd = bufIn + sizeIn;
   newSize = sizeIn + 4;
   if (newSize < sizeIn) {  // Prevent integer overflow
      goto exit;
   }
   bufOutSize = newSize;
   bufOutOffset = 0;
   bufPivSource = bufPiv;
   bufPivTarget = bufPiv;
   bufPivEnd = bufPiv + ARRAYSIZE(bufPiv);

   for (;;) {
      if (!DynBuf_Enlarge(db, bufOutSize)) {
         goto exit;
      }
      bufOut = DynBuf_Get(db);
      bufOutCur = bufOut + bufOutOffset;
      bufOutSize = DynBuf_GetAllocatedSize(db);
      bufOutEnd = bufOut + bufOutSize;

      uerr = U_ZERO_ERROR;
      ucnv_convertEx(cvout, cvin, &bufOutCur, bufOutEnd,
		     &bufInCur, bufInEnd,
		     bufPiv, &bufPivSource, &bufPivTarget, bufPivEnd,
		     FALSE, TRUE, &uerr);

      if (!U_FAILURE(uerr)) {
         /*
          * "This was a triumph. I'm making a note here: HUGE SUCCESS. It's
          * hard to overstate my satisfaction."
          */

         break;
      }

      if (U_BUFFER_OVERFLOW_ERROR != uerr) {
	 // failure
         goto exit;
      }

      /*
       * Our guess at 'bufOutSize' was obviously wrong, just double it.
       * We'll be reallocating bufOut, so will need to recompute bufOutCur
       * based on bufOutOffset.
       */

      newSize = 2 * bufOutSize;

      /*
       * Prevent integer overflow. We can use this form of checking
       * specifically because a multiple by 2 is used. This type of checking
       * does not work in the general case.
       */

      if (newSize < bufOutSize) {
         goto exit;
      }

      bufOutSize = newSize;
      bufOutOffset = bufOutCur - bufOut;
   }

   /*
    * Set final size and return.
    */

   DynBuf_SetSize(db, bufOutCur - bufOut);

   result = TRUE;

  exit:
   if (cvin) {
      ucnv_close(cvin);
   }

   if (cvout) {
      ucnv_close(cvout);
   }

   return result;
#endif
}