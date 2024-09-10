void StatusSocket::InitSSLServer()
{
	InitializeContext("session_id", "server.pem", "keypwd", SSLv23_method());
}