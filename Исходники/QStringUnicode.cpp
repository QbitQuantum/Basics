i8_q* QStringUnicode::ToBytes(const EQTextEncoding &eEncoding, unsigned int &uOutputLength) const
{
    i8_q* pOutputBytes = null_q;
    uOutputLength = 0;

    const unsigned int CHARACTERS_COUNT = m_strString.countChar32(); // It does not include the final null character

    if(CHARACTERS_COUNT > 0)
    {
        UErrorCode errorCode = U_ZERO_ERROR;
        UConverter* pConverter = QStringUnicode::GetConverter(eEncoding);
        const unsigned int CODE_UNITS_COUNT = m_strString.length(); // It does not include the final null character

        // Depending on whether the string is already null-terminated or not, a null terminator will be added at the end
        // of the resultant array of bytes
        const unsigned int ADD_NULL_TERMINATION = m_strString.char32At(CHARACTERS_COUNT - 1) == 0 ? 0 : 1;

        // By default, it is assigned as if it was to be encoded in ASCII or ISO 8859-1 (8-bits per character)
        int32_t nRequiredLengthBytes = CHARACTERS_COUNT + ADD_NULL_TERMINATION;

        // Output size calculation for Unicode encoding forms
        switch(eEncoding)
        {
        case EQTextEncoding::E_UTF8:
            // It is not possible to know in advance how much memory the UTF-8 will require
            // (each character could be represented by 1, 2, 3 or 4 8-bits code units) so we reserve the maximum it would need
            nRequiredLengthBytes = sizeof(i32_q) * (CHARACTERS_COUNT + ADD_NULL_TERMINATION);
            break;
        case EQTextEncoding::E_UTF16:
            // We already know the number of 16 bits code units. A BOM character is added at the beginning
            nRequiredLengthBytes = sizeof(i16_q) * (CODE_UNITS_COUNT + 1 + ADD_NULL_TERMINATION);
            break;
        case EQTextEncoding::E_UTF16BE:
        case EQTextEncoding::E_UTF16LE:
            // We already know the number of 16 bits code units
            nRequiredLengthBytes = sizeof(i16_q) * (CODE_UNITS_COUNT + ADD_NULL_TERMINATION);
            break;
        case EQTextEncoding::E_UTF32:
            // The width of UTF32 characters is always 32 bits. A BOM character is added at the beginning
            nRequiredLengthBytes = sizeof(i32_q) * (CHARACTERS_COUNT + 1 + ADD_NULL_TERMINATION);
            break;
        case EQTextEncoding::E_UTF32BE:
        case EQTextEncoding::E_UTF32LE:
            // The width of UTF32 characters is always 32 bits
            nRequiredLengthBytes = sizeof(i32_q) * (CHARACTERS_COUNT + ADD_NULL_TERMINATION);
            break;
        }

        // Conversion from native encoding (UTF16) to input encoding
        const UChar* pBuffer = m_strString.getBuffer();
        pOutputBytes = new char[nRequiredLengthBytes];
        ucnv_reset(pConverter);
        uOutputLength = ucnv_fromUChars(pConverter, pOutputBytes, nRequiredLengthBytes, pBuffer, CODE_UNITS_COUNT, &errorCode);

        // If it was necessary to add a null terminator...
        if(ADD_NULL_TERMINATION == 1)
        {
            // The last character has to be set to zero (ICU adds only 1 byte at the end as the null terminator)
            // The last character has to be added to the output length
            switch(eEncoding)
            {
            case EQTextEncoding::E_ASCII:
            case EQTextEncoding::E_ISO88591:
            case EQTextEncoding::E_UTF8:
                // 8 bits character
                uOutputLength += sizeof(i8_q);
                memset(&pOutputBytes[uOutputLength - sizeof(i8_q)], 0, sizeof(i8_q));
                break;
            case EQTextEncoding::E_UTF16:
            case EQTextEncoding::E_UTF16BE:
            case EQTextEncoding::E_UTF16LE:
                // 16 bits character
                uOutputLength += sizeof(i16_q);
                memset(&pOutputBytes[uOutputLength - sizeof(i16_q)], 0, sizeof(i16_q));
                break;
            case EQTextEncoding::E_UTF32:
            case EQTextEncoding::E_UTF32BE:
            case EQTextEncoding::E_UTF32LE:
                // 32 bits character
                uOutputLength += sizeof(i32_q);
                memset(&pOutputBytes[uOutputLength - sizeof(i32_q)], 0, sizeof(i32_q));
                break;
            }
        }
    }

    return pOutputBytes;
}