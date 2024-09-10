bool DrmManager::canHandle(int uniqueId, const String8& path, const String8& mimeType) {
    Mutex::Autolock _l(mLock);
    const String8 plugInId = getSupportedPlugInId(mimeType);
    bool result = (EMPTY_STRING != plugInId) ? true : false;

    if (0 < path.length()) {
        if (result) {
            IDrmEngine& rDrmEngine = mPlugInManager.getPlugIn(plugInId);
            result = rDrmEngine.canHandle(uniqueId, path);
        } else {
            String8 extension = path.getPathExtension();
            if (String8("") != extension) {
                result = canHandle(uniqueId, path);
            }
        }
    }
    return result;
}