/*
 * ctpl_input_stream_read_number_internal:
 * @type: which kind of number match (float, int or both)
 * 
 * see ctpl_input_stream_read_number()
 */
static gboolean
ctpl_input_stream_read_number_internal (CtplInputStream *stream,
                                        gint             type,
                                        CtplValue       *value,
                                        GError         **error)
{
  gboolean  have_mantissa       = FALSE;
  gboolean  have_exponent       = FALSE;
  gboolean  have_exponent_delim = FALSE;
  gboolean  have_sign           = FALSE;
  gboolean  have_dot            = FALSE;
  GString  *gstring;
  GError   *err                 = NULL;
  gboolean  in_number           = TRUE;
  gint      base                = 10;
  
  #define ISSIGN(c)   ((c) == '+' || (c) == '-')
  #define ISDIGIT(c)  ((c) >= '0' && (c) <= '9')
  #define ISBDIGIT(c) ((c) == '0' || (c) == '1')
  #define ISODIGIT(c) ((c) >= '0' && (c) <= '7')
  #define ISXDIGIT(c) (ISDIGIT (c) || \
                       ((c) >= 'a' && (c) <= 'f') || \
                       ((c) >= 'A' && (c) <= 'F'))
  
  gstring = g_string_new ("");
  while (in_number && ! err) {
    gchar   buf[3];
    gssize  buf_len;
    
    buf_len = ctpl_input_stream_peek (stream, buf, sizeof (buf), &err);
    if (! err) {
      gchar c = (buf_len > 0) ? buf[0] : CTPL_EOF;
      
      switch (c) {
        case '.':
          if (! have_dot && ! have_exponent_delim && (type & READ_FLOAT)) {
            g_string_append_c (gstring, c);
            have_dot = TRUE;
            type &= READ_FLOAT;
          } else {
            in_number = FALSE;
          }
          break;
        
        case '+':
        case '-':
          if (! have_sign && (! have_mantissa ||
                              (have_exponent_delim && ! have_exponent)) &&
              /* ISDIGIT() is fine here even though we probably don't know the
               * base yet because the default base is 10 and the exponent or
               * power are also in base 10 */
              buf_len > 1 && ISDIGIT (buf[1])) {
            g_string_append_c (gstring, c);
            have_sign = TRUE;
          } else {
            in_number = FALSE;
          }
          break;
        
        case 'e':
        case 'E':
          if (base < 15) {
            if (have_mantissa && ! have_exponent_delim &&
                (type & READ_FLOAT) && base == 10 &&
                ((buf_len > 1 && ISDIGIT (buf[1])) ||
                 (buf_len > 2 && ISSIGN (buf[1]) && ISDIGIT (buf[2])))) {
              have_exponent_delim = TRUE;
              have_sign = FALSE;
              type &= READ_FLOAT;
              g_string_append_c (gstring, 'e');
            } else {
              in_number = FALSE;
            }
            break;
          }
          /* Fallthrough */
        case 'b':
        case 'B':
        case 'a':
        case 'A':
        case 'c':
        case 'C':
        case 'd':
        case 'D':
        case 'f':
        case 'F':
          if (base < 16 || have_exponent_delim /* exponent is decimal */) {
            in_number = FALSE;
            break;
          }
          /* Fallthrough */
        case '8':
        case '9':
          if (base < 10) {
            in_number = FALSE;
            break;
          }
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
          if (base < 8) {
            in_number = FALSE;
            break;
          }
          /* Fallthrough */
        case '0':
          if (! have_mantissa && buf_len > 2) {
            gboolean is_start = TRUE;
            
            if ((type & READ_INT) &&
                (buf[1] == 'b' || buf[1] == 'B') && ISBDIGIT (buf[2])) {
              type &= READ_INT;
              base = 2;
            } else if ((type & READ_INT) &&
                       (buf[1] == 'o' || buf[1] == 'O') && ISODIGIT (buf[2])) {
              type &= READ_INT;
              base = 8;
            } else if ((buf[1] == 'x' || buf[1] == 'X') && ISXDIGIT (buf[2])) {
              /* needed for floating-points */
              g_string_append_c (gstring, c);
              g_string_append_c (gstring, buf[1]);
              base = 16;
            } else {
              is_start = FALSE;
            }
            if (is_start) {
              /* eat the character we just handled. no need to check the error
               * since the data is already cached -- so no error can happen */
              ctpl_input_stream_get_c (stream, NULL);
              break;
            }
          }
          /* Fallthrough */
        case '1':
          g_string_append_c (gstring, c);
          if (! have_exponent_delim) {
            have_mantissa = TRUE;
          } else {
            have_exponent = TRUE;
          }
          break;
        
        case 'p':
        case 'P':
          if (have_mantissa && ! have_exponent_delim &&
              (type & READ_FLOAT) && base == 16 &&
              ((buf_len > 1 && ISDIGIT (buf[1])) ||
               (buf_len > 2 && ISSIGN (buf[1]) && ISDIGIT (buf[2])))) {
            have_exponent_delim = TRUE;
            have_sign = FALSE;
            type &= READ_FLOAT;
            g_string_append_c (gstring, 'p');
          } else {
            in_number = FALSE;
          }
          break;
        
        default:
          in_number = FALSE;
      }
      if (in_number) {
        ctpl_input_stream_get_c (stream, &err); /* eat character */
      }
    }
  }
  if (! err) {
    if (! have_mantissa) {
      ctpl_input_stream_set_error (stream, &err, CTPL_IO_ERROR,
                                   CTPL_IO_ERROR_INVALID_NUMBER,
                                   "Missing mantissa in numeric constant");
    } else {
      gchar  *nptr = gstring->str;
      gchar  *endptr;
      gdouble dblval = 0.0;
      glong   longval = 0;
      gint    errno_save = errno;
      
      errno = 0;
      if (type & READ_INT) {
        longval = strtol (nptr, &endptr, base);
      } else {
        dblval = g_ascii_strtod (nptr, &endptr);
      }
      if (! endptr || *endptr != 0) {
        ctpl_input_stream_set_error (stream, &err, CTPL_IO_ERROR,
                                     CTPL_IO_ERROR_INVALID_NUMBER,
                                     "Invalid base %d numeric constant \"%s\"",
                                     base, nptr);
      } else if (errno == ERANGE) {
        ctpl_input_stream_set_error (stream, &err, CTPL_IO_ERROR,
                                     CTPL_IO_ERROR_RANGE,
                                     "Overflow in numeric constant conversion");
      } else {
        if (type & READ_INT) {
          ctpl_value_set_int (value, longval);
        } else {
          ctpl_value_set_float (value, dblval);
        }
      }
      errno = errno_save;
    }
  }
  if (err) {
    g_propagate_error (error, err);
  }
  g_string_free (gstring, TRUE);
  
  #undef ISSIGN
  #undef ISDIGIT
  #undef ISBDIGIT
  #undef ISODIGIT
  #undef ISXDIGIT
  
  return ! err;
}