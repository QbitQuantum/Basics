static void  _event_socket_prepare( EventHook  hook )
{
    WSANETWORKEVENTS  evts;

    /* look if some of the events we want already happened ? */
    if (!WSAEnumNetworkEvents( hook->fh->fh_socket, NULL, &evts ))
        _event_socket_verify( hook, &evts );
}