// Requires free() of returned UTF16Chars.
void convertUTF8ToUTF16(const NPUTF8 *UTF8Chars, int UTF8Length, NPUTF16 **UTF16Chars, unsigned int *UTF16Length)
{
#if USE(ICU_UNICODE)
    assert(UTF8Chars || UTF8Length == 0);
    assert(UTF16Chars);
    
    if (UTF8Length == -1)
        UTF8Length = static_cast<int>(strlen(UTF8Chars));
        
    // UTF16Length maximum length is the length of the UTF8 string, plus one to include terminator
    // Without the plus one, it will convert ok, but a warning is generated from the converter as
    // there is not enough room for a terminating character.
    *UTF16Length = UTF8Length + 1; 
        
    *UTF16Chars = 0;
    UErrorCode status = U_ZERO_ERROR;
    UConverter* conv = ucnv_open("utf8", &status);
    if (U_SUCCESS(status)) { 
        *UTF16Chars = (NPUTF16 *)malloc(sizeof(NPUTF16) * (*UTF16Length));
        ucnv_setToUCallBack(conv, UCNV_TO_U_CALLBACK_STOP, 0, 0, 0, &status);
        *UTF16Length = ucnv_toUChars(conv, (::UChar*)*UTF16Chars, *UTF16Length, UTF8Chars, UTF8Length, &status); 
        ucnv_close(conv);
    } 
    
    // Check to see if the conversion was successful
    // Some plugins return invalid UTF-8 in NPVariantType_String, see <http://bugs.webkit.org/show_bug.cgi?id=5163>
    // There is no "bad data" for latin1. It is unlikely that the plugin was really sending text in this encoding,
    // but it should have used UTF-8, and now we are simply avoiding a crash.
    if (!U_SUCCESS(status)) {
        *UTF16Length = UTF8Length;
        
        if (!*UTF16Chars)   // If the memory wasn't allocated, allocate it.
            *UTF16Chars = (NPUTF16 *)malloc(sizeof(NPUTF16) * (*UTF16Length));
 
        for (unsigned i = 0; i < *UTF16Length; i++)
            (*UTF16Chars)[i] = UTF8Chars[i] & 0xFF;
    }
#else
    assert(!"Implement me!");    
#endif
}