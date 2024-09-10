//  ------------------------------------------------------------------------
//  ------------------------------------------------------------------------
VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpszArgv){
    sprintf( msg_err, "ServiceMain - init." );
    DWORD xParam = 1;
    JOB = 1;
//  --
    hServiceStatus = RegisterServiceCtrlHandlerEx( service_name, (LPHANDLER_FUNCTION_EX)ServiceCtrlHandlerEx, (PVOID)&xParam );
    if( !hServiceStatus ){
        prn_err( "RegisterServiceCtrlHandlerEx failed.", GetLastError() );
        return;
    }
// init
    service_status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    service_status.dwCurrentState = SERVICE_START_PENDING;
    service_status.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN | SERVICE_ACCEPT_SESSIONCHANGE;
    service_status.dwWin32ExitCode = ERROR_SERVICE_SPECIFIC_ERROR;
    service_status.dwServiceSpecificExitCode = 0;
    service_status.dwCheckPoint = 0;
    service_status.dwWaitHint = 5000;

    if( !SetServiceStatus( hServiceStatus, &service_status )){
        prn_err( "SetServiceStatus 'NULL' failed.", GetLastError() );
        return;
    }

// Rabota
    service_status.dwCurrentState = SERVICE_RUNNING;
    service_status.dwWin32ExitCode = NO_ERROR;
// Set New
    if( !SetServiceStatus( hServiceStatus, &service_status )){
        prn_err( "SetServiceStatus 'SERVICE_START_PENDING' failed.", GetLastError() );
        return;
    }
//  --
    usleep(10000);
//  ------------------------------------------------------------------------
prn_log( "." );
    SetPriorityClass( GetCurrentProcess(), HIGH_PRIORITY_CLASS );
prn_log( "START SERVICE." );
//  ---------------------------------
    if( !init_conf( service_work, service_name, &conf )){	// возврат всегда "1"
        prn_err( "Init config-data failed. This message can not be", 0 );
    }else{
        if( strcasecmp( conf.log_debug, "Off" ) == 0 ) DEBUG = 0;
        else prn_log( "Logger - DEBUG" );
//  --
        if( strcasecmp( conf.user_proc,   "0" ) == 0 ) prn_log( "WARNING! User Process - disabled." );
        if( strcasecmp( conf.maintenance, "0" ) == 0 ) prn_log( "WARNING! Maintenances - disabled." );
        if( strcasecmp( conf.git_exec,    "0" ) == 0 ) prn_log( "WARNING! Git status   - disabled." );
    }
//  --
    JOB = 2;
// Создаем поток логирования cygwin (сокет /dev/log) для ssh-сессий
    HANDLE hCygWinLogThread = CreateThread( NULL, 0, &CygWinLogThread, (LPVOID)&conf, 0, NULL );
    if( !hCygWinLogThread ){
        prn_err( "LogSocket: Create CygWinLogThread - failed.", GetLastError() );
    }
//  ---------------------------------
    JOB = 3;
    if( !open_send( conf.zbx_server, conf.zbx_port, conf.zbx_host )){
        prn_log( "WARNING! Sender not available: Maintenances - will not be available." );
        strcpy( conf.maintenance, "0" );
    }
//  ---------------------------------
    JOB = 22;
// потоки обслуживания
//    HANDLE hGTimeThread = CreateThread( NULL, 0, &GTimeThread, NULL, 0, NULL );// поток
//  ---------------------------------

    usleep(10000);
    JOB = 101;
    send_sm_string( "SM;SyMon;START;!" );
//  --
//  проверка активных сессий
    DWORD pCount;
    HANDLE hToken;
    PWTS_SESSION_INFO ppSessionInfo = NULL;
    HANDLE hTS = WTSOpenServer( "" );
//  --
    if( WTSEnumerateSessions(hTS, 0, 1, &ppSessionInfo, &pCount )){
        while( pCount ){
            if( ppSessionInfo->State == 0 ){
                if( WTSQueryUserToken( ppSessionInfo->SessionId, &hToken )) entering_info( ppSessionInfo->SessionId, 5, hToken, NULL );
                else prn_err( "WTS Token failed.", GetLastError() );
            }

            ppSessionInfo++;
            pCount--;
        }
    }

//  -----------------------------------
    while( JOB > 100 ){ // главный цикл
        git_test();	// выполнение отложенных (тормозных) функций

        sleep(1);
    }
//  --
//    CloseHandle( hGTimeThread );
    sleep( 2 );
    close_send();
    sprintf( msg_err, "ServiceMain - return." );
//  ------------------------------------------------------------------------
}