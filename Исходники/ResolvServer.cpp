void ResolvServer::Run()
{
//  StdoutLog log;
    SocketHandler h;
    ListenSocket<ResolvSocket> l(h);

    if (l.Bind("127.0.0.1", m_port))
    {
        return;
    }
    h.Add(&l);

    m_ready = true;
    while (!m_quit && IsRunning() )
    {
        h.Select(0, 500000);
    }
    SetRunning(false);
}