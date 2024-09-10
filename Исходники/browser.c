/**************************** callBrowser (WIN32) ************************/
int callBrowser(char *url)
/* Returns non-zero on success, 0 on failure */
/* Should use the default browser            */
/* Does nothing with "quit"                  */
{
    static int first=1;
    static char *ComSpec;
    char command[BUFSIZ];
    intptr_t status;

    /* Handle quit */
    if(!strcmp(url,"quit")) {
        /* For compatibility, but do nothing */
        return(3);
    }

    /* Get ComSpec for the command shell (should be defined) */
    if (first) {
        first=0;
        ComSpec = getenv("ComSpec");
    }
    if (!ComSpec) return(0);     /* Abort with no message like the UNIX version*/
    /* Spawn the process that handles a url */
#if 0
    /* Works, command window that goes away */
    sprintf(command,"start \"%s\"",url);
    status = _spawnl(_P_WAIT, ComSpec, ComSpec, "/C", command, NULL);

    /* Works, command window that goes away */
    sprintf(command,"start \"%s\"",url);
    status = _spawnl(_P_DETACH, ComSpec, ComSpec, "/C", command, NULL);

    /* Works, command window that goes away */
    sprintf(command,"\"%s\"",url);
    status = _spawnl(_P_NOWAIT, "c:\\windows\\command\\start.exe",
                     "c:\\windows\\command\\start.exe", command, NULL);

    /* Works, command window that goes away */
    sprintf(command,"\"%s\"",url);
    status = _spawnl(_P_WAIT, ComSpec, "start", command, NULL);

    /* Works, command window that goes away */
    sprintf(command,"start \"%s\"",url);
    status = _spawnl(_P_NOWAIT, ComSpec, ComSpec, "/C", command, NULL);

    /* Doesn't work on 95 (No such file or directory), works on NT */
    sprintf(command,"start \"%s\"",url);
    status = _spawnl(_P_NOWAIT, ComSpec, "/C", command, NULL);

    /* Works on 95, not NT, no command window
       *   No start.exe for NT */
    sprintf(command,"\"%s\"",url);
    status = _spawnlp(_P_DETACH, "start", "start", command, NULL);

    /* Doesn't work on 95 */
    sprintf(command,"\"start %s\"",url);
    status = _spawnl(_P_DETACH, ComSpec, ComSpec, "/C", command, NULL);
#else
    /* This seems to work on 95 and NT, with a command box on 95
       *   It may have trouble if the URL has spaces */
    sprintf(command,"start %s",url);
    status = _spawnl(_P_DETACH, ComSpec, ComSpec, "/C", command, NULL);
#endif
    if(status == -1) {
        char *errstring=strerror(errno);

        printf("\ncallBrowser: Cannot start browser:\n"
               "%s %s\n"
               "  %s\n",ComSpec,command,errstring);
        /* 	perror("callBrowser:"); */
        return(0);
    }
    return(1);
}