BOOL
bGetForms(
    HANDLE   hPrinter,
    PRASDDUIINFO pRasdduiInfo       /* Global Data Access */
)
{
    DWORD   cbNeeded;                   /* Number of bytes needed */
    DWORD   cReturned;                  /* Number of forms returned */

    FORM_INFO_1   *pForm;               /* Scanning through returned data */
    FORM_DATA     *pFDTmp;              /* Filling in FORM_DATA stuff */


    /*
     *    Standard technique:  call first to determine how much storage
     *  is required,  allocate the storage and then call again.
     */

    if( !EnumForms( hPrinter, 1, NULL, 0, &cbNeeded, &cReturned ) )
    {
        if( GetLastError() == ERROR_INSUFFICIENT_BUFFER )
        {
            if( pFIBase = (FORM_INFO_1 *)HEAPALLOC( pRasdduiInfo, 0, cbNeeded ) )
            {
                if( EnumForms( hPrinter, 1, (LPBYTE)pFIBase,
                                            cbNeeded, &cbNeeded, &cReturned ) )
                {
                    /*
                     *  Allocate the number + 1 of structures needed to make
                     *  the FORM_DATA array.  This is used elsewhere.
                     */

                    cbNeeded = (cReturned + 1) * sizeof( FORM_DATA );

                    if( !(pFD = (FORM_DATA *)HEAPALLOC( pRasdduiInfo, 0, cbNeeded )) )
                    {
                        vEndForms(pRasdduiInfo);            /* Does the clean up */

                        return  FALSE;
                    }
                    ZeroMemory( pFD, cbNeeded );

                    pForm = pFIBase;
                    pFDTmp = pFD;

                    pRasdduiInfo->cForms = cReturned;         /* For setting defaults etc */

                    while( cReturned-- )
                    {
                        /*
                         *   Have our structure point to the forms data,
                         * and also convert the forms data base into
                         * master units.
                         */

                        XTOMASTER( pForm->Size.cx );
                        YTOMASTER( pForm->Size.cy );

                        pFDTmp->pFI = pForm++;
                        ++pFDTmp;
                    }

                }
                //If EnumForms fails, return false.
                else
                {
                    RIP("Rasddui!bGetForms:2nd call to EnumForms Failed\n");
                    vEndForms(pRasdduiInfo);            /* Does the clean up */
                    return  FALSE;
                }

                return    TRUE;         /* AOK */
            }
        }
        //If EnumForms fails, return false.
        else
        {
            RIP("Rasddui!bGetForms:EnumForms returns error other than ERROR_INSUFFICIENT_BUFFER\n");
            vEndForms(pRasdduiInfo);            /* Does the clean up */
            return  FALSE;
        }
    }
    RIP("Rasddui!bGetForms:1st call to EnumForms Failed\n");
    /*
     *   If we reach here,  one of the above if(..) statements failed,
     *  and that is NOT good.
     */

    return   FALSE;             /* SHOULD NEVER HAPPEN */
}