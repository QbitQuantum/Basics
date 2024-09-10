/*
 * Sets a property value.
 *
 * @param property - the property name
 * @param value - the property value (zero terminated string)
 */
void DeviceManagementNode::setPropertyValue(const char* prop, const char* value) {
    if ((prop == NULL) || (value == NULL)) {
        return;
    }

    HKEY key;
    DWORD res;
    TCHAR *p = NULL;
    TCHAR *v = NULL;

    RegCreateKeyEx(
            HKEY_DM_ROOT,
            fullContext,
            0,
            NULL,
            REG_OPTION_NON_VOLATILE,
            KEY_ALL_ACCESS,
            NULL,
            &key,
            &res
            );


    if (key == 0) {
        //lastErrorCode = ERR_INVALID_CONTEXT;
        //sprintf(lastErrorMsg, "Invalid context path: %s", fullContext);
        setErrorF(ERR_INVALID_CONTEXT, "Invalid context path: %s", fullContext);
        goto finally;
    }

    p = toWideChar(prop);
    v = toWideChar(value);

    RegSetValueEx(
            key,
            p,
            NULL,
            REG_SZ,  // we currently support only strings
            (UCHAR*)v,
            (wcslen(v)+1)*sizeof(WCHAR)
            );

    delete [] p;
    delete [] v;
    RegFlushKey(key);
finally:

    if (key != 0) {
        RegCloseKey(key);
    }
}