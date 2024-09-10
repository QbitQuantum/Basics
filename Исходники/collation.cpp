/*
Function:
LastIndexOf
*/
extern "C" int32_t LastIndexOf(
    SortHandle* pSortHandle, const UChar* lpTarget, int32_t cwTargetLength, const UChar* lpSource, int32_t cwSourceLength, int32_t options)
{
    static_assert(USEARCH_DONE == -1, "managed side requires -1 for not found");

    int32_t result = USEARCH_DONE;
    UErrorCode err = U_ZERO_ERROR;
    const UCollator* pColl = GetCollatorFromSortHandle(pSortHandle, options, &err);

    if (U_SUCCESS(err))
    {
        UStringSearch* pSearch = usearch_openFromCollator(lpTarget, cwTargetLength, lpSource, cwSourceLength, pColl, nullptr, &err);

        if (U_SUCCESS(err))
        {
            result = usearch_last(pSearch, &err);
            usearch_close(pSearch);
        }
    }

    return result;
}