bool CMPVlcSourceStream::Load(const TCHAR* fn)
{
    char def_options[512];
    char def_sout[512];


    LogDebug("Load()");
    Clear();

    strncpy(m_fn, fn, sizeof(m_fn));

    sprintf(m_pipename, "\\\\.\\pipe\\vlc2ds_%d_%d", GetCurrentThreadId(), GetTickCount());

    LogDebug("Creating named pipe %s", m_pipename);
    m_hPipe = CreateNamedPipe(
                  m_pipename,             // pipe name
                  PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,       // read/write access
                  PIPE_TYPE_MESSAGE |       // message type pipe
                  PIPE_READMODE_BYTE |   // message-read mode
                  PIPE_WAIT,                // blocking mode
                  PIPE_UNLIMITED_INSTANCES, // max. instances
                  IPTV_BUFFER_SIZE,                  // output buffer size
                  IPTV_BUFFER_SIZE,                  // input buffer size
                  0,                        // client time-out
                  NULL);                    // default security attribute
    if (!m_hPipe)
    {
        LogError("CreateNamedPipe failed");
        return false;
    }
    /* Load the VLC engine */
    m_vlc = libvlc_new (0, NULL);
    if (!m_vlc)
    {
        LogError("libvlc_new failed");
        return false;
    }


    // parse input MRL and options
    GetPrivateProfileString("main", "options", "", def_options, sizeof(def_options), m_inifile);
    GetPrivateProfileString("main", "sout", "file{mux=ts,dst=\"\\%s\"}", def_sout, sizeof(def_sout), m_inifile);

    if (strlen(def_options) > 0)
    {
        strcat_s(m_fn, " ");
        strcat_s(m_fn, def_options);
    }

    LogInfo("Adding media: %s", m_fn);

    int argc;
    m_argv = CommandLineToArgvA(m_fn, &argc);
    m_options = (char**)CoTaskMemAlloc(argc * sizeof(char*));

    int nopt = 0;
    int noremux = -1;
    char *opt_out = 0;
    for (int n = 0; n < argc; n++)
    {
        if (m_argv[n][0] == '-' && m_argv[n][1] == '-')
            m_options[nopt] = m_argv[n] + 2;
        else if (m_argv[n][0] == ':')
            m_options[nopt] = m_argv[n] + 1;
        else
        {
            strncpy(m_input, m_argv[n], sizeof(m_input));
            continue;
        }

        if (strncmp(m_options[nopt], "sout", 4) == 0)			// disable direct ts dump if there are any sout options
            noremux = 0;

        if (strncmp(m_options[nopt], "sout=", 5) == 0)
            opt_out = m_options[nopt] + 5;
        else if (strncmp(m_options[nopt], "exec=", 5) == 0)
            m_exec = m_options[nopt] + 5;
        else if (strncmp(m_options[nopt], "exec-opt=", 9) == 0)
            m_exec_opt = m_options[nopt] + 9;
        else if (strncmp(m_options[nopt], "exec-wait=", 10) == 0)
            m_exec_wait = atoi(m_options[nopt] + 10);
        else if (strncmp(m_options[nopt], "no-remux", 8) == 0 && noremux == -1)
            noremux = 1;
        else
            nopt++;
    }


    char t_output[512];
    if (noremux == 1)
    {
        sprintf_s(m_dump_opt, "ts-dump-file=%s", m_pipename);
        m_options[nopt++] = m_dump_opt;
        strcpy_s(m_output, "#dummy");
    }
    else
    {
        sprintf_s(t_output, def_sout, m_pipename);
        if (opt_out)
            sprintf_s(m_output, "%s:%s", opt_out, t_output);
        else
            sprintf_s(m_output, "#%s", t_output);
    }

    LogDebug("input=%s", m_input);
    LogDebug("output=%s", m_output);
    for (int i = 0; i < nopt; i++)
        LogDebug("options[%d]=%s", i, m_options[i]);

    if (libvlc_vlm_add_broadcast(m_vlc, "vlc_ds_stream", m_input, m_output, nopt, m_options, true, 0) != 0)
    {
        LogError("libvlc_vlm_add_broadcast failed");
        return false;
    }
    return true;
}