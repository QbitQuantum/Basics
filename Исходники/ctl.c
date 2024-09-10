static void CTLDataContext_Free(void *context)
{
    PCTL_CONTEXT ctlContext = context;

    CryptMsgClose(ctlContext->hCryptMsg);
    CryptMemFree(ctlContext->pbCtlEncoded);
    CryptMemFree(ctlContext->pbCtlContext);
    LocalFree(ctlContext->pCtlInfo);
}