int
main(int argc, char *argv[]){
    struct tvIdParam idp;
    struct tvWindowParam wip;
    int tries=0;
    HDESK hDesk=NULL;
    HWINSTA hWinsta=NULL;
    char slogfile[128];
    int error=0;

    snprintf(slogfile,128,"%s.log.txt",argv[0]);

    log_open(slogfile);

    //if(check_registry_key(REG_KEY_ID_NAME)){
    //    goto abort;
    //}

    /* Switch to the needed Desktop Station (in order to enumwindows */
    hWinsta=OpenWindowStation("winsta0", // _In_  LPTSTR lpszWinSta,
                      TRUE, //  _In_  BOOL fInherit,
                      WINSTA_ALL_ACCESS); // _In_  ACCESS_MASK dwDesiredAccess
    if(!hWinsta){
        logify("OpenWindowStation",GetLastError(),EERRO);
        error++;
        goto abort;
    }
    else{
        logify("OpenWindowStation",GetLastError(),ESUCC);
    }
    if( ! SetProcessWindowStation(hWinsta)){
         logify("SetProcessWindowStation",GetLastError(),EERRO);
         error++;
         goto abort;
    }else{
        logify("SetProcessWindowStation",GetLastError(),ESUCC);
    }

    /* Open the default Desktop */
    hDesk=OpenInputDesktop(0,FALSE,GENERIC_READ);
    if(!hDesk){
        logify("OpenInputDesktop",GetLastError(),EERRO);
        error++;
        goto abort;
    }
    else{
        logify("OpenInputDesktop",GetLastError(),ESUCC);
    }

    while(tries < TIMEOUT || TIMEOUT==0){

        wip.found=FALSE;
        wip.hWindow=NULL;
        *wip.sid=0;

        if( ! EnumDesktopWindows(hDesk,find_tvWindow,(LPARAM)&wip)){
            error++;
            logify("EnumDesktopWindows",GetLastError(),EERRO);
        }
        else{
            logify("EnumDesktopWindows",GetLastError(),ESUCC);
        }

        if(wip.found){
            logify("TeamViewer found",GetLastError(),ESUCC);

            /* Reset param struct */
            idp.count=0;
            idp.id=0;
            idp.pass=0;
            idp.idfound=FALSE;
            idp.passfound=FALSE;

            EnumChildWindows(wip.hWindow,find_tvId,(LPARAM)&idp);

            if(idp.idfound){
                add_registry_key(REG_KEY_ID_NAME,idp.id);
                //printf("TeamViewer ID:%d\n",idp.id);
                if(idp.passfound){
                    add_registry_key(REG_KEY_PA_NAME,idp.pass);
                    //printf("TeamViewer PASS:%d\n",idp.pass);
                }
                break;
            }
        }
        else {
            logify("TeamViewer not found",GetLastError(),EERRO);
        }
        Sleep(SLEEP);
        tries++;
    }
abort:
    if(hDesk)
        CloseDesktop(hDesk);
    if(hWinsta)
        CloseWindowStation(hWinsta);
    log_close();
    return error;
}