int main()
{
    // Set skt abort function to mine (above)
    skt_set_abort(my_skt_abort);

    SERVER_SOCKET srv = skt_server(&port);
    if (srv == -1)
    {
        cerr << "Error: Could not reserve port #" << port << endl;
        cerr << "EXITING" << endl;
        exit(1);
    }

    while (true)
    {
        listen(srv);
    }

    // Done; close server socket
    skt_close(srv);

    return 0;
}