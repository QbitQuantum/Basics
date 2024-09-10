    void ShowSocks(bool bShowHosts) {
        CSockManager& m = CZNC::Get().GetManager();
        if (!m.size()) {
            PutStatus("You have no open sockets.");
            return;
        }

        std::priority_queue<CSocketSorter> socks;

        for (unsigned int a = 0; a < m.size(); a++) {
            socks.push(m[a]);
        }

        CTable Table;
        Table.AddColumn("Name");
        Table.AddColumn("Created");
        Table.AddColumn("State");
#ifdef HAVE_LIBSSL
        Table.AddColumn("SSL");
#endif
        Table.AddColumn("Local");
        Table.AddColumn("Remote");

        while (!socks.empty()) {
            Csock* pSocket = socks.top().GetSock();
            socks.pop();

            Table.AddRow();

            switch (pSocket->GetType()) {
            case Csock::LISTENER:
                Table.SetCell("State", "Listen");
                break;
            case Csock::INBOUND:
                Table.SetCell("State", "Inbound");
                break;
            case Csock::OUTBOUND:
                if (pSocket->IsConnected())
                    Table.SetCell("State", "Outbound");
                else
                    Table.SetCell("State", "Connecting");
                break;
            default:
                Table.SetCell("State", "UNKNOWN");
                break;
            }

            unsigned long long iStartTime = pSocket->GetStartTime();
            time_t iTime = iStartTime / 1000;
            Table.SetCell("Created", FormatTime("%Y-%m-%d %H:%M:%S", iTime));

#ifdef HAVE_LIBSSL
            if (pSocket->GetSSL()) {
                Table.SetCell("SSL", "Yes");
            } else {
                Table.SetCell("SSL", "No");
            }
#endif


            Table.SetCell("Name", pSocket->GetSockName());
            CString sVHost;
            if (bShowHosts) {
                sVHost = pSocket->GetBindHost();
            }
            if (sVHost.empty()) {
                sVHost = pSocket->GetLocalIP();
            }
            Table.SetCell("Local", sVHost + " " + CString(pSocket->GetLocalPort()));

            CString sHost;
            if (!bShowHosts) {
                sHost = pSocket->GetRemoteIP();
            }
            // While connecting, there might be no ip available
            if (sHost.empty()) {
                sHost = pSocket->GetHostName();
            }

            u_short uPort;
            // While connecting, GetRemotePort() would return 0
            if (pSocket->GetType() == Csock::OUTBOUND) {
                uPort = pSocket->GetPort();
            } else {
                uPort = pSocket->GetRemotePort();
            }
            if (uPort != 0) {
                Table.SetCell("Remote", sHost + " " + CString(uPort));
            } else {
                Table.SetCell("Remote", sHost);
            }
        }

        PutModule(Table);
        return;
    }