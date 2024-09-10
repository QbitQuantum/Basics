U_STABLE void U_EXPORT2
ucnv_setFromUCallBack_53(UConverter * converter,
                       UConverterFromUCallback newAction,
                       const void *newContext,
                       UConverterFromUCallback *oldAction,
                       const void **oldContext,
                       UErrorCode * err)
{
    ucnv_setFromUCallBack(converter, newAction, newContext, oldAction, oldContext, err);
}