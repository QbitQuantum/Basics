/*----------------------------------------------------------------------
|       UdpServerLoop
+---------------------------------------------------------------------*/
static void
UdpServerLoop(int port)
{
    NPT_UdpSocket listener;

    // info
    if (Options.verbose) {
        NPT_Debug("listening on port %d\n", port);
    }

    NPT_Result result = listener.Bind(NPT_SocketAddress(NPT_IpAddress::Any, port));
    if (NPT_FAILED(result)) {
        NPT_Debug("ERROR: Bind() failed (%d)\n", result);
    }

    // packet loop
    NPT_DataBuffer packet(32768);
    NPT_SocketAddress address;

    do {
        result = listener.Receive(packet, &address);
        if (NPT_SUCCEEDED(result)) {
            if (Options.verbose) {
                NPT_String ip = address.GetIpAddress().ToString();
                NPT_Debug("Received %d bytes from %s:%d\n", packet.GetDataSize(), ip.GetChars(), address.GetPort());
            }

            listener.Send(packet, &address);
        }
    } while (NPT_SUCCEEDED(result));
}