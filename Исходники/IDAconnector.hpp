/////////////////////////////////////////////////////////////////////////////////////////
// cleanup()
//
// cancel all notifications, close the socket and destroy the hook notification window.
//
// arguments: none.
// returns:   none.
//
void IDAconnector::cleanup (void)
{
    // cancel all notifications. if we don't do this ida will crash on exit.
    WSAAsyncSelect(connection, socket_hwnd, 0, 0);

    if (connected)
    {
        closesocket(connection);
        WSACleanup();
        DestroyWindow(socket_hwnd);
    }

    connected = false;
}