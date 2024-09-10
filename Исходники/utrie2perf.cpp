    UTrie2PerfTest(int32_t argc, const char *argv[], UErrorCode &status)
            : UPerfTest(argc, argv, NULL, 0, "", status),
              utf8(NULL), utf8Length(0), countInputCodePoints(0) {
        if (U_SUCCESS(status)) {
#if 0       // See comment at unorm_initUTrie2() forward declaration.
            unorm_initUTrie2(&status);
            ubidi_initUTrie2(&status);
#endif
            int32_t inputLength;
            UPerfTest::getBuffer(inputLength, status);
            if(U_SUCCESS(status) && inputLength>0) {
                countInputCodePoints = u_countChar32(buffer, bufferLen);

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
                    printf("code points:%ld  len16:%ld  len8:%ld  "
                           "B/cp:%.3g\n",
                           (long)countInputCodePoints, (long)bufferLen, (long)utf8Length,
                           (double)utf8Length/countInputCodePoints);
                }
            }
        }
    }