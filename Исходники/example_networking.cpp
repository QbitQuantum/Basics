void ServerUDP()
{
    UdpServer server;
    Packet data;
    IP4Address source;
    //server.SetNetworkInterface(0);  // If you wanted to specifiy a network interface to receive on.
    data.SetByteOrder(CX_PACKET_BIG_ENDIAN);
    if(!server.InitializeMulticastSocket(PORT, MULTICAST_GROUP)) 
    {
        cout << "Unable to initialize on port " << PORT << endl;
        return;
    }
    cout << "Initialized UDP Server Socket on port " << PORT << endl;
    char key = 0;
    while(key != 27) 
    {

        //  Do non-blocking receive for data (wait 100 ms).
        if(server.Recv(data, 500, 100, &source) > 0) //  Receive up to 500 bytes to packet.
        { 
            cout << source.mString << " Sent (" << data.Size() << " bytes): ";
            char val;
            while(data.Read(val))
                cout << val;
            cout << endl;
        }
        key = GetChar();     //  Get key.
    }
}