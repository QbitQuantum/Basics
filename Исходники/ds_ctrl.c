/* DG_CONTROL/DAT_PENDINGXFERS/MSG_ENDXFER */
TW_UINT16 SANE_PendingXfersEndXfer (pTW_IDENTITY pOrigin, 
                                     TW_MEMREF pData)
{
#ifndef SONAME_LIBSANE
    return TWRC_FAILURE;
#else
    TW_UINT16 twRC = TWRC_SUCCESS;
    pTW_PENDINGXFERS pPendingXfers = (pTW_PENDINGXFERS) pData;
    SANE_Status status;

    TRACE("DG_CONTROL/DAT_PENDINGXFERS/MSG_ENDXFER\n");

    if (activeDS.currentState != 6 && activeDS.currentState != 7)
    {
        twRC = TWRC_FAILURE;
        activeDS.twCC = TWCC_SEQERROR;
    }
    else
    {
        pPendingXfers->Count = -1;
        activeDS.currentState = 6;
        if (! activeDS.sane_started)
        {
            status = psane_start (activeDS.deviceHandle);
            if (status != SANE_STATUS_GOOD)
            {
                TRACE("PENDINGXFERS/MSG_ENDXFER sane_start returns %s\n", psane_strstatus(status));
                pPendingXfers->Count = 0;
                activeDS.currentState = 5;
                /* Notify the application that it can close the data source */
                if (activeDS.windowMessage)
                    PostMessageA(activeDS.hwndOwner, activeDS.windowMessage, MSG_CLOSEDSREQ, 0);
            }
            else
                activeDS.sane_started = TRUE;
        }
        twRC = TWRC_SUCCESS;
        activeDS.twCC = TWCC_SUCCESS;
    }

    return twRC;
#endif
}