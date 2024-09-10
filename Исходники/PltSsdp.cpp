/*----------------------------------------------------------------------
|   PLT_SsdpSender::SendSsdp
+---------------------------------------------------------------------*/
NPT_Result
PLT_SsdpSender::SendSsdp(NPT_HttpRequest&   request,
                         const char*        usn,
                         const char*        target,
                         NPT_UdpSocket&     socket,
                         bool               notify,
                         const NPT_SocketAddress* addr /* = NULL */)
{
    NPT_CHECK_SEVERE(FormatPacket(request, usn, target, socket, notify));

    // logging
    NPT_String prefix = NPT_String::Format("Sending SSDP %s packet for %s",
        (const char*)request.GetMethod(), 
        usn);
    PLT_LOG_HTTP_MESSAGE(NPT_LOG_LEVEL_FINER, prefix, &request);

    // use a memory stream to write all the data
    NPT_MemoryStream stream;
    NPT_Result res = request.Emit(stream);
    NPT_CHECK(res);

    // copy stream into a data packet and send it
    NPT_LargeSize size;
    stream.GetSize(size);
    if (size != (NPT_Size)size) NPT_CHECK(NPT_ERROR_OUT_OF_RANGE);

    NPT_DataBuffer packet(stream.GetData(), (NPT_Size)size);
    NPT_CHECK_WARNING(socket.Send(packet, addr));
    return NPT_SUCCESS;
}