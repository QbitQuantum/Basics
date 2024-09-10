bool DrmPassthruPlugIn::onCanHandle(int uniqueId, const String8& path) {
    ALOGV("DrmPassthruPlugIn::canHandle: %s ", path.string());
    String8 extension = path.getPathExtension();
    extension.toLower();
    return (String8(".passthru") == extension);
}