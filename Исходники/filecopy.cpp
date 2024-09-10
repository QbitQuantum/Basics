void* ServerThreadHandler::handle(Params* params)
{
    void* ret = (void*) 2;
    cout << "Server connecting to port " << params->port << endl;
    string fileName = params->fileName + ".bak";
    cout << "Writing to file " << fileName << endl;

    Socket sock;
    SocketAddr saddr(0, params->port);
    if (!sock.open(saddr, Socket::modeReadWrite))
    {
        cout << "Error opening server socket: " << errno << endl;
        return ret;
    }

    Stream* clientSock = sock.listen();
    if (clientSock)
    {
        ifstream ifile(fileName.c_str());
        if (ifile.is_open())
        {
            cout << "Output file already exists.  Not overwriting." << endl;
            return ret;
        }
        ofstream ofile(fileName.c_str());

        if (params->binary)
        {
            char buf[256];
            int sz = clientSock->read(buf, sizeof(buf));
            while (clientSock->queryStatus() == SC_OK)
            {
                ofile.write(buf, sz);
                sz = clientSock->read(buf, sizeof(buf));
            }
        }
        else
        {
            string strbuf;
            clientSock->read(strbuf, EOF);
            ofile << strbuf;
        }

        clientSock->close();
        delete clientSock;
    }

    sock.close();
    return 0;
}