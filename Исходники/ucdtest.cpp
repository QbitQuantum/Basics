void UnicodeTest::TestAdditionalProperties() {
#if !UCONFIG_NO_NORMALIZATION
    // test DerivedCoreProperties.txt and DerivedNormalizationProps.txt
    if(UPRV_LENGTHOF(derivedProps)<UPRV_LENGTHOF(derivedPropsNames)) {
        errln("error: UnicodeTest::derivedProps[] too short, need at least %d UnicodeSets\n",
              UPRV_LENGTHOF(derivedPropsNames));
        return;
    }
    if(UPRV_LENGTHOF(derivedPropsIndex)!=UPRV_LENGTHOF(derivedPropsNames)) {
        errln("error in ucdtest.cpp: UPRV_LENGTHOF(derivedPropsIndex)!=UPRV_LENGTHOF(derivedPropsNames)\n");
        return;
    }

    char path[500];
    if(getUnidataPath(path) == NULL) {
        errln("unable to find path to source/data/unidata/");
        return;
    }
    char *basename=strchr(path, 0);
    strcpy(basename, "DerivedCoreProperties.txt");

    char *fields[2][2];
    UErrorCode errorCode=U_ZERO_ERROR;
    u_parseDelimitedFile(path, ';', fields, 2, derivedPropsLineFn, this, &errorCode);
    if(U_FAILURE(errorCode)) {
        errln("error parsing DerivedCoreProperties.txt: %s\n", u_errorName(errorCode));
        return;
    }

    strcpy(basename, "DerivedNormalizationProps.txt");
    u_parseDelimitedFile(path, ';', fields, 2, derivedPropsLineFn, this, &errorCode);
    if(U_FAILURE(errorCode)) {
        errln("error parsing DerivedNormalizationProps.txt: %s\n", u_errorName(errorCode));
        return;
    }

    // now we have all derived core properties in the UnicodeSets
    // run them all through the API
    int32_t rangeCount, range;
    uint32_t i;
    UChar32 start, end;

    // test all TRUE properties
    for(i=0; i<UPRV_LENGTHOF(derivedPropsNames); ++i) {
        rangeCount=derivedProps[i].getRangeCount();
        for(range=0; range<rangeCount && numErrors[i]<MAX_ERRORS; ++range) {
            start=derivedProps[i].getRangeStart(range);
            end=derivedProps[i].getRangeEnd(range);
            for(; start<=end; ++start) {
                if(!u_hasBinaryProperty(start, derivedPropsIndex[i])) {
                    dataerrln("UnicodeTest error: u_hasBinaryProperty(U+%04lx, %s)==FALSE is wrong", start, derivedPropsNames[i]);
                    if(++numErrors[i]>=MAX_ERRORS) {
                      dataerrln("Too many errors, moving to the next test");
                      break;
                    }
                }
            }
        }
    }

    // invert all properties
    for(i=0; i<UPRV_LENGTHOF(derivedPropsNames); ++i) {
        derivedProps[i].complement();
    }

    // test all FALSE properties
    for(i=0; i<UPRV_LENGTHOF(derivedPropsNames); ++i) {
        rangeCount=derivedProps[i].getRangeCount();
        for(range=0; range<rangeCount && numErrors[i]<MAX_ERRORS; ++range) {
            start=derivedProps[i].getRangeStart(range);
            end=derivedProps[i].getRangeEnd(range);
            for(; start<=end; ++start) {
                if(u_hasBinaryProperty(start, derivedPropsIndex[i])) {
                    errln("UnicodeTest error: u_hasBinaryProperty(U+%04lx, %s)==TRUE is wrong\n", start, derivedPropsNames[i]);
                    if(++numErrors[i]>=MAX_ERRORS) {
                      errln("Too many errors, moving to the next test");
                      break;
                    }
                }
            }
        }
    }
#endif /* !UCONFIG_NO_NORMALIZATION */
}