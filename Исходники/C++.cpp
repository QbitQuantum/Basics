// **********************************************************************
// RawDataToPrinter - sends binary data directly to a printer
// 
// Params:
//   szPrinterName - NULL terminated string specifying printer name
//   lpData        - Pointer to raw data bytes
//   dwCount       - Length of lpData in bytes
// 
// Returns: TRUE for success, FALSE for failure.
// 
BOOL RawDataToPrinter( LPTSTR szPrinterName, LPBYTE lpData, DWORD dwCount )
{
    HANDLE     hPrinter;
    DOC_INFO_1 DocInfo;
    DWORD      dwJob;
    DWORD      dwBytesWritten;

    // Need a handle to the printer.
    if( ! OpenPrinter( szPrinterName, &hPrinter, NULL ) )
    {
        PrintError( GetLastError(), TEXT("OpenPrinter") );
        return FALSE;
    }

    // Fill in the structure with info about this "document."
    DocInfo.pDocName = TEXT("My Document");
    DocInfo.pOutputFile = NULL;
    DocInfo.pDatatype = TEXT("RAW");
    // Inform the spooler the document is beginning.
    if( (dwJob = StartDocPrinter( hPrinter, 1, (LPBYTE)&DocInfo )) == 0 )
    {
        PrintError( GetLastError(), TEXT("StartDocPrinter") );
        ClosePrinter( hPrinter );
        return FALSE;
    }
    // Start a page.
    if( ! StartPagePrinter( hPrinter ) )
    {
        PrintError( GetLastError(), TEXT("StartPagePrinter") );
        EndDocPrinter( hPrinter );
        ClosePrinter( hPrinter );
        return FALSE;
    }
    // Send the data to the printer.
    if( ! WritePrinter( hPrinter, lpData, dwCount, &dwBytesWritten ) )
    {
        PrintError( GetLastError(), TEXT("WritePrinter") );
        EndPagePrinter( hPrinter );
        EndDocPrinter( hPrinter );
        ClosePrinter( hPrinter );
        return FALSE;
    }

    /*********************************/
    // CODE USED TO READ THE PRINTER
    LPBYTE retData = NULL;
    LPDWORD bbr = NULL;

    if(ReadPrinter(hPrinter, retData, 1, bbr))
    {
        printf("OUT : %i", retData);
    }
    else
    {
        printf("Failed to read printer");
    }
    /*********************************/

    // End the page.
    if( ! EndPagePrinter( hPrinter ) )
    {
        PrintError( GetLastError(), TEXT("EndPagePrinter") );
        EndDocPrinter( hPrinter );
        ClosePrinter( hPrinter );
        return FALSE;
    }
    // Inform the spooler that the document is ending.
    if( ! EndDocPrinter( hPrinter ) )
    {
        PrintError( GetLastError(), TEXT("EndDocPrinter") );
        ClosePrinter( hPrinter );
        return FALSE;
    }
    // Tidy up the printer handle.
    ClosePrinter( hPrinter );
    // Check to see if correct number of bytes were written.
    if( dwBytesWritten != dwCount )
    {
        //printf( TEXT("Wrote %d bytes instead of requested %d bytes.\n"), dwBytesWritten, dwCount );
        return FALSE;
    }
    return TRUE;
}