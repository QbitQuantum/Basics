AudioParameter::AudioParameter(const String8& keyValuePairs)
{
    char *str = new char[keyValuePairs.length()+1];
    mKeyValuePairs = keyValuePairs;
    char *last;

    strcpy(str, keyValuePairs.string());
    char *pair = strtok_r(str, ";", &last);
    while (pair != NULL) {
        if (strlen(pair) != 0) {
            size_t eqIdx = strcspn(pair, "=");
            String8 key = String8(pair, eqIdx);
            String8 value;
            if (eqIdx == strlen(pair)) {
                value = String8("");
            } else {
                value = String8(pair + eqIdx + 1);
            }
            if (mParameters.indexOfKey(key) < 0) {
                mParameters.add(key, value);
            } else {
                mParameters.replaceValueFor(key, value);
            }
        } else {
            ALOGV("AudioParameter() cstor empty key value pair");
        }
        pair = strtok_r(NULL, ";", &last);
    }

    delete[] str;
}