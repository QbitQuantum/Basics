U16Char_t* convCharStrToU16Str(const char* src, const char* Encoding)
{

    //static char const* const tocode = CHARCONV_ICONV_UTF16;
    char const* const fromcode = getPlatformEncoding(Encoding);

    UErrorCode status = U_ZERO_ERROR;

#ifdef ENCCONV_DEBUG
    std::cout << "\t" "convString" << std::endl;
    //std::cout << "\t\t" "tocode   = " << tocode   << std::endl;
    std::cout << "\t\t" "fromcode = " << fromcode << std::endl;
#endif

    //iconv_t cd = iconv_open(tocode, fromcode);
    // Initializing ICU converter
    UConverter *conv= ucnv_open(fromcode, &status);
#ifdef CHARCONV_DEBUG
    std::cout << "\t\t" "aft ucnv_open: status = " << status << std::endl;
#endif
    if (conv == NULL)
    {   // try default encoding "ISO-8859-1"
        //throw std::runtime_error("Unable to create Unicode converter object");
        conv = ucnv_open("ISO-8859-1", &status);
    }



    char const* srcWrk = src;
    const size_t srcSizeInBytes = std::strlen(src);
    const size_t dstSizeInBytes = MAX(256, (srcSizeInBytes + 1)) * sizeof(U16Char_t);
    U16Char_t* dst = new U16Char_t [dstSizeInBytes / sizeof(U16Char_t)];
    U16Char_t* dstWrk = dst;
    size_t srcLeftInBytes = srcSizeInBytes;
    size_t dstLeftInBytes = dstSizeInBytes - sizeof(U16Char_t);

    status = U_ZERO_ERROR;

    //still if conv is null simply return blank string

    if (conv == NULL)
    {
        dst[0] = NULL;
        //Fix for #3211945
        dstWrk = NULL;
        return dst;
    }

    ucnv_toUChars(conv, (UChar *) dstWrk, dstLeftInBytes, (char*)srcWrk, srcLeftInBytes, &status);

#ifdef CHARCONV_DEBUG
    std::cout << "\t\t" "aft iconv: status = " << status << std::endl;
#endif
    if (status != U_ZERO_ERROR )
    {
        //	throw std::runtime_error("Unable to convert to string");
        *dstWrk = 0;
    }


    //const int err = iconv_close(cd);

    ucnv_close(conv);

    //if (err == -1)
    //	throw std::runtime_error("Unable to deallocate iconv_t object");
    //Fix for #3211945
    dstWrk = NULL;
    return dst;

}