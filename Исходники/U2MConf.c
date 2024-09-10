/* functions for handling the configuration file */
BOOL parseConfFile(user_input_data *user_dat)
{
    cfg_opt_t email_opts[] = {
        CFG_STR("From", NULL, CFGF_NONE),
        CFG_STR("To", NULL, CFGF_NONE),
        CFG_STR("Cc", NULL, CFGF_NONE),
        CFG_STR("Subject", NULL, CFGF_NONE),
        CFG_STR("Body", NULL, CFGF_NONE),
        CFG_STR("Password", NULL, CFGF_NONE),
        CFG_STR("SMTP_server", NULL, CFGF_NONE),
        CFG_INT("Port_number", 0, CFGF_NONE),
        CFG_END()
    };

    cfg_t *U2MConf;
    U2MConf = cfg_init(email_opts, CFGF_NONE);
    int cfg_err = cfg_parse(U2MConf, cfg_filename);

    if (cfg_err) {
#if 0
        if (cfg_err == CFG_PARSE_ERROR)
            fprintf(stderr, "Error at parsing %s\n", cfg_filename);
        else
            fprintf(stderr, "Couldn't find configuration file with filename %s\n", cfg_filename);
#endif
        cfg_free(U2MConf);
        return FALSE;
    }

    char *temp[7] = {
        cfg_getstr(U2MConf, "From"),
        cfg_getstr(U2MConf, "To"),
        cfg_getstr(U2MConf, "Cc"),
        cfg_getstr(U2MConf, "Subject"),
        cfg_getstr(U2MConf, "Body"),
        cfg_getstr(U2MConf, "Password"),
        cfg_getstr(U2MConf, "SMTP_server")
    };

    if (temp[0]) {
        size_t len;
        if (SUCCEEDED(StringCbLengthA(temp[0], MAX_BUFFER, &len))) {
            if (user_dat->FROM) HeapFree(GetProcessHeap(), 0, user_dat->FROM);
            user_dat->FROM = HeapAlloc(GetProcessHeap(), HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY, sizeof(temp[0])*(len + 1));
            if (user_dat->FROM) StringCchCopyA(user_dat->FROM, MAX_BUFFER, temp[0]);
            else __MsgBoxGetLastError(NULL, TEXT("HeapAlloc()"), __LINE__);
        }
    }
    if (temp[1]) {
        size_t len;
        if (SUCCEEDED(StringCbLengthA(temp[1], MAX_BUFFER, &len))) {
            if (user_dat->TO) HeapFree(GetProcessHeap(), 0, user_dat->TO);
            user_dat->TO = HeapAlloc(GetProcessHeap(), HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY, sizeof(temp[1])*(len + 1));
            if (user_dat->TO) StringCchCopyA(user_dat->TO, MAX_BUFFER, temp[1]);
            else __MsgBoxGetLastError(NULL, TEXT("HeapAlloc()"), __LINE__);
        }
    }
    if (temp[2]) {
        size_t len;
        if (SUCCEEDED(StringCbLengthA(temp[2], MAX_BUFFER, &len))) {
            if (user_dat->CC) HeapFree(GetProcessHeap(), 0, user_dat->CC);
            user_dat->CC = HeapAlloc(GetProcessHeap(), HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY, sizeof(temp[2])*(len + 1));
            if (user_dat->CC) StringCchCopyA(user_dat->CC, MAX_BUFFER, temp[2]);
            else __MsgBoxGetLastError(NULL, TEXT("HeapAlloc()"), __LINE__);
        }
    }
    if (temp[3]) {
        size_t len;
        if (SUCCEEDED(StringCbLengthA(temp[3], MAX_BUFFER, &len))) {
            if (user_dat->SUBJECT) HeapFree(GetProcessHeap(), 0, user_dat->SUBJECT);
            user_dat->SUBJECT = HeapAlloc(GetProcessHeap(), HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY, sizeof(temp[3])*(len + 1));
            if (user_dat->SUBJECT) StringCchCopyA(user_dat->SUBJECT, MAX_BUFFER, temp[3]);
            else __MsgBoxGetLastError(NULL, TEXT("HeapAlloc()"), __LINE__);
        }
    }
    if (temp[4]) {
        size_t len;
        if (SUCCEEDED(StringCbLengthA(temp[4], MAX_BUFFER, &len))) {
            if (user_dat->BODY) HeapFree(GetProcessHeap(), 0, user_dat->BODY);
            user_dat->BODY = HeapAlloc(GetProcessHeap(), HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY, sizeof(temp[4])*(len + 1));
            if (user_dat->BODY) StringCchCopyA(user_dat->BODY, MAX_BUFFER, temp[4]);
            else __MsgBoxGetLastError(NULL, TEXT("HeapAlloc()"), __LINE__);
        }
    }
    if (temp[5]) {
        size_t len;
        if (SUCCEEDED(StringCbLengthA(temp[5], MAX_BUFFER, &len))) {
            if (user_dat->pass) HeapFree(GetProcessHeap(), 0, user_dat->pass);
            user_dat->pass = HeapAlloc(GetProcessHeap(), HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY, sizeof(temp[5])*(len + 1));
            if (user_dat->pass) StringCchCopyA(user_dat->pass, MAX_BUFFER, temp[5]);
            else __MsgBoxGetLastError(NULL, TEXT("HeapAlloc()"), __LINE__);
        }
    }
    if (temp[6]) {
        size_t len;
        if (SUCCEEDED(StringCbLengthA(temp[6], MAX_BUFFER, &len))) {
            if (user_dat->SMTP_SERVER) HeapFree(GetProcessHeap(), 0, user_dat->SMTP_SERVER);
            user_dat->SMTP_SERVER = HeapAlloc(GetProcessHeap(), HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY, sizeof(temp[6])*(len + 1));
            if (user_dat->SMTP_SERVER) StringCchCopyA(user_dat->SMTP_SERVER, MAX_BUFFER, temp[6]);
            else __MsgBoxGetLastError(NULL, TEXT("HeapAlloc()"), __LINE__);
        }
    }

    int signed_port = cfg_getint(U2MConf, "Port_number");
    user_dat->PORT = (UINT)signed_port;

    cfg_free(U2MConf);

#ifdef DEBUG
    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%u\n", user_dat->FROM, user_dat->TO, user_dat->CC,
           user_dat->SUBJECT, user_dat->BODY, user_dat->pass, user_dat->SMTP_SERVER, user_dat->PORT);
#endif
    return TRUE;
}