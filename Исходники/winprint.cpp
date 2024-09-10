/*++
*******************************************************************
    E n u m P r i n t P r o c e s s o r D a t a t y p e s W

    Routine Description:
        Enumerates the data types supported by the print processor.

    Arguments:
        pName               => server name
        pPrintProcessorName => print processor name
        Level               => level of data to return (must be 1)
        pDatatypes          => structure array to fill in
        cbBuf               => length of structure array in bytes
        pcbNeeded           => buffer length copied/required
        pcReturned          => number of structures returned

    Return Value:
        TRUE  if successful
        FALSE if failed - caller must use GetLastError for reason
*******************************************************************
--*/
_Use_decl_annotations_
BOOL WINAPI
EnumPrintProcessorDatatypes(
    LPWSTR  pName,
    LPWSTR  pPrintProcessorName,
    DWORD   Level,
    LPBYTE  pDatatypes,
    DWORD   cbBuf,
    LPDWORD pcbNeeded,
    LPDWORD pcReturned
)
{
    DATATYPES_INFO_1    *pInfo1 = (DATATYPES_INFO_1 *)pDatatypes;
    LPWSTR              *pMyDatatypes = Datatypes;
    size_t              cbTotal=0;
    ULONG               cchBuf =0;
    LPBYTE              pEnd;
    BOOL                bRetVal = TRUE;
    HRESULT             hr;
    size_t              tempSizeT;

    UNREFERENCED_PARAMETER(pName);
    UNREFERENCED_PARAMETER(pPrintProcessorName);

    if ( NULL == pcbNeeded  ||
         NULL == pcReturned )
    {
        SetLastError (ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    /** Start assuming failure, no entries returned **/

    *pcbNeeded  = 0;
    *pcReturned = 0;

    if (Level != 1)
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    /** Add up the minimum buffer required **/

    while (*pMyDatatypes) {
        if (FAILED(SizeTMult(wcslen(*pMyDatatypes), sizeof(WCHAR), &tempSizeT)) ||
            FAILED(SizeTAdd(tempSizeT, sizeof(WCHAR), &tempSizeT)) ||
            FAILED(SizeTAdd(tempSizeT, sizeof(DATATYPES_INFO_1), &tempSizeT)) ||
            FAILED(SizeTAdd(cbTotal, tempSizeT, &cbTotal)))
        {
            SetLastError (ERROR_ARITHMETIC_OVERFLOW);
            bRetVal = FALSE;
            break;
        }

        pMyDatatypes++;
    }

    /** Set the buffer length returned/required **/

    if (bRetVal && FAILED(SizeTToDWord(cbTotal, pcbNeeded)))
    {
        SetLastError (ERROR_ARITHMETIC_OVERFLOW);
        bRetVal = FALSE;
    }

    /** Fill in the array only if there is sufficient space **/

    if (bRetVal && cbTotal <= cbBuf)
    {

        if ( NULL == pInfo1 ) //pInfo1 is same as pDatatypes
        {
            SetLastError (ERROR_INVALID_PARAMETER);
            bRetVal = FALSE;
        }
        else
        {

            /** Pick up pointer to end of the given buffer **/

            pEnd = (LPBYTE)pInfo1 + cbBuf;


            /** Pick up our list of supported data types **/

            pMyDatatypes = Datatypes;

            /**
                Fill in the given buffer.  We put the data names at the end of
                the buffer, working towards the front.  The structures are put
                at the front, working towards the end.
            **/

            while (*pMyDatatypes) {

                if (FAILED(SizeTAdd(wcslen(*pMyDatatypes), 1, &tempSizeT)) || //+1 is for \0.
                    FAILED(SizeTToDWord(tempSizeT, &cchBuf)))
                {
                    SetLastError (ERROR_ARITHMETIC_OVERFLOW);
                    bRetVal = FALSE;
                    break;
                }
                pEnd -= cchBuf*sizeof(WCHAR);

                hr = StringCchCopy ( (LPWSTR)pEnd, cchBuf, *pMyDatatypes);
                if ( FAILED(hr) )
                {
                    //
                    // For the hr values returned by StringCchCopy, the following macro
                    // is sufficient
                    //
                    SetLastError (HRESULT_CODE(hr));
                    bRetVal = FALSE;
                    break;
                }

                pInfo1->pName = (LPWSTR)pEnd;
                pInfo1++;
                (*pcReturned)++;

                pMyDatatypes++;
            }
        }

    } else {

        /** Caller didn't have large enough buffer, set error and return **/

        SetLastError(ERROR_INSUFFICIENT_BUFFER);
        bRetVal = FALSE;
    }

    return bRetVal;
}