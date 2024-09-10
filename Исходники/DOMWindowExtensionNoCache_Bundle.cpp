void DOMWindowExtensionNoCache::willDestroyGlobalObjectForDOMWindowExtension(WKBundleDOMWindowExtensionRef extension)
{
    sendBundleMessage("WillDestroyDOMWindowExtensionToGlobalObject called");
    updateExtensionStateRecord(extension, Destroyed);
    m_extensionToRecordMap.remove(extension);
    WKRelease(extension);
}