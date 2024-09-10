static int
format_complex_internal(PyObject *value,
                        const InternalFormatSpec *format,
                        _PyUnicodeWriter *writer)
{
    double re;
    double im;
    char *re_buf = NULL;       /* buffer returned from PyOS_double_to_string */
    char *im_buf = NULL;       /* buffer returned from PyOS_double_to_string */

    InternalFormatSpec tmp_format = *format;
    Py_ssize_t n_re_digits;
    Py_ssize_t n_im_digits;
    Py_ssize_t n_re_remainder;
    Py_ssize_t n_im_remainder;
    Py_ssize_t n_re_total;
    Py_ssize_t n_im_total;
    int re_has_decimal;
    int im_has_decimal;
    int precision, default_precision = 6;
    Py_UCS4 type = format->type;
    Py_ssize_t i_re;
    Py_ssize_t i_im;
    NumberFieldWidths re_spec;
    NumberFieldWidths im_spec;
    int flags = 0;
    int result = -1;
    Py_UCS4 maxchar = 127;
    enum PyUnicode_Kind rkind;
    void *rdata;
    Py_UCS4 re_sign_char = '\0';
    Py_UCS4 im_sign_char = '\0';
    int re_float_type; /* Used to see if we have a nan, inf, or regular float. */
    int im_float_type;
    int add_parens = 0;
    int skip_re = 0;
    Py_ssize_t lpad;
    Py_ssize_t rpad;
    Py_ssize_t total;
    PyObject *re_unicode_tmp = NULL;
    PyObject *im_unicode_tmp = NULL;

    /* Locale settings, either from the actual locale or
       from a hard-code pseudo-locale */
    LocaleInfo locale = STATIC_LOCALE_INFO_INIT;

    if (format->precision > INT_MAX) {
        PyErr_SetString(PyExc_ValueError, "precision too big");
        goto done;
    }
    precision = (int)format->precision;

    /* Zero padding is not allowed. */
    if (format->fill_char == '0') {
        PyErr_SetString(PyExc_ValueError,
                        "Zero padding is not allowed in complex format "
                        "specifier");
        goto done;
    }

    /* Neither is '=' alignment . */
    if (format->align == '=') {
        PyErr_SetString(PyExc_ValueError,
                        "'=' alignment flag is not allowed in complex format "
                        "specifier");
        goto done;
    }

    re = PyComplex_RealAsDouble(value);
    if (re == -1.0 && PyErr_Occurred())
        goto done;
    im = PyComplex_ImagAsDouble(value);
    if (im == -1.0 && PyErr_Occurred())
        goto done;

    if (format->alternate)
        flags |= Py_DTSF_ALT;

    if (type == '\0') {
        /* Omitted type specifier. Should be like str(self). */
        type = 'r';
        default_precision = 0;
        if (re == 0.0 && copysign(1.0, re) == 1.0)
            skip_re = 1;
        else
            add_parens = 1;
    }

    if (type == 'n')
        /* 'n' is the same as 'g', except for the locale used to
           format the result. We take care of that later. */
        type = 'g';

    if (precision < 0)
        precision = default_precision;
    else if (type == 'r')
        type = 'g';

    /* Cast "type", because if we're in unicode we need to pass a
       8-bit char. This is safe, because we've restricted what "type"
       can be. */
    re_buf = PyOS_double_to_string(re, (char)type, precision, flags,
                                   &re_float_type);
    if (re_buf == NULL)
        goto done;
    im_buf = PyOS_double_to_string(im, (char)type, precision, flags,
                                   &im_float_type);
    if (im_buf == NULL)
        goto done;

    n_re_digits = strlen(re_buf);
    n_im_digits = strlen(im_buf);

    /* Since there is no unicode version of PyOS_double_to_string,
       just use the 8 bit version and then convert to unicode. */
    re_unicode_tmp = _PyUnicode_FromASCII(re_buf, n_re_digits);
    if (re_unicode_tmp == NULL)
        goto done;
    i_re = 0;

    im_unicode_tmp = _PyUnicode_FromASCII(im_buf, n_im_digits);
    if (im_unicode_tmp == NULL)
        goto done;
    i_im = 0;

    /* Is a sign character present in the output?  If so, remember it
       and skip it */
    if (PyUnicode_READ_CHAR(re_unicode_tmp, i_re) == '-') {
        re_sign_char = '-';
        ++i_re;
        --n_re_digits;
    }
    if (PyUnicode_READ_CHAR(im_unicode_tmp, i_im) == '-') {
        im_sign_char = '-';
        ++i_im;
        --n_im_digits;
    }

    /* Determine if we have any "remainder" (after the digits, might include
       decimal or exponent or both (or neither)) */
    parse_number(re_unicode_tmp, i_re, i_re + n_re_digits,
                 &n_re_remainder, &re_has_decimal);
    parse_number(im_unicode_tmp, i_im, i_im + n_im_digits,
                 &n_im_remainder, &im_has_decimal);

    /* Determine the grouping, separator, and decimal point, if any. */
    if (get_locale_info(format->type == 'n' ? LT_CURRENT_LOCALE :
                        (format->thousands_separators ?
                         LT_DEFAULT_LOCALE :
                         LT_NO_LOCALE),
                        &locale) == -1)
        goto done;

    /* Turn off any padding. We'll do it later after we've composed
       the numbers without padding. */
    tmp_format.fill_char = '\0';
    tmp_format.align = '<';
    tmp_format.width = -1;

    /* Calculate how much memory we'll need. */
    n_re_total = calc_number_widths(&re_spec, 0, re_sign_char, re_unicode_tmp,
                                    i_re, i_re + n_re_digits, n_re_remainder,
                                    re_has_decimal, &locale, &tmp_format,
                                    &maxchar);

    /* Same formatting, but always include a sign, unless the real part is
     * going to be omitted, in which case we use whatever sign convention was
     * requested by the original format. */
    if (!skip_re)
        tmp_format.sign = '+';
    n_im_total = calc_number_widths(&im_spec, 0, im_sign_char, im_unicode_tmp,
                                    i_im, i_im + n_im_digits, n_im_remainder,
                                    im_has_decimal, &locale, &tmp_format,
                                    &maxchar);

    if (skip_re)
        n_re_total = 0;

    /* Add 1 for the 'j', and optionally 2 for parens. */
    calc_padding(n_re_total + n_im_total + 1 + add_parens * 2,
                 format->width, format->align, &lpad, &rpad, &total);

    if (lpad || rpad)
        maxchar = Py_MAX(maxchar, format->fill_char);

    if (_PyUnicodeWriter_Prepare(writer, total, maxchar) == -1)
        goto done;
    rkind = writer->kind;
    rdata = writer->data;

    /* Populate the memory. First, the padding. */
    result = fill_padding(writer,
                          n_re_total + n_im_total + 1 + add_parens * 2,
                          format->fill_char, lpad, rpad);
    if (result == -1)
        goto done;

    if (add_parens) {
        PyUnicode_WRITE(rkind, rdata, writer->pos, '(');
        writer->pos++;
    }

    if (!skip_re) {
        result = fill_number(writer, &re_spec,
                             re_unicode_tmp, i_re, i_re + n_re_digits,
                             NULL, 0,
                             0,
                             &locale, 0);
        if (result == -1)
            goto done;
    }
    result = fill_number(writer, &im_spec,
                         im_unicode_tmp, i_im, i_im + n_im_digits,
                         NULL, 0,
                         0,
                         &locale, 0);
    if (result == -1)
        goto done;
    PyUnicode_WRITE(rkind, rdata, writer->pos, 'j');
    writer->pos++;

    if (add_parens) {
        PyUnicode_WRITE(rkind, rdata, writer->pos, ')');
        writer->pos++;
    }

    writer->pos += rpad;

done:
    PyMem_Free(re_buf);
    PyMem_Free(im_buf);
    Py_XDECREF(re_unicode_tmp);
    Py_XDECREF(im_unicode_tmp);
    free_locale_info(&locale);
    return result;
}