// Sets the outgoing address
void BufferedSocket::SetRemoteAddress(const wxString &Address, const wxInt16 &Port)
{
    struct hostent *he;

    if((he = gethostbyname((const char *)Address.char_str())) == NULL)
    {
        CheckError();
        return;
    }

    m_RemoteAddress.sin_family = PF_INET;
    m_RemoteAddress.sin_port = htons(Port);
    m_RemoteAddress.sin_addr = *((struct in_addr *)he->h_addr);
    memset(m_RemoteAddress.sin_zero, '\0', sizeof m_RemoteAddress.sin_zero);
}