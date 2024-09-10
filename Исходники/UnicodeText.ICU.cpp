        int32 ChangeStringLinguisticCase(CaseFlags caseFlags, const char16* sourceString, uint32 sourceLength, char16* destString, uint32 destLength, ApiError* pErrorOut)
        {
            int32_t resultStringLength = 0;
            UErrorCode errorCode = U_ZERO_ERROR;

            static_assert(sizeof(UChar) == sizeof(char16), "Unexpected char type from ICU, function might have to be updated");
            if (caseFlags == CaseFlagsUpper)
            {
                resultStringLength = u_strToUpper((UChar*) destString, destLength,
                    (UChar*) sourceString, sourceLength, NULL, &errorCode);
            }
            else if (caseFlags == CaseFlagsLower)
            {
                resultStringLength = u_strToLower((UChar*) destString, destLength,
                    (UChar*) sourceString, sourceLength, NULL, &errorCode);
            }
            else
            {
                Assert(false);
            }

            if (U_FAILURE(errorCode) &&
                !(destLength == 0 && errorCode == U_BUFFER_OVERFLOW_ERROR))
            {
                *pErrorOut = TranslateUErrorCode(errorCode);
                return -1;
            }

            // Todo: check for resultStringLength > destLength
            // Return insufficient buffer in that case
            return resultStringLength;
        }