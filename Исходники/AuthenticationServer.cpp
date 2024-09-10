// _SendRequestReply
status_t
AuthenticationServer::_SendRequestReply(port_id port, int32 token,
	status_t error, bool cancelled, const char* user, const char* password)
{
	// prepare the reply
	KMessage reply;
	reply.AddInt32("error", error);
	if (error == B_OK) {
		reply.AddBool("cancelled", cancelled);
		if (!cancelled) {
			reply.AddString("user", user);
			reply.AddString("password", password);
		}
	}
	// send the reply
	return reply.SendTo(port, token);
}