bool LoginSession::Recieve(XMLPacket *Packet)
{
    if (!Packet) {
        return false;
    }

    if (strncmp(Packet->m_Path, g_STS_Ping, sizeof(Packet->m_Path)) == 0) {
        printf("%s -> Ping!\n", m_Client->m_ClientIP);
    }

    else if (strncmp(Packet->m_Path, g_STS_Connect, sizeof(Packet->m_Path)) == 0) {
        Init(Packet);
    }

    else if (strncmp(Packet->m_Path, g_AUTH_StartTLS, sizeof(Packet->m_Path)) == 0) {
        StartTLS(Packet);
    }

    else if (strncmp(Packet->m_Path, g_AUTH_GetHost, sizeof(Packet->m_Path)) == 0) {
        GetHostname(Packet);
    }

    else if (strncmp(Packet->m_Path, g_AUTH_StartSsoLogin, sizeof(Packet->m_Path)) == 0) {
        StartSsoLogin(Packet);
    }

    else if (strncmp(Packet->m_Path, g_AUTH_ListGameAcc, sizeof(Packet->m_Path)) == 0) {
        ListGameAccounts(Packet);
    }

    else if (strncmp(Packet->m_Path, g_AUTH_Resume, sizeof(Packet->m_Path)) == 0) {
        ResumeAuthentication(Packet);
    }

    else if (strncmp(Packet->m_Path, g_AUTH_RequestGameToken, sizeof(Packet->m_Path)) == 0) {
        RequestGameToken(Packet);
    }

    else if (strncmp(Packet->m_Path, g_AUTH_Logout, sizeof(Packet->m_Path)) == 0) {
        Logout(Packet);
    }

    else {
        printf("Unknown command: %s\n", Packet->m_Path);
    }

    return true;
}