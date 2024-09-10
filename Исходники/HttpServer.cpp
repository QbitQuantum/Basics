bool CHttpServer::run()
{
    LOG(INFO) + "Start HTTP server";

    if (!init())
        return false;

    m_active = true;

    RHODESAPP().notifyLocalServerStarted();

    for(;;) 
    {
        RAWTRACE("Waiting for connections...");
#ifndef RHO_NO_RUBY_API
        if (rho_ruby_is_started())
            rho_ruby_start_threadidle();
#endif
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(m_listener, &readfds);

        timeval tv = {0,0};
        unsigned long nTimeout = RHODESAPP().getTimer().getNextTimeout();
        tv.tv_sec = nTimeout/1000;
        tv.tv_usec = (nTimeout - tv.tv_sec*1000)*1000;
        int ret = select(m_listener+1, &readfds, NULL, NULL, (tv.tv_sec == 0 && tv.tv_usec == 0 ? 0 : &tv) );
#ifndef RHO_NO_RUBY_API
        if (rho_ruby_is_started())
            rho_ruby_stop_threadidle();
#endif
        bool bProcessed = false;
        if (ret > 0) 
        {
            if (FD_ISSET(m_listener, &readfds))
            {
                //RAWTRACE("Before accept...");
                SOCKET conn = accept(m_listener, NULL, NULL);
                //RAWTRACE("After accept...");
                if (!m_active) {
                    RAWTRACE("Stop HTTP server");
                    return true;
                }
                if (conn == INVALID_SOCKET) {
        #if !defined(WINDOWS_PLATFORM)
                    if (RHO_NET_ERROR_CODE == EINTR)
                        continue;
        #endif
                    RAWLOG_ERROR1("Can not accept connection: %d", RHO_NET_ERROR_CODE);
                    return false;
                }

                RAWTRACE("Connection accepted, process it...");
                VALUE val;
#ifndef RHO_NO_RUBY_API                
                if (rho_ruby_is_started())
                {
                    if ( !RHOCONF().getBool("enable_gc_while_request") )                
                        val = rho_ruby_disable_gc();
                }
#endif
                m_sock = conn;
                bProcessed = process(m_sock);
#ifndef RHO_NO_RUBY_API
                if (rho_ruby_is_started())
                {
                    if ( !RHOCONF().getBool("enable_gc_while_request") )
                        rho_ruby_enable_gc(val);
                }
#endif
                RAWTRACE("Close connected socket");
                closesocket(m_sock);
                m_sock = INVALID_SOCKET;
            }
        }
        else if ( ret == 0 ) //timeout
        {
            bProcessed = RHODESAPP().getTimer().checkTimers();
        }
        else
        {
            RAWLOG_ERROR1("select error: %d", ret);
            return false;
        }
#ifndef RHO_NO_RUBY_API
        if (rho_ruby_is_started())
        {
            if ( bProcessed )
            {
                LOG(INFO) + "GC Start.";
                rb_gc();
                LOG(INFO) + "GC End.";
            }
        }
#endif
    }
}