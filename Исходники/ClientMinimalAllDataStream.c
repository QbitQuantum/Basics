/*
 * Formats an Float (32bits) from host to TCP/IP network byte order (which is big-endian)
 * and sends it thought the Socket
 */
void SendFloatClientSocket(SOCKET theSocket, float value)
{
	int htonvalue[] = { htonf(value) };
	send(theSocket, (char*)htonvalue, sizeof(int), 0);
}