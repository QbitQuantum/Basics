CFURLRef WKURLCopyCFURL(CFAllocatorRef allocatorRef, WKURLRef URLRef)
{
    ASSERT(!toImpl(URLRef)->string().isNull());

    // We first create a CString and then create the CFURL from it. This will ensure that the CFURL is stored in 
    // UTF-8 which uses less memory and is what WebKit clients might expect.

    // This pattern of using UTF-8 and then falling back to Latin1 on failure matches KURL::createCFString with the
    // major differnce being that KURL does not do a UTF-8 conversion and instead chops off the high bits of the UTF-16
    // character sequence.

    CString buffer = toImpl(URLRef)->string().utf8();
    CFURLRef result = CFURLCreateAbsoluteURLWithBytes(kCFAllocatorDefault, reinterpret_cast<const UInt8*>(buffer.data()), buffer.length(), kCFStringEncodingUTF8, 0, true);
    if (!result)
        result = CFURLCreateAbsoluteURLWithBytes(kCFAllocatorDefault, reinterpret_cast<const UInt8*>(buffer.data()), buffer.length(), kCFStringEncodingISOLatin1, 0, true);
    return result;
}