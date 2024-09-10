int sendsms (char *host, char *gsmnumber, char *gsmtext, int checksent,
             char *port)
{
    const char urlconfirm[] =
        "GET /sendsms.php?sent=cli&to=%s&fromform=true&confirmation=on&text=%s HTTP/1.1\r\n"
        "Host:%s\r\n" "Connection: close\r\n\r\n";
    const char urlnoconfirm[] =
        "GET /sendsms.php?sent=cli&to=%s&fromform=true&text=%s HTTP/1.1\r\n"
        "Host:%s\r\n" "Connection: close\r\n\r\n";
    const char urlcontinuecheck[] =
        "GET /sendsms.php?sent=cli&confirmation=on&msgid=%s HTTP/1.1\r\n"
        "Host:%s\r\n" "Connection: close\r\n\r\n";
    char *buffer, *smsreq, *urltemplate, *out, *smsid = NULL, *smsstatus;

    int sd, s, flags = 0, i;


    struct addrinfo hints;

    struct addrinfo *result, *rp;

    smsid = (char *) malloc (50);
    memset (smsid, 0x0, 14);

    memset (&hints, 0x0, sizeof (struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;
    s = getaddrinfo (host, port, &hints, &result);
    if (s != 0) {
        printf ("SMSTATUS: GETADDRINFO FAILED - %s\n", gai_strerror (s));
        return -1;
    }

    for (i = 0; i < 10; i++) {
        for (rp = result; rp != NULL; rp = rp->ai_next) {
            sd = socket (rp->ai_family, rp->ai_socktype, rp->ai_protocol);
            if (sd == -1)
                continue;
#ifndef MINGW32
#define SHUTDOWN(fd)    { shutdown((fd),0); close((fd)); }
            flags = fcntl (sd, F_GETFL, 0);
#else
#define fcntl(fd,b,c) { u_long arg=1;ioctlsocket(fd, c, &arg); }
#define SHUTDOWN(fd) { shutdown((fd),0); closesocket((fd)); }
#define sleep(x) Sleep((x)*1000)
            flags = 0;
#endif
            fcntl (sd, F_SETFL, flags);
            if (connect (sd, rp->ai_addr, rp->ai_addrlen) != -1)
                break;
            close (sd);
        }
        if (rp == NULL) {
            printf ("SMSSTATUS: FAILED CONNECT TO SERVER\n");
            return -1;
        }

        buffer = (char *) malloc (1023);
        memset (buffer, 0x0, 1023);
        if (!(strncmp (smsid, "send_", 5) == 0)) {
            if (checksent == 1) {
                urltemplate = (char *) malloc (strlen (urlconfirm));
                memset (urltemplate, 0x0, strlen (urlconfirm));
                strcpy (urltemplate, urlconfirm);
            }
            else {
                urltemplate = (char *) malloc (strlen (urlnoconfirm));
                memset (urltemplate, 0x0, strlen (urlnoconfirm));
                strcpy (urltemplate, urlnoconfirm);
            }
            smsreq = (char *) malloc (strlen (urltemplate) + 1023);
            memset (smsreq, 0x0, strlen (urltemplate) + 1023);
            sprintf (smsreq, urltemplate, gsmnumber,
                     replace (gsmtext, " ", "+"), host);
        }
        else {
            urltemplate = (char *) malloc (strlen (urlcontinuecheck));
            memset (urltemplate, 0x0, strlen (urlcontinuecheck));
            strcpy (urltemplate, urlcontinuecheck);
            smsreq = (char *) malloc (strlen (urltemplate) + 1023);
            memset (smsreq, 0x0, strlen (urltemplate) + 1023);

            sprintf (smsreq, urltemplate, smsid, host);
        }
        if (send (sd, smsreq, strlen (smsreq), 0) != strlen (smsreq)) {
            printf ("SMSSTATUS: FAILED in send()\n");
            return -1;
        }
        out = (char *) malloc (1024);
        memset (out, 0x0, 1024);
        recv (sd, out, 1024, 0);
        SHUTDOWN (sd);          /* close socket... */
        smsstatus = strstr (out, "SMSSTATUS: ");
        if (strstr (out, "HTTP/1.1 200") == NULL) {
            printf ("SMSSTATUS: FAILED SERVER NOT CONFIGURED\n");
            return (-1);
        }
        char *tmp;

        if ((tmp = (char *) strchr (smsstatus, '#')) != NULL) {
            smsid = strdup (tmp + 1);
        }
        free (buffer);
        free (urltemplate);
        free (smsreq);
        free (out);
        if (!checksent)
            return 0;
        if (strstr (smsstatus, "SENT")) {
            printf ("%s\n", smsstatus);
            return 0;
        }
        if (strstr (smsstatus, "FAILED")) {
            printf ("%s\n", smsstatus);
            return -1;
        }
        sleep (5);
    }

    printf ("SMSSTATUS: POSSIBLE FAIL (TIMEOUT)\n");
    return 1;
}