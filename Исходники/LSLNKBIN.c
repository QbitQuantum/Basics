/*====================================================================*/
int processKeyArray(char* key,
                    char* value,
                    CICSProgramDesc* pProgramDesc) {

    char itemValue[MAX_VALUE_LEN];
    char* remaining = value;
    int pos = 0;
    int maxSize = MAX_OUT_CONTAINERS * (CONTAINER_NAME_LEN + 1);

    if (value == NULL || strlen(value) == 0) {
        logError(MODULE_NAME, "Key found with no associated value.");
        return ERROR_CODE;
    }

    if (g_pTraceParms->traceMode == TRUE_CODE) {
        sprintf(g_traceMessage,
            "processKeyArray key=%s value=%s", key, value);
        traceMessage(MODULE_NAME, g_traceMessage);
    }

    if (0 == strcmp(OUTCONTAINERS_KEY, key)) {
        /* Get the first item value */
        remaining = getToken(
                       remaining, itemValue, MAX_VALUE_LEN - 1,
                       VALUE_DELIM, VALUE_DELIM);
        while(itemValue != NULL
                && strlen(itemValue) > 0 && pos < maxSize) {
            memcpy(pProgramDesc->CICSOutputContainers + pos,
                   itemValue, strlen(itemValue));
            pProgramDesc->CICSOutputContainersCount += 1;
            pos += (CONTAINER_NAME_LEN + 1);
            remaining = getToken(
                           remaining, itemValue, MAX_VALUE_LEN - 1,
                           VALUE_DELIM, VALUE_DELIM);
        }
    }

    return OK_CODE;
}