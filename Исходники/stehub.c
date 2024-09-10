main(int argc,char *argv[])
#endif
{
    int                 listener_fd, new_fd;
    int                 remotelen;
    int                 port = 0;
    int                 c, on;
    struct sockaddr_in  local_sin, remote_sin;
    static              fd_set  fdset, fdset_saved;
    struct conn_stat   *rconn, *wconn;
#ifdef STE_WINDOWS
    u_long              param = 0; /* FIONBIO コマンドのパラメータ Non-Blocking ON*/
    int                 nRtn;
    WSADATA             wsaData;
    stehubstat_t        stehubstat[1];
    
    nRtn = WSAStartup(MAKEWORD(1, 1), &wsaData);
#endif

    while ((c = getopt(argc, argv, "p:d:")) != EOF){
        switch (c) {
            case 'p':
                port = atoi(optarg);
                break;                
            case 'd':
                debuglevel = atoi(optarg);
                break;
            default:
                print_usage(argv[0]);
        }
    }    

    conn_stat_head->next = NULL;
    conn_stat_head->fd = 0;

    if(( listener_fd = socket( AF_INET, SOCK_STREAM,0 )) < 0 ) {
        SET_ERRNO();
        print_err(LOG_ERR,"socket: %s (%d)\n", strerror(errno), errno);
        exit(1);
    }

    on = 1;
    if((setsockopt(listener_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on))) <0){
        SET_ERRNO();        
        print_err(LOG_ERR,"setsockopt:%s\n", strerror(errno));                
        exit(1);
    }

    if(port == 0)
        port = PORT_NO;
    memset((char *)&remote_sin, 0x0, sizeof(struct sockaddr_in));
    memset((char *)&local_sin, 0x0, sizeof(struct sockaddr_in));
    local_sin.sin_port   = htons((short)port);
    local_sin.sin_family = AF_INET;
    local_sin.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(listener_fd,(struct sockaddr *)&local_sin,sizeof(struct sockaddr_in)) < 0 ){
        SET_ERRNO();
        print_err(LOG_ERR,"bind:%s\n", strerror(errno));                        
        exit(1);
    }

    /*
     * accept() でブロックされるのを防ぐため、non-blocking mode に設定
     */
#ifndef STE_WINDOWS            
    if( fcntl (listener_fd, F_SETFL, O_NONBLOCK) < 0) {
#else
    if( ioctlsocket(listener_fd, FIONBIO, &param) < 0){
#endif                
        SET_ERRNO();
        print_err(LOG_ERR, "Failed to set nonblock: %s (%d)\n",strerror(errno), errno);
        exit(1);
    }

    if(listen(listener_fd, 5) < 0) {
        SET_ERRNO();
        print_err(LOG_ERR,"listen:%s\n", strerror(errno));                                
        exit(1);
    }

    FD_ZERO(&fdset_saved);
    FD_SET(listener_fd, &fdset_saved);

    /*
     * syslog のための設定。Facility は　LOG_USER とする
     * Windows の場合はログファイルをオープンする。
     */
#ifdef STE_WINDOWS
    hStedLog = CreateFile(STEHUB_LOG_FILE,
                          GENERIC_READ|GENERIC_WRITE,
                          FILE_SHARE_READ| FILE_SHARE_WRITE,
                          NULL,
                          CREATE_ALWAYS,
                          FILE_ATTRIBUTE_NORMAL,
                          NULL);
    SetFilePointer(hStedLog, 0, NULL, FILE_END);

    if(isTerminal == FALSE){
        /* サービスとして呼ばれている（コマンドプロンプトから呼ばれていない）場合 */
        stehubServiceStatus.dwServiceType = SERVICE_WIN32;
        stehubServiceStatus.dwCurrentState = SERVICE_START_PENDING;
        stehubServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
        stehubServiceStatus.dwWin32ExitCode = 0;
        stehubServiceStatus.dwServiceSpecificExitCode = 0;
        stehubServiceStatus.dwCheckPoint = 0;
        stehubServiceStatus.dwWaitHint = 0;
    
        /* サービスコントロールハンドラーを登録 */
        stehubServiceStatusHandle = RegisterServiceCtrlHandlerEx(
            "Stehub",                //LPCTSTR
            stehub_svc_ctrl_handler, //LPHANDLER_FUNCTION_EX
            (LPVOID)stehubstat       //LPVOID 
            );

        if (stehubServiceStatusHandle == (SERVICE_STATUS_HANDLE)0){
            return;
        }
    
        stehubServiceStatus.dwCurrentState = SERVICE_RUNNING;
        stehubServiceStatus.dwCheckPoint = 0;
        stehubServiceStatus.dwWaitHint = 0;
    
        if (!SetServiceStatus (stehubServiceStatusHandle, &stehubServiceStatus)){
            // SetServiceStatus が失敗した場合の処理・・        
            print_err(LOG_ERR, "SetServiceStatus Failed\n");
        }
    }
#else
     openlog(basename(argv[0]),LOG_PID,LOG_USER);
#endif
     
    /*
     * ここまではとりあえず、フォアグラウンドで実行。
     * ここからは、デバッグレベル 0 （デフォルト）なら、バックグラウンド
     * で実行し、そうでなければフォアグラウンド続行。
     * Windows の場合は、いづれにしてもフォアグラウンドで実行
     * し、デバッグレベル 1 以上の場合はログをファイルに書く。
     */
    if (debuglevel == 0){
#ifndef STE_WINDOWS             
        print_err(LOG_NOTICE,"Going to background mode\n");
        if(become_daemon() != 0){
            print_err(LOG_ERR,"can't become daemon\n");
            print_err(LOG_ERR,"Exit\n");            
            exit(1);
        }
#else 
        use_log = 1;
#endif    
    }
    print_err(LOG_NOTICE,"Started\n");        

    /*
     * メインループ
     * 仮想 NIC デーモンからの接続要求を待ち、接続後は仮想 NIC デーモン
     * からのデータを待つ。１つの仮想デーモンからのデータを他方に転送する。
     */
    for(;;){
        fdset = fdset_saved;
        if( select(FD_SETSIZE, &fdset, NULL, NULL, NULL) < 0){
            SET_ERRNO();
            print_err(LOG_ERR,"select:%s\n", strerror(errno));
        }

        if(FD_ISSET(listener_fd, &fdset)){
            remotelen = sizeof(struct sockaddr_in);
            if((new_fd = accept(listener_fd,(struct sockaddr *)&remote_sin, &remotelen)) < 0){
                SET_ERRNO();
                if(errno == EINTR || errno == EWOULDBLOCK || errno == ECONNABORTED){
                    print_err(LOG_NOTICE, "accept: %s\n", strerror(errno));
                    continue;
                } else {
                    print_err(LOG_ERR, "accept: %s\n", strerror(errno));                    
                    return(-1);
                }
            }
            
            FD_SET(new_fd, &fdset_saved);
            print_err(LOG_NOTICE,"fd%d: connection from %s\n",new_fd, inet_ntoa(remote_sin.sin_addr));
            add_conn_stat(new_fd, remote_sin.sin_addr);
            /*
             * recv() でブロックされるのを防ぐため、non-blocking mode に設定
             */
#ifndef STE_WINDOWS            
            if (fcntl(new_fd, F_SETFL, O_NONBLOCK) < 0 ) {
#else
                if(ioctlsocket(new_fd, FIONBIO, &param) < 0){
#endif                
                    SET_ERRNO();
                    print_err(LOG_ERR, "fd%d: Failed to set nonblock: %s (%d)\n",
                              new_fd,strerror(errno),errno);
                    return(-1);
                }
                continue;
            }

            for( rconn = conn_stat_head->next ; rconn != NULL ; rconn = rconn->next){
                int rfd, wfd;

                rfd = rconn->fd;
            
                if (FD_ISSET(rfd, &fdset)){
                    int   rsize;
                    char  databuf[SOCKBUFSIZE];
                    char *bufp;
                    int   datalen;

                    bufp = (char *)databuf;
                    rsize = recv(rfd, bufp, SOCKBUFSIZE,0);
                    if(rsize == 0){
                        /*
                         * コネクションが切断されたようだ。
                         * socket を close してループを抜ける
                         */
                        print_err(LOG_ERR,"fd%d: Connection closed by %s\n", rfd, inet_ntoa(rconn->addr));
                        CLOSE(rfd);
                        print_err(LOG_ERR,"fd%d: closed\n", rfd);
                        FD_CLR(rfd, &fdset_saved);
                        delete_conn_stat(rfd);
                        break;
                    }
                    if(rsize < 0){
                        SET_ERRNO();                    
                        /*
                         * 致命的でない error の場合は無視してループを継続
                         */
                        if(errno == EINTR || errno == EWOULDBLOCK){
                            print_err(LOG_NOTICE, "fd%d: recv: %s\n", rfd, strerror(errno));
                            continue;
                        }
                        /*
                         * エラーが発生したようだ。
                         * socket を close して forループを抜ける
                         */
                        print_err(LOG_ERR,"fd%d: recv: %s\n", rfd,strerror(errno));
                        CLOSE(rfd);
                        print_err(LOG_ERR,"fd%d: closed\n", rfd);
                        FD_CLR(rfd, &fdset_saved);
                        delete_conn_stat(rfd);
                        break;
                    }
                    /*
                     * 他の仮想 NIC にパケットを転送する。
                     * 「待ち」が発生すると、パフォーマンスに影響があるので、EWOULDBLOCK
                     *  の場合は配送をあきらめる。
                     */
                    for(wconn = conn_stat_head->next ; wconn != NULL ; wconn = wconn->next){
                    
                        wfd = wconn->fd;

                        if (rfd == wfd)
                            continue;

                        if( debuglevel > 1){
                            print_err(LOG_ERR,"fd%d(%s) ==> ", rfd, inet_ntoa(rconn->addr));
                            print_err(LOG_ERR,"fd%d(%s)\n", wfd,inet_ntoa(wconn->addr));
                        }
                
                        if ( send(wfd, bufp, rsize, 0) < 0){
                            SET_ERRNO();                    
                            if(errno == EINTR || errno == EWOULDBLOCK ){
                                print_err(LOG_NOTICE,"fd%d: send: %s\n", wfd ,strerror(errno));
                                continue;
                            } else {
                                print_err(LOG_ERR,"fd%d: send: %s (%d)\n",wfd,strerror(errno), errno);
                                CLOSE(wfd);
                                print_err(LOG_ERR,"fd%d: closed\n", wfd);
                                FD_CLR(wfd, &fdset_saved);
                                delete_conn_stat(wfd);
                                break;                            
                            }
                        }                    
                    } /* End of loop for send()ing */
                }
            } /* End of loop for each connection */
        } /* End of main loop */
}

#ifdef STE_WINDOWS
/**************************************************************************
 * Windows の場合の main()
 * 
 * 引数が -I もしくは -U だった場合には本プログラム（仮想 HUB デーモン）
 * を Windows のサービスとして登録/登録解除する。
 * それ以外の引数が渡された場合には ste_svc_main() を直接呼び出し、引数も
 * そのまま ste_svc_main() に渡す。
 * 
 * 引数(argvとして）:
 * 
 *      -I : サービスとして登録。
 *      -U : 登録解除
 * 
 **************************************************************************/
int WINAPIV
main(int argc, char *argv[])
{
    int c;

    SERVICE_TABLE_ENTRY  DispatchTable[] = {
        {  "Stehub", stehub_svc_main},
        {  NULL,   NULL         }
    };

    isTerminal = _isatty(_fileno(stdout))? TRUE:FALSE;    

    //
    // 引数が無ない場合。
    // コマンドプロンプトから呼ばれた時は stehub_svc_main() を呼び、
    // そうでなければ StartServiceCtlDispatcher() を呼ぶ。
    //
    if(argc == 1 ){
        if(isTerminal == TRUE){
            stehub_svc_main(argc, argv);
            return(0);
        } else {
            StartServiceCtrlDispatcher(DispatchTable);
            return(0);
        }
    }
    
    while((c = getopt(argc, argv, "IU")) != EOF ){        
        switch(c){
            case 'I':
                // stehub.exe をサービスとして登録
                if(stehub_install_svc())
                    printf("Service Installed Sucessfully\n");
                else
                    printf("Error Installing Service\n");
                break;
            case 'U':
                // stehub.exe のサービスとして登録を解除
                if(stehub_delete_svc())
                    printf("Service UnInstalled Sucessfully\n");
                else
                    printf("Error UnInstalling Service\n");
                break;
            default :
                //
                // 引数が -U、-I でなければコマンドプロンプト内で
                // stehub.exe を起動したいのだと判断し、引数を全て
                // stehub_svc_main() に渡して呼び出す。
                //
                stehub_svc_main(argc, argv);
                return(0);
        }
    }
    return(0);    
}

/****************************************
 * Windows サービス登録ルーチン
 * 
 ****************************************/
BOOL stehub_install_svc()
{
    LPCTSTR lpszBinaryPathName;
    TCHAR strDir[1024];
    HANDLE schSCManager,schService;
    
    GetCurrentDirectory(1024, strDir);
    strcat((char *)strDir, "\\stehub.exe"); 
    schSCManager = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS);

    if (schSCManager == NULL) 
        return FALSE;

    lpszBinaryPathName=strDir;

    schService = CreateService(schSCManager,"Stehub", 
                               "Stehub Virtual HUB daemon", // 表示用サービス名
                               SERVICE_ALL_ACCESS,        // アクセス
                               SERVICE_WIN32_OWN_PROCESS, // サービスタイプ
                               SERVICE_DEMAND_START,      // スタートタイプ
                               SERVICE_ERROR_NORMAL,      // エラーコントロールタイプ
                               lpszBinaryPathName,        // バイナリへのパス
                               NULL, // No load ordering group 
                               NULL, // No tag identifier 
                               NULL, // No dependencies
                               NULL, // LocalSystem account
                               NULL);// No password

    if (schService == NULL)
        return FALSE; 

    CloseServiceHandle(schService);
    return TRUE;
}

/****************************************
 * Windows サービス登録解除ルーチン
 * 
 ****************************************/
BOOL stehub_delete_svc()
{
    HANDLE schSCManager;
    SC_HANDLE hService;
    schSCManager = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS);

    if (schSCManager == NULL)
        return FALSE;
    hService=OpenService(schSCManager, "Stehub", SERVICE_ALL_ACCESS);
    if (hService == NULL)
        return FALSE;
    if(DeleteService(hService)==0)
        return FALSE;
    if(CloseServiceHandle(hService)==0)
        return FALSE;

    return TRUE;
}

/******************************************************************************
 * stehub_svc_ctrl_handler()
 * 
 * サービスステータスハンドラー
 * DEVICEEVENT を拾うためには Handler ではなく、HandlerEx じゃないといけないらしい。
 * http://msdn.microsoft.com/library/default.asp?url=/library/en-us/dllproc/base/handlerex.asp
 *
 * まったく呼ばれていないような・・？
 ******************************************************************************/
DWORD WINAPI
stehub_svc_ctrl_handler(
    DWORD dwControl,
    DWORD dwEventType,
    LPVOID lpEventData,  
    LPVOID lpContext
    )
{
    PDEV_BROADCAST_HDR  p      = (PDEV_BROADCAST_HDR) lpEventData;
    WPARAM              wParam = (WPARAM) dwEventType;
    stehubstat_t         *stehubstat = NULL;

    stehubstat = (stehubstat_t *)lpContext;

    if(debuglevel > 1){
        print_err(LOG_DEBUG, "Service Status Handler stehub_svc_ctrl_handler called\n");
    }
    
    switch(dwControl){
        case SERVICE_CONTROL_DEVICEEVENT:
            break;
        case SERVICE_CONTROL_PAUSE: 
            stehubServiceStatus.dwCurrentState = SERVICE_PAUSED;
            break;
        case SERVICE_CONTROL_CONTINUE:
            stehubServiceStatus.dwCurrentState = SERVICE_RUNNING;
            break;
        case SERVICE_CONTROL_STOP:
            stehubServiceStatus.dwWin32ExitCode = 0;
            stehubServiceStatus.dwCurrentState = SERVICE_STOPPED;
            stehubServiceStatus.dwCheckPoint = 0;
            stehubServiceStatus.dwWaitHint = 0;

            SetServiceStatus (stehubServiceStatusHandle,&stehubServiceStatus);

            break;
        case SERVICE_CONTROL_INTERROGATE:
            break; 
    }
    return NO_ERROR;
}