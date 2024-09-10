static void close_client_connection(NVQRConnection c)
{
#if defined (_WIN32)
    DisconnectNamedPipe(c.client_handle);
#else
#endif
}