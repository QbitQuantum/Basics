void FontAtlas::conversionU16TOGB2312(const std::u16string& newChars, std::unordered_map<unsigned short, unsigned short>& newCharsMap)
{
    size_t strLen = newChars.length();
    auto gb2312StrSize = strLen * 2;
    auto gb2312Text = new (std::nothrow) char[gb2312StrSize];
    memset(gb2312Text, 0, gb2312StrSize);

    switch (_fontFreeType->getEncoding())
    {
    case FT_ENCODING_GB2312:
    {
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT
        WideCharToMultiByte(936, NULL, (LPCWCH)newChars.c_str(), strLen, (LPSTR)gb2312Text, gb2312StrSize, NULL, NULL);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        conversionEncodingJNI((char*)newChars.c_str(), gb2312StrSize, "UTF-16LE", gb2312Text, "GB2312");
#else
        if (_iconv == nullptr)
        {
            _iconv = iconv_open("gb2312", "utf-16le");
        }

        if (_iconv == (iconv_t)-1)
        {
            CCLOG("conversion from utf16 to gb2312 not available");
        }
        else
        {
            char* pin = (char*)newChars.c_str();
            char* pout = gb2312Text;
            size_t inLen = strLen * 2;
            size_t outLen = gb2312StrSize;

            iconv(_iconv, (char**)&pin, &inLen, &pout, &outLen);
        }
#endif
    }
        break;
    default:
        CCLOG("Unsupported encoding:%d", _fontFreeType->getEncoding());
        break;
    }

    unsigned short gb2312Code = 0;
    unsigned char* dst = (unsigned char*)&gb2312Code;
    unsigned short u16Code;
    for (size_t index = 0, gbIndex = 0; index < strLen; ++index)
    {
        u16Code = newChars[index];
        if (u16Code < 256)
        {
            newCharsMap[u16Code] = u16Code;
            gbIndex += 1;
        }
        else
        {
            dst[0] = gb2312Text[gbIndex + 1];
            dst[1] = gb2312Text[gbIndex];
            newCharsMap[u16Code] = gb2312Code;

            gbIndex += 2;
        }
    }

    delete [] gb2312Text;
}