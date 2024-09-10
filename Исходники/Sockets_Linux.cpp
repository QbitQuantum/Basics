void main() {
    try {
        SocketSystem su;
        std::string host = su.getHostName(), ip = su.getIpFromName(host), name = su.getNameFromIp(ip);
        SocketListener listener(2048);
        Socket sendr;
        if (!sendr.connect(name, 2048)) // can use ip addr, e.g., 127.0.0.1
            return;
        Socket recvr = listener.waitForConnect();
        // sending
        const char* msg1 = "this is a message";
        sendr.send(msg1, strlen(msg1) + 1);
        const char* msg2 = "and a final message";
        sendr.send(msg2, strlen(msg2) + 1);
        sendr.send("quit", strlen("quit") + 1);
        const int BufLen = 256;
        char buffer[BufLen];
        recvr.recv(buffer, strlen(msg1) + 1);
        recvr.recv(buffer, strlen(msg2) + 1);

        recvr.recv(buffer, strlen("quit") + 1);
        recvr.disconnect();
        sendr.disconnect();
        if (!sendr.connect(name, 2048)) {
            throw std::exception("\n  sender reconnect failed");
        }
        recvr = listener.waitForConnect();
        msg1 = "another message after reconnecting";
        std::cout << "\n  sender sending: " << msg1;
        sendr.send(msg1, strlen(msg1) + 1);
        recvr.recv(buffer, strlen(msg1) + 1);
        msg1 = "sending message back";
        recvr.send(msg1, strlen(msg1) + 1);
        recvr.send("quit", strlen("quit") + 1);
        // receiving
        sendr.recv(buffer, strlen(msg1) + 1);
        sendr.recv(buffer, strlen("quit") + 1);
        sendr.disconnect();
        recvr.disconnect();
    } catch (std::exception& e) {
        std::cout << "\n  " << e.what() << "\n\n";
    }
}