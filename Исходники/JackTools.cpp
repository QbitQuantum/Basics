    void JackTools::KillServer()
    {
#ifdef WIN32
        exit(1);
#else
        kill(GetPID(), SIGINT);
#endif
    }