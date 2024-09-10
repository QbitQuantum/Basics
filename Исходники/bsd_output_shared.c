char *
dtoa(double d,       // IN
     int mode,       // IN
     int prec,       // IN
     int *expOut,    // OUT
     int *sign,      // OUT
     char **strEnd)  // OUT
{
   char *str = NULL;
   int dec;

#if defined(_WIN32)
   if (2 == mode) {
      str = malloc(_CVTBUFSIZE);
      if (str) {
         if (_ecvt_s(str, _CVTBUFSIZE, d, prec, &dec, sign)) {
            free(str);
            str = NULL;
         }
      }
   } else {
      ASSERT(3 == mode);
      str = malloc(_CVTBUFSIZE);
      if (str) {
         if (_fcvt_s(str, _CVTBUFSIZE, d, prec, &dec, sign)) {
            free(str);
            str = NULL;
         }
      }

      /*
       * When the value is not zero but rounds to zero at prec digits,
       * the Windows fcvt() sometimes returns the empty string and
       * a negative dec that goes too far (as in -dec > prec).
       * For example, converting 0.001 with prec 1 results in
       * the empty string and dec -2.  (See bug 253674.)
       *
       * We just clamp dec to -prec when this happens.
       *
       * While this may appear to be a safe and good thing to
       * do in general.  It really only works when the result is
       * all zeros or empty.  Since checking for all zeros is
       * expensive, we only check for empty string, which works
       * for this bug.
       */

      if (str && *str == '\0' && dec < 0 && dec < -prec) {
	 dec = -prec;
      }
   }
#else // _WIN32
   static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

   if (2 == mode) {
      pthread_mutex_lock(&mutex);
      str = strdup(ecvt(d, prec, &dec, sign));
      pthread_mutex_unlock(&mutex);
   } else {
      ASSERT(3 == mode);

#ifdef __APPLE__
      /*
       * The Mac fcvt() returns "" when prec is 0, so we have to
       * compensate.  See bug 233530.
       * While it is conceivable that fcvt(round(d), 1) can return
       * a string that doesn't end in 0, it doesn't seem to happen
       * in practice (on the Mac).  The problematic case that we
       * want to avoid is a last digit greater than 4, which requires
       * rounding up, which we don't want to do, which is why we're
       * doing the rounding on the number instead of after fcvt()
       * in the first place.
       * -- edward
       */

      if (prec == 0) {
	 size_t l;
         pthread_mutex_lock(&mutex);
	 str = strdup(fcvt(round(d), 1, &dec, sign));
         pthread_mutex_unlock(&mutex);
	 if (str) {
	    l = strlen(str);
	    ASSERT(l > 0);
	    l--;
	    ASSERT(str[l] == '0');
	    str[l] = '\0';
         }
      } else 
#endif // __APPLE__
      {
         pthread_mutex_lock(&mutex);
         str = strdup(fcvt(d, prec, &dec, sign));
         pthread_mutex_unlock(&mutex);
      }
   }
#endif // _WIN32

   if (str) {
      *strEnd = str + strlen(str);

      /* strip trailing zeroes */
      while ((*strEnd > str) && ('0' == *((*strEnd) - 1))) {
         (*strEnd)--;
      }

      *expOut = dec;
   }

   return str;
}