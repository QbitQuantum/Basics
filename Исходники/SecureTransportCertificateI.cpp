chrono::system_clock::time_point
#else
IceUtil::Time
#endif
getX509Date(SecCertificateRef cert, CFTypeRef key)
{
    assert(key == kSecOIDX509V1ValidityNotAfter || key == kSecOIDX509V1ValidityNotBefore);
    UniqueRef<CFDictionaryRef> property(getCertificateProperty(cert, key));
    CFAbsoluteTime seconds = 0;
    if(property)
    {
        CFNumberRef date = static_cast<CFNumberRef>(CFDictionaryGetValue(property.get(), kSecPropertyKeyValue));
        CFNumberGetValue(date, kCFNumberDoubleType, &seconds);
    }

    IceUtil::Time time = IceUtil::Time::secondsDouble(kCFAbsoluteTimeIntervalSince1970 + seconds);

#ifdef ICE_CPP11_MAPPING
    return chrono::system_clock::time_point(chrono::microseconds(time.toMicroSeconds()));
#else
    return time;
#endif
}