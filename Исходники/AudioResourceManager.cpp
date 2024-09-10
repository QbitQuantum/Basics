status_t AudioResourceManager::setParameter(const String8& keyValuePairs) {

    String8 key;
    String8 value;
    status_t status = NO_ERROR;
    AudioParameter param = AudioParameter(keyValuePairs);

    Mutex::Autolock autolock(mLock);

    ALOGD(" setParameter %s:",  keyValuePairs.string());
    for(uint8_t i=0; i < ARRAY_SIZE(sUseCaseNameToEnumValue); i++) {
        key = sUseCaseNameToEnumValue[i].name;
        if (param.get(key, value) == NO_ERROR) {

            audio_use_case_value_t useCase =
                        (audio_use_case_value_t) extractMetaData(
                    sUseCaseNameToEnumValue,
                    ARRAY_SIZE(sUseCaseNameToEnumValue),
                    key);
            ALOGD("key = %s, value = %s, useCase = %d",
                        key.string(), value.string(), (int32_t)useCase);
            if(value == "true") {
                // check if there is a conflicting usecase
                // if yes, return error without updating the refCount
                // if no increment the refCount
                ALOGV("handleConcurrency");
                status = handleConcurrency(useCase, true);
            }
            else if(value == "false") {
                // Decrement the refCount
                ALOGV("updateUsecaseRefCount");
                status = updateUsecaseRefCount(useCase, false);
            }
            else {
                ALOGE(" Wrong value set for use case = %s", key.string());
                status = BAD_VALUE;
            }
            break;
        } else {
            status = NAME_NOT_FOUND;
            ALOGV("Not a concurrency setParameter - Not an error");

        }
    }
    param.remove(key);

    return status;
}