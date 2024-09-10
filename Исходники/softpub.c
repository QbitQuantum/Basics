static DWORD SOFTPUB_LoadCatalogMessage(CRYPT_PROVIDER_DATA *data)
{
    DWORD err;
    HANDLE catalog = INVALID_HANDLE_VALUE;

    if (!data->pWintrustData->u.pCatalog)
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }
    catalog = CreateFileW(data->pWintrustData->u.pCatalog->pcwszCatalogFilePath,
     GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
     NULL);
    if (catalog == INVALID_HANDLE_VALUE)
        return GetLastError();
    if (!CryptSIPRetrieveSubjectGuid(
     data->pWintrustData->u.pCatalog->pcwszCatalogFilePath, catalog,
     &data->u.pPDSip->gSubject))
    {
        err = GetLastError();
        goto error;
    }
    err = SOFTPUB_GetSIP(data);
    if (err)
        goto error;
    err = SOFTPUB_GetMessageFromFile(data, catalog,
     data->pWintrustData->u.pCatalog->pcwszCatalogFilePath);
    if (err)
        goto error;
    err = SOFTPUB_CreateStoreFromMessage(data);
    if (err)
        goto error;
    err = SOFTPUB_DecodeInnerContent(data);
    /* FIXME: this loads the catalog file, but doesn't validate the member. */
error:
    CloseHandle(catalog);
    return err;
}