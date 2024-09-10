/*
 * This routine takes the current input command line "line" and
 * searches for any possible macro declarations.  These are
 * present in the line as "$#" where '#' is a single digit
 * number from 0 to 9.  If a macro argument is found, it is
 * either substituted with the value on the same line as the
 * macro call (if it was present) or silently replaced with an
 * empty string.
 *
 * The user order of macro substitutions runs from the 1st to 9th
 * and then the 0th value.  Internally, the array runs from 0 to 9.
 * Thus, when a macro argument is found, it's integer value
 * will need to be shifted to account for the difference.  This
 * is done with a simple mod operation:
 * Internal order is: $0, $1, ..., $8, $9;
 * User sees order as: $1, $2, ..., $9, $0.
 *
 * This routine uses the input string "string" to copy the argument
 * substituted line into, so make sure it is large enough to hold
 * everything!  Also, this function returns a pointer to "string"
 * in the same fashion as strcpy().  There is no check to make sure
 * that the size of macarg[] is sufficient to cover all input
 * arguments.  This is a quiet assumption.  Also, macarg should
 * be declared "const char *macarg[]" but because it is a pointer to
 * an open array, I have trouble doing this.
 *
 */
static char *domacsubs(char *string, const char *line, char *macarg[])
{
    register int j, k;
    register char *s, *ptr, *arg;

    if (Strchr(line, '$') == (char *)NULL) {   /* No arguments to sub. */
      (void)Strcpy(string, line);     /* Simply return a copy of line. */
    } else {
      s = (char *)line;
      ptr = string;
      while (*s) {                      /* Parse through input string. */
        if (*s != '$') {                /* If not special character... */
          *ptr++ = *s++;                /* ...copy regular characters; */
        } else {                /* otherwise, get the argument number. */
          j = (*(s+1)) - '0';      /* Convert next char to an integer. */
          if ((j < 0) || (j > 9)) {       /* Not a macro substitution. */
            *ptr++ = *s++;                      /* Just a regular '$'. */
          } else {
#if 1
            if ( *(s+2) ) {             /* see if next char */
                k = *(s+2) - '0';       /* is a digit */
                if (k>=0 && k<=9) {     /* and if so */
                    j = j*10 + k;       /* allow two digit parameters */
                    k = 1;              /* remember we had 2 digits */
                } else
                    k = 0;
            } else 
                k = 0;
            if (j >= MAXARG) {
                wipoutput(stderr, "$%d too large a reference\n",j);
                return NULL;
            }
            j = (j==0 ? 9 : j-1);
#else
            j = (j + 9) % 10;       /* This is where order is shifted. */
            k = 0;
#endif
            /*
             *  If the macro argument is not present, then quietly
             *  skip over the request.  If it is present (macarg[j]
             *  != Null), then substitute the argument value now.
             */
            if (macarg[j] != Null) {     /* If a value exists, then... */
              arg = (char *)macarg[j];  /* ...substitute the argument. */
              while (*arg)
                *ptr++ = *arg++;
            }
            s++;                                 /* Skip over the '$'. */
            s++;                                 /* Skip over the '#'. */
            if (k) s++;                     /* and one more if needed. */
          }                           /* If (0 <= j <= 9) conditional. */
        }                               /* If (*s != '$') conditional. */
      }                                            /* While (*s) loop. */
      *ptr = Null;                   /* Make sure it ends with a Null. */
    }                               /* if (!Strchr(line, '$')) branch. */

    return(string);
}