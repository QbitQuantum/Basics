void notify_ADMINX(Connection *xConn,PCStr(admin),PCStr(what),PCStr(body))
{   FILE *tmp;
    FILE *bt;
    Connection ConnBuff,*Conn = &ConnBuff;
    CStr(head,1024);
    CStr(me,128);
    CStr(date,128);
    CStr(load,128);
    CStr(cwd,1024);
    CStr(uname,128);
    int now;
    const char *bugbox = "*****@*****.**";
    CStr(msgid,1024);
    CStr(buf,1024);

    if( strncasecmp(what,"sig",3) != 0 )
        if( strncasecmp(what,"failed",6) != 0 )
            if( strncasecmp(what,"modified",8) != 0 )
                if( strncasecmp(what,"approved",8) != 0 )
                    if( strncasecmp(what,"detected",8) != 0 )
                        if( strncasecmp(what,"[",1) != 0 ) /* abort in child process */
                            return;

    if( admin == NULL || *admin == 0 )
        admin = getADMIN1();

    now = time(NULL);
    if( xConn )
        *Conn = *xConn;
    else	bzero(Conn,sizeof(Connection));
    tmp = TMPFILE("NOTIFY");

    head[0] = 0;
    if( gethostname(me,sizeof(me)) != 0 )
        strcpy(me,"?");
    sprintf(msgid,"%d.%d.%d@%s",getpid(),itime(0),getuid(),me);

    StrftimeLocal(AVStr(date),sizeof(date),TIMEFORM_RFC822,now,0);
    Xsprintf(TVStr(head),"Subject: DeleGate-Report: %s\r\n",what);
    Xsprintf(TVStr(head),"From: [%d]@%s\r\n",getuid(),me);
    Xsprintf(TVStr(head),"To: %s (DeleGate ADMIN)\r\n",admin);
    Xsprintf(TVStr(head),"Reply-To: %s\r\n",bugbox);
    Xsprintf(TVStr(head),"Date: %s\r\n",date);
    Xsprintf(TVStr(head),"Message-Id: <%s>\r\n",msgid);
    Xsprintf(TVStr(head),"Content-Type: text/plain\r\n");
    fprintf(tmp,"%s\r\n",head);
    fprintf(tmp,"PLEASE FORWARD THIS MESSAGE TO <%s>.\r\n",bugbox);
    fprintf(tmp,"IT WILL BE HELPFUL FOR DEBUGGING.\r\n");
    fprintf(tmp,"\r\n");
    fprintf(tmp,"%s",head);
    fprintf(tmp,"Event: %s\r\n",what);
    Uname(AVStr(uname));
    fprintf(tmp,"Version: %s (%s)\r\n",DELEGATE_verdate(),uname);
    fprintf(tmp,"Host: %s\r\n",me);
    fprintf(tmp,"Owner: uid=%d/%d, gid=%d/%d\r\n",
            geteuid(),getuid(),getegid(),getgid());
    StrftimeLocal(AVStr(date),sizeof(date),TIMEFORM_RFC822,START_TIME,0);
    fprintf(tmp,"Started: %s\r\n",date);
    fprintf(tmp,"Pid: %d\r\n",getpid());
    cwd[0] = 0;
    IGNRETS getcwd(cwd,sizeof(cwd));
    fprintf(tmp,"Cwd: %s\r\n",cwd);
    strfLoadStat(AVStr(load),sizeof(load),"%L (%l)",now);
    fprintf(tmp,"Load: %s\r\n",load);
    fprintf(tmp,"Stack: %X %d/%d\r\n",p2i(STACK_PEAK),ll2i(STACK_BASE-STACK_PEAK),
            STACK_SIZE);
    fprintf(tmp,"\r\n");

    if( iamServer() ) {
    } else {
        fprintf(tmp,"Client-Proto: %s\r\n",CLNT_PROTO);
        fprintf(tmp,"Client-Host: %s:%d\r\n",Client_Addr(buf),Client_Port);
        if( TeleportHost[0] )
            fprintf(tmp,"Rident-Host: %s:%d..%s:%d\r\n",TelesockHost,TelesockPort,
                    TeleportAddr,TeleportPort);
        fprintf(tmp,"\r\n");
    }
    fprintf(tmp,"%s\r\n",body);

    /*
    	if( strncasecmp(what,"sig",3) == 0 || *what == '[' ){
    */
    if( strncasecmp(what,"sig",3) == 0
            || strncasecmp(what,"failed",6) == 0
            || *what == '[' ) {
        fprintf(tmp,"--iLog--begin\r\n");
        iLOGdump1(tmp,0);
        fprintf(tmp,"--iLog--end\r\n");

        fprintf(tmp,"\r\n");
        fprintf(tmp,"--AbortLog--begin\r\n");
        putAbortLog(tmp);
        fprintf(tmp,"--AbortLog--end\r\n");
    }

    if( strncasecmp(what,"sig",3) == 0 ) {
        int btout[2];
        double Start = Time();
        int rcc;

        fprintf(tmp,"\r\n");
        fprintf(tmp,"--BackTrace--begin\r\n");
        fflush(tmp);

        if( pipe(btout) == 0 ) {
            setNonblockingIO(btout[1],1);
            bt = fdopen(btout[1],"w");
            putBackTrace(bt);
            fclose(bt);
            bt = fdopen(btout[0],"r");
            rcc = file_copyTimeout(bt,tmp,NULL,128*1024,NULL,15);
            fclose(bt);
            sv1log("BatckTrace: %dB / %.1fs\n",rcc,Time()-Start);
        } else {
            bt = TMPFILE("BackTrace");
            putBackTrace(bt);
            fseek(bt,0,0);
            copyfile1(bt,tmp);
            fclose(bt);
        }
        fprintf(tmp,"\r\n");
        fprintf(tmp,"--BackTrace--end\r\n");
    }

    fflush(tmp);
    fseek(tmp,0,0);
    if( curLogFp() ) {
        CStr(line,1024);
        while( fgets(line,sizeof(line),tmp) != NULL )
            fprintf(curLogFp(),"--ABORT-- %s",line);
        fseek(tmp,0,0);
    }
    Conn->co_mask = (CONN_NOPROXY | CONN_NOMASTER);
    sendmail1(Conn,admin,admin,tmp,NULL);
    fclose(tmp);
}