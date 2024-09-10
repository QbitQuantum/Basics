int
mpc_inp_str (mpc_ptr rop, FILE *stream, size_t *read, int base,
mpc_rnd_t rnd_mode)
{
   size_t white, nread = 0;
   int inex = -1;
   int c;
   char *str;

   if (stream == NULL)
      stream = stdin;

   white = skip_whitespace (stream);
   c = getc (stream);
   if (c != EOF) {
     if (c == '(') {
       char *real_str;
       char *imag_str;
       size_t n;
       int ret;

       nread++; /* the opening parenthesis */
       white = skip_whitespace (stream);
       real_str = extract_string (stream);
       nread += strlen(real_str);

       c = getc (stream);
       if (!isspace ((unsigned int) c)) {
         if (c != EOF)
           ungetc (c, stream);
         mpc_free_str (real_str);
         goto error;
       }
       else
         ungetc (c, stream);

       white += skip_whitespace (stream);
       imag_str = extract_string (stream);
       nread += strlen (imag_str);

       str = mpc_alloc_str (nread + 2);
       ret = sprintf (str, "(%s %s", real_str, imag_str);
       MPC_ASSERT (ret >= 0);
       n = (size_t) ret;
       MPC_ASSERT (n == nread + 1);
       mpc_free_str (real_str);
       mpc_free_str (imag_str);

       white += skip_whitespace (stream);
       c = getc (stream);
       if (c == ')') {
         str = mpc_realloc_str (str, nread +2, nread + 3);
         str [nread+1] = (char) c;
         str [nread+2] = '\0';
         nread++;
       }
       else if (c != EOF)
         ungetc (c, stream);
     }
     else {
       if (c != EOF)
         ungetc (c, stream);
       str = extract_string (stream);
       nread += strlen (str);
     }

     inex = mpc_set_str (rop, str, base, rnd_mode);

     mpc_free_str (str);
   }

error:
   if (inex == -1) {
      mpfr_set_nan (mpc_realref(rop));
      mpfr_set_nan (mpc_imagref(rop));
   }
   if (read != NULL)
     *read = white + nread;
   return inex;
}