ResourceBundle ResourceBundle::get(const char* key, UErrorCode& status) const {
    UResourceBundle r;

    ures_initStackObject(&r);
    ures_getByKey(fResource, key, &r, &status);
    ResourceBundle res(&r, status);
    if (U_SUCCESS(status)) {
        ures_close(&r);
    }
    return res;
}