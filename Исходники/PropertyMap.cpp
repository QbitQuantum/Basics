bool PropertyMap::tryGetProperty(const String8& key, float& outValue) const {
    String8 stringValue;
    if (! tryGetProperty(key, stringValue) || stringValue.length() == 0) {
        return false;
    }

    char* end;
    float value = strtof(stringValue.string(), & end);
    if (*end != '\0') {
        ALOGW("Property key '%s' has invalid value '%s'.  Expected a float.",
                key.string(), stringValue.string());
        return false;
    }
    outValue = value;
    return true;
}