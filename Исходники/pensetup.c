UINT
CreatePenSetupOI(
    PPRINTERINFO    pPI,
    POPTITEM        pOptItem,
    POIDATA         pOIData
    )

/*++

Routine Description:




Arguments:




Return Value:




Author:

    06-Nov-1995 Mon 16:23:36 created  


Revision History:


--*/

{
    PPENDATA    pPenData;
    POPTITEM    pOI;
    POPTITEM    pOIPen;
    POPTTYPE    pOTPen;
    EXTRAINFO   EI;
    UINT        i;
    UINT        j;
    UINT        MaxPens;
    UINT        cPenClr;
    WCHAR       Buf[128];
    DWORD       dwchSize;
    HRESULT     hr;

    MaxPens  = (UINT)pPI->pPlotGPC->MaxPens;
    cPenClr  = PC_IDX_TOTAL;

    if (!pOptItem) {

        return(((MaxPens + 1) * PRK_MAX_PENDATA_SET) + 1);
    }

    EI.Size  = (UINT)((LoadString(hPlotUIModule,
                                  IDS_PEN_NUM,
                                  Buf,
                                  (sizeof(Buf) / sizeof(WCHAR)) - 1)
                       + 5) * sizeof(WCHAR));
    dwchSize = EI.Size;
    pPenData = PI_PPENDATA(pPI);
    pOTPen   = NULL;
    pOIPen   = NULL;
    pOI      = pOptItem;

    //
    // First: Create PenSetup: HEADER
    //

    if (CreateOPTTYPE(pPI, pOI, pOIData, 0, NULL)) {

        pOI++;
    }

    //
    // Now Create Each pen set
    //

    for (i = (UINT)IDS_PENSET_FIRST; i <= (UINT)IDS_PENSET_LAST; i++) {

        if (CreateOPTTYPE(pPI, pOI, &OIPenSet, 0, NULL)) {

            pOI->pName     = (LPTSTR)UIntToPtr(i);
            pOI->Flags    |= OPTIF_EXT_IS_EXTPUSH;
            pOI->pExtPush  = &PenSetExtPush;
        }

        pOI++;

        for (j = 1; j <= MaxPens; j++, pOI++, pPenData++) {

            if (CreateOPTTYPE(pPI, pOI, &OIPenNum, cPenClr, &EI)) {

                if (pOTPen) {

                    pOI->pOptType = pOTPen;

                } else {

                    pOTPen  = pOI->pOptType;
                    cPenClr = 0;
                }

                if (pOIPen) {

                    pOI->pName = pOIPen->pName;
                    pOIPen++;

                } else {

                    pOI->pName = (LPTSTR)EI.pData;
                    hr = StringCchPrintfW(pOI->pName, dwchSize, L"%ws%u", Buf, j);
                    if ( FAILED(hr) )
                    {
                        PLOTASSERT(0,
                                   "Couldn't format string into pName",
                                   SUCCEEDED(hr), 0);

                    }
                }
            }

            pOI->Sel = pPenData->ColorIdx;
        }

        if (!pOIPen) {

            EI.Size = 0;
            pOIPen  = pOI;
        }

        pOIPen -= MaxPens;
    }

    return (UINT)(pOI - pOptItem);
}