void
WUploadThread::SetUpload(const ConstSocketRef &socket, muscle::ip_address remoteIP, WFileThread * ft)
{
	String host;
	fAccept = false;
	fRemoteIP = remoteIP;
	fSocket = socket;
	fFileThread = ft;
	// Set string ip too
	muscle::ip_address _ip = GetPeerIPAddress(fSocket, true);
	host = Inet_NtoA(_ip, true);
	fStrRemoteIP = host.Cstr();
}