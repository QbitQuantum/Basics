void LinkOptions::OnOk()
{
    static const int length = 256;
    int timeout;
    CString timeoutStr;
    CString host;
    CString title;
    CString addressMessage;

    UpdateData(TRUE);

    // Close any previous link
    CloseLink();

    m_serverip.GetWindowText(host);
    m_timeout.GetWindowText(timeoutStr);
    sscanf(timeoutStr, "%d", &timeout);
    SetLinkTimeout(timeout);

    LinkMode newMode = (LinkMode)m_type;

    if (newMode == LINK_DISCONNECTED) {
        linkTimeout = timeout;
        linkMode = LINK_DISCONNECTED;
        theApp.linkHostAddr = host;
        CDialog::OnOK();
        return;
    }

    bool needsServerHost = newMode == LINK_GAMECUBE_DOLPHIN || (newMode == LINK_CABLE_SOCKET && !m_server) || (newMode == LINK_RFU_SOCKET && !m_server);

    if (needsServerHost) {
        bool valid = SetLinkServerHost(host);
        if (!valid) {
            AfxMessageBox("You must enter a valid host name", MB_OK | MB_ICONSTOP);
            return;
        }
    }

    EnableSpeedHacks(linkHacks);
    EnableLinkServer(m_server, linkNumPlayers + 1);

    if (m_server) {
        char localhost[length];
        GetLinkServerHost(localhost, length);

        title = "Waiting for clients...";
        addressMessage.Format("Server IP address is: %s\n", localhost);
    } else {
        title = "Waiting for connection...";
        addressMessage.Format("Connecting to %s\n", host);
    }

    // Init link
    ConnectionState state = InitLink(newMode);

    // Display a progress dialog while the connection is establishing
    if (state == LINK_NEEDS_UPDATE) {
        ServerWait* dlg = new ServerWait();
        dlg->Create(ServerWait::IDD, this);
        dlg->m_plconn[1] = title;
        dlg->m_serveraddress = addressMessage;
        dlg->ShowWindow(SW_SHOW);

        while (state == LINK_NEEDS_UPDATE) {
            // Ask the core for updates
            char message[length];
            state = ConnectLinkUpdate(message, length);

            // Update the wait message
            if (strlen(message)) {
                dlg->m_plconn[1] = message;
            }

            // Step the progress bar and update dialog data
            dlg->m_prgctrl.StepIt();
            dlg->UpdateData(false);

            // Process Windows messages
            MSG msg;
            while (PeekMessage(&msg, 0, 0, 0, PM_NOREMOVE)) {
                AfxGetApp()->PumpMessage();
            }

            // Check whether the user has aborted
            if (dlg->m_userAborted) {
                state = LINK_ABORT;
            }
        }

        delete dlg;
    }

    // The user canceled the connection attempt
    if (state == LINK_ABORT) {
        CloseLink();
        return;
    }

    // Something failed during init
    if (state == LINK_ERROR) {
        AfxMessageBox("Error occurred.\nPlease try again.", MB_OK | MB_ICONSTOP);
        return;
    }

    linkTimeout = timeout;
    linkMode = GetLinkMode();
    theApp.linkHostAddr = host;

    CDialog::OnOK();
    return;
}