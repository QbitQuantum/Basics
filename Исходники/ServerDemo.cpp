int _tmain(int argc, _TCHAR* argv[])
{
    oLog::initialise();
    sLog.Init( 5, LOGON_LOG );

    LOG_DETAIL( "服务器启动..." );
    CNet net;
    if ( !net.Startup() )
    {
        return -1;
    }

    CServer server;
    CClient client;


    net.Listen( 6000, &server );

    net.Connect( "127.0.0.1", 6000, &client );

    LOG_DETAIL( "%s", "welcome, the serve is started..." );

    while( 1 )
    {
        net.Process();
        server.Process();
        client.Process();

    }

    net.Clearup();

    LOG_DETAIL( "服务器退出..." );

    sLog.Close();
    oLog::release();
    return 0;
}