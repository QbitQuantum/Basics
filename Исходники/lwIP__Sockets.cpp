BOOL LWIP_SOCKETS_Driver::Uninitialize()
{
    NATIVE_PROFILE_PAL_NETWORK();      

    PostAddressChangedContinuation.Abort();
    PostAvailabilityOnContinuation.Abort();
    PostAvailabilityOffContinuation.Abort();

    for(int i=0; i<g_NetworkConfig.NetworkInterfaceCount; i++)
    {
        Network_Interface_Close(i);
    }

    tcpip_shutdown();

    return TRUE;
}