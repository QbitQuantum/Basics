// create a new connection reading a file from server
void TFTPServer::ConnectRead(char* buff) {
    extern LaosFileSystem sd;
    remote_ip = client.get_address();
    remote_port = client.get_port();
    Ack(0);
    blockcnt = 0;
    dupcnt = 0;

    sprintf(filename, "%s", &buff[2]);
    
    if (modeOctet(buff))
        fp = sd.openfile(filename, "rb");
    else
        fp = sd.openfile(filename, "r");
    if (fp == NULL) {
        state  = listen;
        Err("Could not read file");
    } else {
        // file ready for reading
        blockcnt = 0;
        state = reading;
        #ifdef TFTP_DEBUG
            char debugmsg[256];
            sprintf(debugmsg, "Listen: Requested file %s from TFTP connection %d.%d.%d.%d port %d",
                filename, clientIp[0], clientIp[1], clientIp[2], clientIp[3], clientPort);
            TFTP_DEBUG(debugmsg);
        #endif
        getBlock();
        sendBlock();
    }
}