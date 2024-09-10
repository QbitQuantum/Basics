int FwdLockEngine::onGetDrmObjectType(int uniqueId,
                                      const String8& path,
                                      const String8& mimeType) {
    String8 mimeStr = String8(mimeType);

    LOG_VERBOSE("FwdLockEngine::onGetDrmObjectType");

    /* Checks whether
    * 1. path and mime type both are not empty strings (meaning unavailable) else content is unknown
    * 2. if one of them is empty string and if other is known then its a DRM Content Object.
    * 3. if both of them are available, then both may be of known type
    *    (regardless of the relation between them to make it compatible with other DRM Engines)
    */
    if (((0 == path.length()) || onCanHandle(uniqueId, path)) &&
        ((0 == mimeType.length()) || IsMimeTypeSupported(mimeType)) && (mimeType != path) ) {
            return DrmObjectType::CONTENT;
    }

    return DrmObjectType::UNKNOWN;
}