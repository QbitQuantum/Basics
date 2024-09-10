/* See description in header file. */
void WorkerThread::DoRealWorks()
{
    while (!m_stop)
    {
        int ret = m_param.WaitForAction();
        if (ret)
        {
            continue;
        }
        // PDEBUG ("Thread %lu is working...\n", TID2ULONG(m_tid));
        PDEBUG ("Thread %p is working...\n", this);

        Socket* sock = m_param.m_sock;
        if (!sock)
        {
            continue;
        }

        while (true)
        {
            THMessagePtr msg = sock->Receive();
            if (!msg)
            {
                m_param.m_busy = false;
                sock->Close();
                if (m_pPool)
                {
                    m_pPool->ReturnThread(this);
                }
                PDEBUG ("Socket closed ...\n");
                break;
            }

            // TODO: Add real work here.
            THMessagePtr rsp = HandleRequest(msg);

            // Send it back to client;
            int n = sock->Send(rsp);
        }
    }
}