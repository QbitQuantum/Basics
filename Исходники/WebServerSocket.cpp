CWebServerSocket::CWebServerSocket(CWebServer* pWebServer, int port)
	: m_pWebServer(pWebServer)
{
	Create(port);
	Listen();
}