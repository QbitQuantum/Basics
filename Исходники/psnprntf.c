int pvsnfmt_double(pvsnfmt_vars *info, double d) {
    char *digits;
    int sign = 0;
    int dec;
    double value = d;

    int len;
    int pad = 0;
    //int signwidth = 0;
    int totallen;
    char signchar = 0;
    int leadingzeros = 0;

    int printdigits; /* temporary var used in different contexts */

    int flags = info->flags;
    int width = info->width;
    const char fmt = *(info->fmt);
    int precision = info->precision;

    /* Check for special values first */
    char *special = 0;
    if(ISSNAN(value)) {
        special = "NaN";
    }
    else if(ISQNAN(value)) {
        special = "NaN";
    }
    else if(ISINF(value)) {
        if(value < 0) {
            sign = 1;
        }
        special = "Inf";
    }

    if(special) {
        totallen = len = strlen(special);

        /* Sign (this is silly for NaN but conforming to printf */
        if(flags & (FLAG_SIGNED | FLAG_SIGN_PAD) || sign) {
            if(sign) {
                signchar = '-';
            }
            else if(flags & FLAG_SIGN_PAD) {
                signchar = ' ';
            }
            else {
                signchar = '+';
            }
            totallen++;
        }

        /* Padding */
        if(totallen < width) {
            pad = width - totallen;
        }
        else {
            pad = 0;
        }

        totallen += pad ;

        // haleyjd 05/07/08: this was forgotten!
        if(info->nmax <= 1) {
            return totallen;
        }


        /* Sign now if zeropad */
        if(flags & FLAG_ZERO_PAD && signchar) {
            if(info->nmax > 1) {
                *(info->pinsertion) = signchar;
                info->pinsertion += 1;
                info->nmax -= 1;
            }
        }

        /* Right align */
        if(!(flags & FLAG_LEFT_ALIGN)) {
            if(info->nmax <= 1) {
                pad  = 0;
            }
            else if((int) info->nmax - 1 < pad) {
                pad  = info->nmax - 1;
            }

            if(flags & FLAG_ZERO_PAD) {
                memset(info->pinsertion, '0', pad);
            }
            else {
                memset(info->pinsertion, ' ', pad);
            }
            info->pinsertion += pad ;
            info->nmax -= pad ;
        }

        /* Sign now if not zeropad */
        if(!(flags & FLAG_ZERO_PAD) && signchar) {
            if(info->nmax > 1) {
                *(info->pinsertion) = signchar;
                info->pinsertion += 1;
                info->nmax -= 1;
            }
        }

        if(info->nmax <= 0) {
            len = 0;
        }
        else if((int) info->nmax - 1 < len) {
            len = info->nmax - 1;
        }
        memcpy(info->pinsertion, special, len);
        info->pinsertion += len;
        info->nmax -= len;

        /* Left align */
        if(flags & FLAG_LEFT_ALIGN) {
            if(info->nmax <= 1) {
                pad  = 0;
            }
            else if((int) info->nmax - 1 < pad) {
                pad  = info->nmax - 1;
            }

            memset(info->pinsertion, ' ', pad);
            info->pinsertion += pad ;
            info->nmax -= pad ;
        }

        return totallen;
    }

    if(fmt == 'f') {
        if(precision == UNKNOWN_PRECISION) {
            precision = 6;
        }

        digits = FCVT(value, precision, &dec, &sign);
        len = strlen(digits);

        if(dec > 0) {
            totallen = dec;
        }
        else {
            totallen = 0;
        }

        /* plus 1 for decimal place */
        if(dec <= 0) {
            totallen += 2;    /* and trailing ".0" */
        }
        else if(precision > 0 || flags & FLAG_HASH) {
            totallen += 1;
        }


        /* Determine sign width (0 or 1) */
        if(flags & (FLAG_SIGNED | FLAG_SIGN_PAD) || sign) {
            if(sign) {
                signchar = '-';
            }
            else if(flags & FLAG_SIGN_PAD) {
                signchar = ' ';
            }
            else {
                signchar = '+';
            }
            totallen++;
        }

        /* Determine if leading zeros required */
        if(dec <= 0) {
            leadingzeros = 1 - dec; /* add one for zero before decimal point (0.) */
        }

        if(leadingzeros - 1 > precision) {
            totallen += precision;
        }
        else if(len - dec > 0) {
            totallen += precision;
        }
        else {
            totallen += leadingzeros;
        }

        /* Determine padding width */
        if(totallen < width) {
            pad = width - totallen;
        }

        totallen += pad;
        if(info->nmax <= 1) {
            return totallen;
        }

        /* Now that the length has been calculated, print as much of it
         * as possible into the buffer
         */

        /* Print sign now if padding with zeros */
        if(flags & FLAG_ZERO_PAD && signchar != 0) {
            if(info->nmax > 1) {
                *(info->pinsertion) = signchar;
                info->pinsertion += 1;
                info->nmax -= 1;
            }
        }

        /* Print width padding if right-aligned */
        if(!(flags & FLAG_LEFT_ALIGN)) {
            if(info->nmax <= 1) {
                pad = 0;
            }
            else if((int) info->nmax - 1 < pad) {
                pad = info->nmax - 1;
            }

            if(flags & FLAG_ZERO_PAD) {
                memset(info->pinsertion, '0', pad);
            }
            else {
                memset(info->pinsertion, ' ', pad);
            }

            info->pinsertion += pad;
            info->nmax -= pad;
        }

        /* Print sign now if padding was spaces */
        if(!(flags & FLAG_ZERO_PAD) && signchar != 0) {
            *(info->pinsertion) = signchar;
            info->pinsertion += 1;
            info->nmax -= 1;
        }

        /* Print leading zeros */
        if(leadingzeros) {
            /* Print "0.", then leadingzeros - 1 */
            if(info->nmax > 1) {
                *(info->pinsertion) = '0';
                info->pinsertion += 1;
                info->nmax -= 1;
            }

            if(precision > 0 || flags & FLAG_HASH) {
                if(info->nmax > 1) {
                    *(info->pinsertion) = '.';
                    info->pinsertion += 1;
                    info->nmax -= 1;
                }
            }

            /* WARNING not rounding here!
             * i.e. printf(".3f", 0.0007) gives "0.000" not "0.001"
             *
             * This whole function could do with a rewrite...
             */
            if(leadingzeros - 1 > precision) {
                leadingzeros = precision + 1;
                len = 0;
            }
            /* END WARNING */

            precision -= leadingzeros - 1;

            if(info->nmax <= 1) {
                leadingzeros = 0;
            }
            else if((int) info->nmax /* - 1 */ < leadingzeros /* -1 */) {
                leadingzeros = info->nmax;    /* -1 */
            }

            leadingzeros--;
            memset(info->pinsertion, '0', leadingzeros);
            info->pinsertion += leadingzeros;
            info->nmax -= leadingzeros;
        }

        /* Print digits before decimal place */
        if(dec > 0) {
            if(info->nmax <= 1) {
                printdigits = 0;
            }
            else if((int) info->nmax - 1 < dec) {
                printdigits = info->nmax - 1;
            }
            else {
                printdigits = dec;
            }

            memcpy(info->pinsertion, digits, printdigits);
            info->pinsertion += printdigits;
            info->nmax -= printdigits;

            if(precision > 0 || flags & FLAG_HASH) {
                /* Print decimal place */
                if(info->nmax > 1) {
                    *(info->pinsertion) = '.';
                    info->pinsertion += 1;
                    info->nmax -= 1;
                }

                /* Print trailing zero if no precision but hash given */
                if(precision == 0 && info->nmax > 1) {
                    *(info->pinsertion) = '0';
                    info->pinsertion += 1;
                    info->nmax -= 1;
                }
            }

            /* Bypass the digits we've already printed */
            len -= dec;
            digits += dec;
        }

        /* Print digits after decimal place */
        if(len > precision) {
            len = precision;
        }

        if(info->nmax <= 1) {
            printdigits = 0;
        }
        else if((int) info->nmax - 1 < len) {
            printdigits = info->nmax - 1;
        }
        else {
            printdigits = len;
        }

        memcpy(info->pinsertion, digits, printdigits);
        info->pinsertion += printdigits;
        info->nmax -= printdigits;

        /* Print left-aligned pad */
        if(flags & FLAG_LEFT_ALIGN) {
            if(info->nmax <= 1) {
                pad = 0;
            }
            else if((int) info->nmax - 1 < pad) {
                pad = info->nmax - 1;
            }

            memset(info->pinsertion, ' ', pad);
            info->pinsertion += pad;
            info->nmax -= pad;
        }
        return totallen;
    }

    return 0;
}