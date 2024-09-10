static ErlDrvData couch_drv_start(ErlDrvPort port, char *buff)
{
    UErrorCode status = U_ZERO_ERROR;
    couch_drv_data* pData = (couch_drv_data*)driver_alloc(sizeof(couch_drv_data));

    if (pData == NULL)
        return ERL_DRV_ERROR_GENERAL;

    pData->port = port;

    pData->coll = ucol_open("", &status);
    if (U_FAILURE(status)) {
        couch_drv_stop((ErlDrvData)pData);
        return ERL_DRV_ERROR_GENERAL;
    }

    pData->collNoCase = ucol_open("", &status);
    if (U_FAILURE(status)) {
        couch_drv_stop((ErlDrvData)pData);
        return ERL_DRV_ERROR_GENERAL;
    }

    ucol_setAttribute(pData->collNoCase, UCOL_STRENGTH, UCOL_PRIMARY, &status);
    if (U_FAILURE(status)) {
        couch_drv_stop((ErlDrvData)pData);
        return ERL_DRV_ERROR_GENERAL;
    }

    return (ErlDrvData)pData;
}