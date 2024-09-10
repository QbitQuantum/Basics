DWORD
CheckPrinterJobToken(
    LPCWSTR string,
    LPCWSTR pSecondPart,
    PDWORD pTypeofHandle,
    PINIPRINTER* ppIniPrinter,
    PINIJOB* ppIniJob,
    PHANDLE phReadFile,
    const PINISPOOLER pIniSpooler
    )
{
    HANDLE  hImpersonationToken;
    DWORD Position;
    DWORD JobId;
    PINIPRINTER pIniPrinter;
    PINIJOB pIniJob, pCurrentIniJob;

    if( wcsncmp( pSecondPart, L"Job ", 4 ) != STRINGS_ARE_EQUAL ||
        !( pIniPrinter = FindPrinter( string ))){

        return ROUTER_UNKNOWN;
    }

    //
    //  Get the Job ID ",Job xxxx"
    //
    pSecondPart += 4;

    JobId = Myatol( (LPWSTR)pSecondPart );

    pIniJob = FindJob( pIniPrinter, JobId, &Position );

    if( pIniJob == NULL ) {

        DBGMSG( DBG_WARN, ("OpenPrinter failed to find Job %d\n", JobId ));
        return ROUTER_UNKNOWN;
    }

    DBGMSG( DBG_TRACE, ("OpenPrinter: pIniJob->cRef = %d\n", pIniJob->cRef));

    if( pIniJob->Status & JOB_DIRECT ) {

        SplInSem();
        INCJOBREF( pIniJob );

        *pTypeofHandle |= PRINTER_HANDLE_JOB | PRINTER_HANDLE_DIRECT;
        goto Success;
    }

    //
    //  If this job is assigned to a port
    //  Then pick up the correct chained jobid file instead of the master
    //  JobId.
    //


    if ( pIniJob->pCurrentIniJob != NULL ) {

        SPLASSERT( pIniJob->pCurrentIniJob->signature == IJ_SIGNATURE );

        DBGMSG( DBG_TRACE,("CheckPrinterJobToken pIniJob %x JobId %d using chain JobId %d\n",
                pIniJob, pIniJob->JobId, pIniJob->pCurrentIniJob->JobId ));


        pCurrentIniJob = pIniJob->pCurrentIniJob;


        SPLASSERT( pCurrentIniJob->signature == IJ_SIGNATURE );

    } else {

        pCurrentIniJob = pIniJob;

    }


    GetFullNameFromId( pCurrentIniJob->pIniPrinter,
                       pCurrentIniJob->JobId,
                       TRUE,
                       (LPWSTR)string,
                       FALSE );


    //  !! BUGBUG !!
    //  Even a user without previledge can open a ", JOB #"
    //  if he is physically running on the machine.


    hImpersonationToken = RevertToPrinterSelf();

    *phReadFile = CreateFile( string,
                  GENERIC_READ,
                  FILE_SHARE_READ |
                  FILE_SHARE_WRITE,
                  NULL,
                  OPEN_EXISTING,
                  FILE_ATTRIBUTE_NORMAL |
                  FILE_FLAG_SEQUENTIAL_SCAN,
                  NULL );

    ImpersonatePrinterClient( hImpersonationToken );

    if( *phReadFile != INVALID_HANDLE_VALUE ) {

    DBGMSG( DBG_TRACE, ("OpenPrinter JobID %d pIniJob %x CreateFile( %ws ), hReadFile %x success", JobId, pIniJob, string, *phReadFile ));

        SplInSem();
    INCJOBREF( pIniJob );

        *pTypeofHandle |= PRINTER_HANDLE_JOB;
        goto Success;
    }

    DBGMSG( DBG_WARNING, ("LocalOpenPrinter CreateFile(%ws) GENERIC_READ failed : %d\n", string, GetLastError()));
    SPLASSERT( GetLastError( ));

    return ROUTER_STOP_ROUTING;

Success:

    *ppIniJob = pIniJob;
    *ppIniPrinter = pIniPrinter;
    return ROUTER_SUCCESS;
}