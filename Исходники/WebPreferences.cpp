void WebPreferences::migrateWebKitPreferencesToCFPreferences()
{
    CFStringRef didMigrateKey = CFSTR(WebKitDidMigrateWebKitPreferencesToCFPreferencesPreferenceKey);
    if (boolValueForKey(didMigrateKey))
        return;
    bool oldValue = m_autoSaves;
    m_autoSaves = true;
    setBoolValue(didMigrateKey, TRUE);
    m_autoSaves = oldValue;

    CString path = oldPreferencesPath().utf8();

    RetainPtr<CFURLRef> urlRef(AdoptCF, CFURLCreateFromFileSystemRepresentation(0, reinterpret_cast<const UInt8*>(path.data()), path.length(), false));
    if (!urlRef)
        return;

    RetainPtr<CFReadStreamRef> stream(AdoptCF, CFReadStreamCreateWithFile(0, urlRef.get()));
    if (!stream)
        return;

    if (!CFReadStreamOpen(stream.get()))
        return;

    CFPropertyListFormat format = kCFPropertyListBinaryFormat_v1_0 | kCFPropertyListXMLFormat_v1_0;
    RetainPtr<CFPropertyListRef> plist(AdoptCF, CFPropertyListCreateFromStream(0, stream.get(), 0, kCFPropertyListMutableContainersAndLeaves, &format, 0));
    CFReadStreamClose(stream.get());

    if (!plist || CFGetTypeID(plist.get()) != CFDictionaryGetTypeID())
        return;

    copyWebKitPreferencesToCFPreferences(static_cast<CFDictionaryRef>(plist.get()));

    deleteFile(oldPreferencesPath());
}