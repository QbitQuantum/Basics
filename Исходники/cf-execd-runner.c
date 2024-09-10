static void MailResult(const ExecConfig *config, const char *file)
{
#if defined __linux__ || defined __NetBSD__ || defined __FreeBSD__ || defined __OpenBSD__
    time_t now = time(NULL);
#endif
    Log(LOG_LEVEL_VERBOSE, "Mail result...");

    {
        struct stat statbuf;
        if (stat(file, &statbuf) == -1)
        {
            return;
        }

        if (statbuf.st_size == 0)
        {
            unlink(file);
            Log(LOG_LEVEL_DEBUG, "Nothing to report in file '%s'", file);
            return;
        }
    }

    {
        char prev_file[CF_BUFSIZE];
        snprintf(prev_file, CF_BUFSIZE - 1, "%s/outputs/previous", CFWORKDIR);
        MapName(prev_file);

        if (CompareResult(file, prev_file) == 0)
        {
            Log(LOG_LEVEL_VERBOSE, "Previous output is the same as current so do not mail it");
            return;
        }
    }

    if ((strlen(config->mail_server) == 0) || (strlen(config->mail_to_address) == 0))
    {
        /* Syslog should have done this */
        Log(LOG_LEVEL_VERBOSE, "Empty mail server or address - skipping");
        return;
    }

    if (config->mail_max_lines == 0)
    {
        Log(LOG_LEVEL_DEBUG, "Not mailing: EmailMaxLines was zero");
        return;
    }

    Log(LOG_LEVEL_DEBUG, "Mailing results of '%s' to '%s'", file, config->mail_to_address);

/* Check first for anomalies - for subject header */

    FILE *fp = fopen(file, "r");
    if (!fp)
    {
        Log(LOG_LEVEL_INFO, "Couldn't open file '%s'. (fopen: %s)", file, GetErrorStr());
        return;
    }

    bool anomaly = false;
    char vbuff[CF_BUFSIZE];

    while (!feof(fp))
    {
        vbuff[0] = '\0';
        if (fgets(vbuff, sizeof(vbuff), fp) == NULL)
        {
            break;
        }

        if (strstr(vbuff, "entropy"))
        {
            anomaly = true;
            break;
        }
    }

    fclose(fp);

    if ((fp = fopen(file, "r")) == NULL)
    {
        Log(LOG_LEVEL_INFO, "Couldn't open file '%s'. (fopen: %s)", file, GetErrorStr());
        return;
    }

    struct hostent *hp = gethostbyname(config->mail_server);
    if (!hp)
    {
        Log(LOG_LEVEL_ERR, "While mailing agent output, unknown host '%s'. Make sure that fully qualified names can be looked up at your site.",
            config->mail_server);
        fclose(fp);
        return;
    }

    struct servent *server = getservbyname("smtp", "tcp");
    if (!server)
    {
        Log(LOG_LEVEL_INFO, "Unable to lookup smtp service. (getservbyname: %s)", GetErrorStr());
        fclose(fp);
        return;
    }

    struct sockaddr_in raddr;
    memset(&raddr, 0, sizeof(raddr));

    raddr.sin_port = (unsigned int) server->s_port;
    raddr.sin_addr.s_addr = ((struct in_addr *) (hp->h_addr))->s_addr;
    raddr.sin_family = AF_INET;

    Log(LOG_LEVEL_DEBUG, "Connecting...");

    int sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd == -1)
    {
        Log(LOG_LEVEL_INFO, "Couldn't open a socket. (socket: %s)", GetErrorStr());
        fclose(fp);
        return;
    }

    if (connect(sd, (void *) &raddr, sizeof(raddr)) == -1)
    {
        Log(LOG_LEVEL_INFO, "Couldn't connect to host '%s'. (connect: %s)",
            config->mail_server, GetErrorStr());
        fclose(fp);
        cf_closesocket(sd);
        return;
    }

/* read greeting */

    if (!Dialogue(sd, NULL))
    {
        goto mail_err;
    }

    sprintf(vbuff, "HELO %s\r\n", config->fq_name);
    Log(LOG_LEVEL_DEBUG, "%s", vbuff);

    if (!Dialogue(sd, vbuff))
    {
        goto mail_err;
    }

    if (strlen(config->mail_from_address) == 0)
    {
        sprintf(vbuff, "MAIL FROM: <cfengine@%s>\r\n", config->fq_name);
        Log(LOG_LEVEL_DEBUG, "%s", vbuff);
    }
    else
    {
        sprintf(vbuff, "MAIL FROM: <%s>\r\n", config->mail_from_address);
        Log(LOG_LEVEL_DEBUG, "%s", vbuff);
    }

    if (!Dialogue(sd, vbuff))
    {
        goto mail_err;
    }

    sprintf(vbuff, "RCPT TO: <%s>\r\n", config->mail_to_address);
    Log(LOG_LEVEL_DEBUG, "%s", vbuff);

    if (!Dialogue(sd, vbuff))
    {
        goto mail_err;
    }

    if (!Dialogue(sd, "DATA\r\n"))
    {
        goto mail_err;
    }

    char mailsubject_anomaly_prefix[8];
    if (anomaly)
    {
        strcpy(mailsubject_anomaly_prefix, "**!! ");
    }
    else
    {
        mailsubject_anomaly_prefix[0] = '\0';
    }

    if (SafeStringLength(config->mail_subject) == 0)
    {
        snprintf(vbuff, sizeof(vbuff), "Subject: %s[%s/%s]\r\n", mailsubject_anomaly_prefix, config->fq_name, config->ip_address);
        Log(LOG_LEVEL_DEBUG, "%s", vbuff);
    }
    else
    {
        snprintf(vbuff, sizeof(vbuff), "Subject: %s%s\r\n", mailsubject_anomaly_prefix, config->mail_subject);
        Log(LOG_LEVEL_DEBUG, "%s", vbuff);
    }

    send(sd, vbuff, strlen(vbuff), 0);

    /* send X-CFEngine SMTP header if mailsubject set */
    if (SafeStringLength(config->mail_subject) > 0)
    {
        unsigned char digest[EVP_MAX_MD_SIZE + 1];
        char buffer[EVP_MAX_MD_SIZE * 4];

        char *existing_policy_server = ReadPolicyServerFile(GetWorkDir());

        HashPubKey(PUBKEY, digest, CF_DEFAULT_DIGEST);

        snprintf(vbuff, sizeof(vbuff), "X-CFEngine: vfqhost=\"%s\";ip-addresses=\"%s\";policyhub=\"%s\";pkhash=\"%s\"\r\n",
                 VFQNAME, config->ip_addresses, existing_policy_server,
                 HashPrintSafe(CF_DEFAULT_DIGEST, true, digest, buffer));

        send(sd, vbuff, strlen(vbuff), 0);
        free(existing_policy_server);
    }

#if defined __linux__ || defined __NetBSD__ || defined __FreeBSD__ || defined __OpenBSD__
    strftime(vbuff, CF_BUFSIZE, "Date: %a, %d %b %Y %H:%M:%S %z\r\n", localtime(&now));
    send(sd, vbuff, strlen(vbuff), 0);
#endif

    if (strlen(config->mail_from_address) == 0)
    {
        sprintf(vbuff, "From: cfengine@%s\r\n", config->fq_name);
        Log(LOG_LEVEL_DEBUG, "%s", vbuff);
    }
    else
    {
        sprintf(vbuff, "From: %s\r\n", config->mail_from_address);
        Log(LOG_LEVEL_DEBUG, "%s", vbuff);
    }

    send(sd, vbuff, strlen(vbuff), 0);

    sprintf(vbuff, "To: %s\r\n\r\n", config->mail_to_address);
    Log(LOG_LEVEL_DEBUG, "%s", vbuff);
    send(sd, vbuff, strlen(vbuff), 0);

    int count = 0;
    while (!feof(fp))
    {
        vbuff[0] = '\0';
        if (fgets(vbuff, sizeof(vbuff), fp) == NULL)
        {
            break;
        }

        Log(LOG_LEVEL_DEBUG, "%s", vbuff);

        if (strlen(vbuff) > 0)
        {
            vbuff[strlen(vbuff) - 1] = '\r';
            strcat(vbuff, "\n");
            count++;
            send(sd, vbuff, strlen(vbuff), 0);
        }

        if ((config->mail_max_lines != INF_LINES) && (count > config->mail_max_lines))
        {
            sprintf(vbuff, "\r\n[Mail truncated by cfengine. File is at %s on %s]\r\n", file, config->fq_name);
            send(sd, vbuff, strlen(vbuff), 0);
            break;
        }
    }

    if (!Dialogue(sd, ".\r\n"))
    {
        Log(LOG_LEVEL_DEBUG, "mail_err\n");
        goto mail_err;
    }

    Dialogue(sd, "QUIT\r\n");
    Log(LOG_LEVEL_DEBUG, "Done sending mail");
    fclose(fp);
    cf_closesocket(sd);
    return;

  mail_err:

    fclose(fp);
    cf_closesocket(sd);
    Log(LOG_LEVEL_INFO, "Cannot mail to %s.", config->mail_to_address);
}