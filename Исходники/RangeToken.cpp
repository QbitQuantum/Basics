// ---------------------------------------------------------------------------
//  RangeToken: Getter methods
// ---------------------------------------------------------------------------
RangeToken* RangeToken::getCaseInsensitiveToken(TokenFactory* const tokFactory) {

    if (fCaseIToken == 0 && tokFactory && fRanges) {

        bool isNRange = (getTokenType() == T_NRANGE) ? true : false;
        RangeToken* lwrToken = tokFactory->createRange(isNRange);

#if XERCES_USE_TRANSCODER_ICU && ((U_ICU_VERSION_MAJOR_NUM > 2) || (U_ICU_VERSION_MAJOR_NUM == 2 && U_ICU_VERSION_MINOR_NUM >=4))
        UChar* rangeStr=(UChar*)fMemoryManager->allocate(40*fElemCount*sizeof(UChar));
        ArrayJanitor<UChar> janRange(rangeStr, fMemoryManager);
        int c=0;
        rangeStr[c++] = chOpenSquare;
        for (unsigned int i = 0;  i < fElemCount - 1;  i += 2) {
            XMLCh buffer[10];
            XMLSize_t len, j;

            rangeStr[c++] = chBackSlash;
            rangeStr[c++] = chLatin_U;
            XMLString::binToText(fRanges[i], buffer, 10, 16, fMemoryManager);
            len = XMLString::stringLen(buffer);
            for(j=0;j<(8-len);j++)
                rangeStr[c++] = chDigit_0;
            XMLCh* p=buffer;
            while(*p)
                rangeStr[c++] = *p++;
            if(fRanges[i+1]!=fRanges[i])
            {
                rangeStr[c++] = chDash;
                rangeStr[c++] = chBackSlash;
                rangeStr[c++] = chLatin_U;
                XMLString::binToText(fRanges[i+1], buffer, 10, 16, fMemoryManager);
                len = XMLString::stringLen(buffer);
                for(j=0;j<(8-len);j++)
                    rangeStr[c++] = chDigit_0;
                p=buffer;
                while(*p)
                    rangeStr[c++] = *p++;
            }
        }
        rangeStr[c++] = chCloseSquare;
        rangeStr[c++] = chNull;
        UErrorCode ec=U_ZERO_ERROR;
        USet* range=uset_openPatternOptions(rangeStr, -1, USET_CASE_INSENSITIVE, &ec);
        if(range)
        {
            ec = U_ZERO_ERROR;
            uint32_t cbCount=uset_serialize(range, NULL, 0, &ec);
            uint16_t* buffer=(uint16_t*)fMemoryManager->allocate(cbCount*sizeof(uint16_t));
            ArrayJanitor<uint16_t> janSet(buffer, fMemoryManager);
            ec = U_ZERO_ERROR;
            uset_serialize(range, buffer, cbCount, &ec);
            USerializedSet serializedSet;
            uset_getSerializedSet(&serializedSet, buffer, cbCount);
            int32_t nSets=uset_getSerializedRangeCount(&serializedSet);
            for(int32_t i=0; i<nSets; i++)
            {
                UChar32 start, end;
                uset_getSerializedRange(&serializedSet, i, &start, &end);
                lwrToken->addRange(start, end);
            }
            // does this release the memory allocated by the set?
            uset_setSerializedToOne(&serializedSet, 32);
            uset_close(range);
        }
#else
        unsigned int exceptIndex = 0;

        for (unsigned int i = 0;  i < fElemCount - 1;  i += 2) {
            for (XMLInt32 ch = fRanges[i];  ch <= fRanges[i + 1];  ++ch) {
#if XERCES_USE_TRANSCODER_ICU
                const XMLInt32  upperCh = u_toupper(ch);

                if (upperCh != ch)
                {
                    lwrToken->addRange(upperCh, upperCh);
                }

                const XMLInt32  lowerCh = u_tolower(ch);

                if (lowerCh != ch)
                {
                    lwrToken->addRange(lowerCh, lowerCh);
                }

                const XMLInt32  titleCh = u_totitle(ch);

                if (titleCh != ch && titleCh != upperCh)
                {
                    lwrToken->addRange(titleCh, titleCh);
                }
#else
                if (ch >= chLatin_A && ch <= chLatin_Z)
                {
                    ch += chLatin_a - chLatin_A;

                    lwrToken->addRange(ch, ch);
                }
                else if (ch >= chLatin_a && ch <= chLatin_z)
                {
                    ch -= chLatin_a - chLatin_A;

                    lwrToken->addRange(ch, ch);
                }
#endif

                const unsigned int  exceptionsSize =
                    sizeof(s_exceptions) / sizeof(s_exceptions[0]);

                // Add any exception chars.  These are characters where the the
                // case mapping is not symmetric.  (Unicode case mappings are not isomorphic...)
                while (exceptIndex < exceptionsSize)
                {
                    if (s_exceptions[exceptIndex].baseChar < ch)
                    {
                        ++exceptIndex;
                    }
                    else if (s_exceptions[exceptIndex].baseChar == ch)
                    {
                        const XMLInt32  matchingChar =
                            s_exceptions[exceptIndex].matchingChar;

                        lwrToken->addRange(
                            matchingChar,
                            matchingChar);

                        ++exceptIndex;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }

        lwrToken->mergeRanges(this);
#endif
        lwrToken->compactRanges();
        lwrToken->createMap();

        fCaseIToken = lwrToken;
        // TODO(dbertoni) This is a temporary hack until we can change the ABI.
        // See Jira issue XERCESC-1866 for more details.
        // Overload the fCaseIToken data member to be the case-insensitive token
        // that's caching the case-insensitive one.  We need this because tokens
        // have varying lifetimes.
        fCaseIToken->setCaseInsensitiveToken(this);
    }

    return fCaseIToken;
}