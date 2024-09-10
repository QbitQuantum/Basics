void FetchClientPrivate::packet_ready()
{
    if (m_socket->readBuffer.readPos() == m_socket->readBuffer.writePos())
        return;
    for (;;){
        if (m_state == Data){
            unsigned size = m_socket->readBuffer.writePos() - m_socket->readBuffer.readPos();
            if (size){
                if (!m_client->write_data(m_socket->readBuffer.data(m_socket->readBuffer.readPos()), size)){
                    m_socket->error_state("Write error");
                    return;
                }
            }
            m_received += size;
            if (m_received >= m_size){
                m_state = Done;
                m_socket->error_state("");
                return;
            }
            m_socket->readBuffer.init(0);
            m_socket->readBuffer.packetStart();
            return;
        }
        log_packet(m_socket->readBuffer, false, HTTPPacket);
        string line;
        string opt;
        if (!read_line(line)){
            m_socket->readBuffer.init(0);
            m_socket->readBuffer.packetStart();
            return;
        }
        switch (m_state){
        case None:
#ifdef USE_OPENSSL
        case SSLConnect:
#endif
            if (getToken(line, ' ').substr(0, 5) != "HTTP/"){
                m_socket->error_state("Bad HTTP answer");
                return;
            }
            m_code = atol(getToken(line, ' ').c_str());
            m_state = Header;
            break;
        case Header:
            if (line.empty()){
                m_state = Data;
                break;
            }
            m_hIn += line;
            m_hIn += '\x00';
            opt = getToken(line, ':');
            if (opt == "Content-Length"){
                const char *p;
                for (p = line.c_str(); *p; p++)
                    if (*p != ' ')
                        break;
                m_size = atol(p);
            }
            if ((opt == "Location") && m_bRedirect){
                const char *p;
                for (p = line.c_str(); *p; p++)
                    if (*p != ' ')
                        break;
                string proto;
                string host;
                string user;
                string pass;
                string uri;
                string extra;
                unsigned short port;
                if (!FetchClient::crackUrl(p, proto, host, port, user, pass, uri, extra)){
                    FetchClient::crackUrl(m_uri.c_str(), proto, host, port, user, pass, uri, extra);
                    extra = "";
                    if (*p == '/'){
                        uri = p;
                    }else{
                        int n = uri.find_last_of('/');
                        uri = uri.substr(0, n + 1);
                        uri += p;
                    }
                }
                m_uri = proto;
                m_uri += "://";
                m_uri += host;
                m_uri += ":";
                m_uri += number(port);
                m_uri += uri;
                if (!extra.empty()){
                    m_uri += "?";
                    m_uri += extra;
                }
                m_state = Redirect;
                m_socket->close();
                m_socket->error_state("");
                return;
            }
            break;
        default:
            break;
        }
    }
}