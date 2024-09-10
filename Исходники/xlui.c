PUIDATA
FillUiData(
    HANDLE      hPrinter,
    PDEVMODE    pdmInput,
    INT         caller
    )

/*++

Routine Description:

    Fill in the global data structure used by the driver user interface

Arguments:

    hPrinter - Handle to the printer
    pdmInput - Pointer to input devmode, NULL if there is none
    caller - Identifier who the caller is

Return Value:

    Pointer to UIDATA structure, NULL if there is an error

--*/

{
    PRINTER_INFO_2 *pPrinterInfo2 = NULL;
    PUIDATA         pUiData = NULL;
    HANDLE          hheap = NULL;
    DWORD           cbNeeded;

    //
    // Create a heap to manage memory
    // Allocate memory to hold UIDATA structure
    // Load printer description data
    // Retrieve printer properties data from registry
    // Get printer info from the spooler
    // Copy the driver name
    //

    if (! (hheap = HeapCreate(0, 4096, 0)) ||
        ! (pUiData = HeapAlloc(hheap, HEAP_ZERO_MEMORY, sizeof(UIDATA))) ||
        ! (pUiData->pmpd = LoadMpdFile(hPrinter)) ||
        ! GetPrinterProperties(&pUiData->prnprop, hPrinter, pUiData->pmpd) ||
        ! (pPrinterInfo2 = MyGetPrinter(hPrinter, 2)) ||
        ! (pUiData->pDriverName = DuplicateUnicodeString(pPrinterInfo2->pDriverName, hheap)))
    {
        if (pUiData && pUiData->pmpd)
            UnloadMpdFile(pUiData->pmpd);

        if (hheap)
            HeapDestroy(hheap);

        MemFree(pPrinterInfo2);
        return NULL;
    }

    pUiData->hPrinter = hPrinter;
    pUiData->hheap = hheap;
    pUiData->signature = DRIVER_SIGNATURE;

    //
    // Add printer-specific forms to the global forms database
    //

    if (! AddDriverForms(hPrinter, pUiData->pmpd)) {

        Error(("Failed to add printer-specific forms\n"));
    }

    //
    // If we're doing document properties, combine input devmode with defaults
    //

    if (caller == DOCPROPDLG) {

        FORM_INFO_1 formInfo;
        WCHAR       formName[CCHFORMNAME];

        //
        // Start with driver default devmode
        //
    
        DriverDefaultDevmode(&pUiData->devmode, NULL, pUiData->pmpd);

        //
        // Merge with system defaults and the input devmode
        //
    
        if (! MergeDevmode(&pUiData->devmode, pPrinterInfo2->pDevMode, pUiData->pmpd)) {

            Error(("Invalid system default devmode\n"));
        }

        if (! MergeDevmode(&pUiData->devmode, pdmInput, pUiData->pmpd)) {

            Error(("Invalid input devmode\n"));
        }

        //
        // Validate the form requested by the input devmode
        //

        if (! ValidDevmodeForm(hPrinter, &pUiData->devmode.dmPublic, &formInfo, formName)) {

            Error(("Invalid form requested\n"));
        }

        //
        // Convert public devmode fields to printer feature selections
        //

        DevmodeFieldsToOptions(&pUiData->devmode,
                               pUiData->devmode.dmPublic.dmFields,
                               pUiData->pmpd);

        //
        // Look for conflicts between feature selections
        //
        
        CombineDocumentAndPrinterFeatureSelections(pUiData->pmpd,
                                                   pUiData->devmode.dmPrivate.options,
                                                   pUiData->devmode.dmPrivate.options,
                                                   pUiData->prnprop.options);
    }

    MemFree(pPrinterInfo2);
    return pUiData;
}