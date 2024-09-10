LONG
PsDocumentProperties(
    HWND        hwnd,
    HANDLE      hPrinter,
    PWSTR       pDeviceName,
    PDEVMODE    pdmOutput,
    PDEVMODE    pdmInput,
    DWORD       fMode
    )

/*++

Arguments:

    hwnd - Handle to the parent window of the document properties dialog box.

    hPrinter - Handle to a printer object.

    pDeviceName - Points to a null-terminated string that specifies
        the name of the device for which the document properties dialog
        box should be displayed.

    pdmOutput - Points to a DEVMODE structure that receives the document
        properties data specified by the user.

    pdmInput - Points to a DEVMODE structure that initializes the dialog
        box controls. This parameter can be NULL.

    fmode - Specifies a mask of flags that determine which operations
        the function performs.

Return Value:

    > 0 if successful
    = 0 if canceled
    < 0 if error

--*/

{
    COMPROPSHEETUIHEADER comPropSheetUIHdr;
    DOCUMENTPROPERTYHEADER docPropHdr;

    memset(&comPropSheetUIHdr, 0, sizeof(comPropSheetUIHdr));
    comPropSheetUIHdr.cbSize = sizeof(comPropSheetUIHdr);
    comPropSheetUIHdr.lParam = (LPARAM) &docPropHdr;
    comPropSheetUIHdr.hWndParent = hwnd;
    comPropSheetUIHdr.Flags = CPSUIHDRF_NOAPPLYNOW | CPSUIHDRF_PROPTITLE;
    comPropSheetUIHdr.pTitle = pDeviceName;
    comPropSheetUIHdr.IconID = IDI_CPSUI_PRINTER2;
    comPropSheetUIHdr.hInst = ghInstance;

    memset(&docPropHdr, 0, sizeof(docPropHdr));
    docPropHdr.cbSize = sizeof(docPropHdr);
    docPropHdr.hPrinter = hPrinter;
    docPropHdr.pszPrinterName = pDeviceName;
    docPropHdr.pdmIn = pdmInput;
    docPropHdr.pdmOut = pdmOutput;
    docPropHdr.fMode = fMode;

    return DrvDocumentPropertySheets(&comPropSheetUIHdr, NULL);
}