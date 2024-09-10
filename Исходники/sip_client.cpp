    void on_open(connection_ptr con) {
        // now it is safe to use the connection
        std::cout << "connection ready" << std::endl;

        received = false;

        std::string SIP_msg="OPTIONS sip:[email protected] SIP/2.0\r\nVia: SIP/2.0/WS df7jal23ls0d.invalid;rport;branch=z9hG4bKhjhs8ass877\r\nMax-Forwards: 70\r\nTo: <sip:[email protected]>\r\nFrom: Alice <sip:[email protected]>;tag=1928301774\r\nCall-ID: a84b4c76e66710\r\nCSeq: 63104 OPTIONS\r\nContact: <sip:[email protected]>\r\nAccept: application/sdp\r\nContent-Length: 0\r\n\r\n";
        con->send(SIP_msg.c_str());
    }