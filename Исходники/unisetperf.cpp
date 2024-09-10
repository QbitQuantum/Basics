    UnicodeSetPerformanceTest(int32_t argc, const char *argv[], UErrorCode &status)
            : UPerfTest(argc, argv, options, LENGTHOF(options), unisetperf_usage, status),
              utf8(NULL), utf8Length(0), countInputCodePoints(0), spanCount(0) {
        if (U_SUCCESS(status)) {
            UnicodeString pattern=UnicodeString(options[SET_PATTERN].value, -1, US_INV).unescape();
            set.applyPattern(pattern, status);
            prefrozen=set;
            if(0==strcmp(options[FAST_TYPE].value, "fast")) {
                set.freeze();
            }

            int32_t inputLength;
            UPerfTest::getBuffer(inputLength, status);
            if(U_SUCCESS(status) && inputLength>0) {
                countInputCodePoints = u_countChar32(buffer, bufferLen);

                countSpans();

                // Preflight the UTF-8 length and allocate utf8.
                u_strToUTF8(NULL, 0, &utf8Length, buffer, bufferLen, &status);
                if(status==U_BUFFER_OVERFLOW_ERROR) {
                    utf8=(char *)malloc(utf8Length);
                    if(utf8!=NULL) {
                        status=U_ZERO_ERROR;
                        u_strToUTF8(utf8, utf8Length, NULL, buffer, bufferLen, &status);
                    } else {
                        status=U_MEMORY_ALLOCATION_ERROR;
                    }
                }

                if(verbose) {
                    printf("code points:%ld  len16:%ld  len8:%ld  spans:%ld  "
                           "cp/span:%.3g  UChar/span:%.3g  B/span:%.3g  B/cp:%.3g\n",
                           (long)countInputCodePoints, (long)bufferLen, (long)utf8Length, (long)spanCount,
                           (double)countInputCodePoints/spanCount, (double)bufferLen/spanCount, (double)utf8Length/spanCount,
                           (double)utf8Length/countInputCodePoints);
                }
            }
        }
    }