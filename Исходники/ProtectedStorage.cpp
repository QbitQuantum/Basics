char* ProtectedStorage::DecryptData(int nDataLen, BYTE* pData)
{
    DATA_BLOB DataOut;
    DATA_BLOB DataIn;
    char* pReturn = NULL;

    // Set up the input data structure
    DataIn.cbData = nDataLen;
    DataIn.pbData = (BYTE*)malloc(nDataLen);
    memcpy(DataIn.pbData, pData, nDataLen);

    if (CryptUnprotectData(&DataIn,	NULL, NULL, NULL, NULL, 0, &DataOut))
    {
        pReturn = (char*)malloc(DataOut.cbData + 1);
        memset(pReturn, 0, DataOut.cbData + 1);
        _snprintf_s(pReturn, DataOut.cbData, sizeof(DataOut.pbData), "%S", DataOut.pbData);

        //memcpy(pReturn, DataOut.pbData, DataOut.cbData);
        //pReturn[DataOut.cbData + 1] = 0;

        free(DataIn.pbData);
        return pReturn;
    }
    else
    {
        free(DataIn.pbData);
        return NULL;
    }
}