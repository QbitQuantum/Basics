ULONG
BaseSrvNlsSetUserInfo(
    IN OUT PCSR_API_MSG m,
    IN OUT PCSR_REPLY_STATUS ReplyStatus)
{
    PBASE_NLS_SET_USER_INFO_MSG a =
        (PBASE_NLS_SET_USER_INFO_MSG)&m->u.ApiMessageData;

    ULONG rc;                               /* return code */


    /*
     *  Get the cache mutant.
     */
    NtWaitForSingleObject( hNlsCacheMutant, FALSE, NULL );

    /*
     *  Set the value in the registry and update the cache.
     */
    rc = NlsSetRegAndCache( a->pValue,
                            a->pCacheString,
                            a->pData,
                            a->DataLength );

    /*
     *  Release the cache mutant.
     */
    NtReleaseMutant( hNlsCacheMutant, NULL );

    /*
     *  Return the result of NtSetValueKey.
     */
    return (rc);

    ReplyStatus;    // get rid of unreferenced parameter warning message
}