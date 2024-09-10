unsigned int
parse_memory_size(const char *sizeName, /*  "initial heap" or "maximum heap" or
                                            "initial stack" or "maximum stack"
                                        */
                  const char *sizeFlag, // "-Xms" or "-Xmx" or
                                        // "-Xss" or "-Xsg" or "-Xsx"
                  const char *defaultFactor, // We now always default to bytes ("")
                  unsigned roundTo,  // Round to PAGE_SIZE_BYTES or to 4.
                  const char *token /* e.g., "-Xms200M" or "-Xms200" */,
                  const char *subtoken /* e.g., "200M" or "200" */,
                  bool *fastExit)
{
    errno = 0;
    long double userNum;
    char *endp;                 /* Should be const char *, but if we do that,
                                   then the C++ compiler complains about the
                                   prototype for strtold() or strtod().   This
                                   is probably a bug in the specification
                                   of the prototype. */
    userNum = strtold(subtoken, &endp);
    if (endp == subtoken) {
        fprintf(SysTraceFile, "%s: \"%s\": -X%s must be followed by a number.\n", Me, token, sizeFlag);
        *fastExit = true;
    }

    // First, set the factor appropriately, and make sure there aren't extra
    // characters at the end of the line.
    const char *factorStr = defaultFactor;
    long double factor = 0.0;   // 0.0 is a sentinel meaning Unset

    if (*endp == '\0') {
        /* no suffix.  Along with the Sun JVM, we now assume Bytes by
           default. (This is a change from  previous Jikes RVM behaviour.)  */
        factor = 1.0;
    } else if (strequal(endp, "pages") ) {
        factor = BYTES_IN_PAGE;
    /* Handle constructs like "M" and "K" */
    } else if ( endp[1] == '\0' ) {
        factorStr = endp;
    } else {
        fprintf(SysTraceFile, "%s: \"%s\": I don't recognize \"%s\" as a"
                " unit of memory size\n", Me, token, endp);
        *fastExit = true;
    }

    if (! *fastExit && factor == 0.0) {
        char e = *factorStr;
        if (e == 'g' || e == 'G') factor = 1024.0 * 1024.0 * 1024.0;
        else if (e == 'm' || e == 'M') factor = 1024.0 * 1024.0;
        else if (e == 'k' || e == 'K') factor = 1024.0;
        else if (e == '\0') factor = 1.0;
        else {
            fprintf(SysTraceFile, "%s: \"%s\": I don't recognize \"%s\" as a"
                    " unit of memory size\n", Me, token, factorStr);
            *fastExit = true;
        }
    }

    // Note: on underflow, strtod() returns 0.
    if (!*fastExit) {
        if (userNum <= 0.0) {
            fprintf(SysTraceFile,
                    "%s: You may not specify a %s %s;\n",
                    Me, userNum < 0.0 ? "negative" : "zero", sizeName);
            fprintf(SysTraceFile, "\tit just doesn't make any sense.\n");
            *fastExit = true;
        }
    }

    if (!*fastExit) {
        if ( errno == ERANGE || userNum > (((long double) (UINT_MAX - roundTo))/factor) )
        {
            fprintf(SysTraceFile, "%s: \"%s\": out of range to represent internally\n", Me, subtoken);
            *fastExit = true;
        }
    }

    if (*fastExit) {
        fprintf(SysTraceFile, "\tPlease specify %s as follows:\n", sizeName);
        fprintf(SysTraceFile, "\t    in bytes, using \"-X%s<positive number>\",\n", sizeFlag);
        fprintf(SysTraceFile, "\tor, in kilobytes, using \"-X%s<positive number>K\",\n", sizeFlag);
        fprintf(SysTraceFile, "\tor, in virtual memory pages of %u bytes, using\n"
                "\t\t\"-X%s<positive number>pages\",\n", BYTES_IN_PAGE,
                sizeFlag);
        fprintf(SysTraceFile, "\tor, in megabytes, using \"-X%s<positive number>M\",\n", sizeFlag);
        fprintf(SysTraceFile, "\tor, in gigabytes, using \"-X%s<positive number>G\"\n", sizeFlag);
        fprintf(SysTraceFile, "  <positive number> can be a floating point value or a hex value like 0x10cafe0.\n");
        if (roundTo != 1) {
            fprintf(SysTraceFile, "  The # of bytes will be rounded up to a multiple of");
            if (roundTo == BYTES_IN_PAGE) fprintf(SysTraceFile, "\n  the virtual memory page size: ");
            fprintf(SysTraceFile, "%u\n", roundTo);
        }
        return 0U;              // Distinguished value meaning trouble.
    }
    long double tot_d = userNum * factor;
    assert(tot_d <= (UINT_MAX - roundTo));
    assert(tot_d >= 1);

    unsigned tot = (unsigned) tot_d;
    if (tot % roundTo) {
        unsigned newTot = tot + roundTo - (tot % roundTo);
        fprintf(SysTraceFile,
                "%s: Rounding up %s size from %u bytes to %u,\n"
                "\tthe next multiple of %u bytes%s\n",
                Me, sizeName, tot, newTot, roundTo,
                roundTo == BYTES_IN_PAGE ?
                           ", the virtual memory page size" : "");
        tot = newTot;
    }
    return tot;
}