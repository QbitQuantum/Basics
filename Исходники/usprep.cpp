U_CAPI UStringPrepProfile* U_EXPORT2
usprep_openByType(UStringPrepProfileType type,
				  UErrorCode* status) {
    if(status == NULL || U_FAILURE(*status)){
        return NULL;
    }
    int32_t index = (int32_t)type;
    if (index < 0 || index >= UPRV_LENGTHOF(PROFILE_NAMES)) {
        *status = U_ILLEGAL_ARGUMENT_ERROR;
        return NULL;
    }
    return usprep_open(NULL, PROFILE_NAMES[index], status);
}