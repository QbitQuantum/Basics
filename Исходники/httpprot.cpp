void CSecureHttpProtocol::init(IPropertyTree * cfg, const char * process, const char * protocol)
{
    Owned<IPropertyTree> proc_cfg = getProcessConfig(cfg, process);
    if (proc_cfg)
    {
        CEspProtocol::setViewConfig(proc_cfg->getPropBool("@httpConfigAccess"));
        const char* mctstr = proc_cfg->queryProp("@maxConcurrentThreads");
        if(mctstr && *mctstr)
        {
            m_maxConcurrentThreads = atoi(mctstr);
        }

        if(m_maxConcurrentThreads > 0)
        {
            // Could use a mutex, but since all the protocols are instantiated sequentially, not really necessary
            if(!http_pool_factory)
                http_pool_factory = new CHttpThreadPoolFactory();
            if(!http_thread_pool)
                http_thread_pool = createThreadPool("Http Thread", http_pool_factory, NULL, m_maxConcurrentThreads, INFINITE);
        }
    }

    initPersistentHandler(proc_cfg);

    Owned<IPropertyTree> proto_cfg = getProtocolConfig(cfg, protocol, process);
    if(proto_cfg)
    {
        const char* lenstr = proto_cfg->queryProp("@maxRequestEntityLength");
        if(lenstr && *lenstr)
        {
            setMaxRequestEntityLength(atoi(lenstr));
        }
    }
}