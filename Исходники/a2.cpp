int clientSlidingWindow(UdpSocket &sock, const int max, int message[], const int windowSize) {
    
    int retransmits = 0;
    int ack;
    int ackSeq = 0;         // expected ack to receive
    
    // transfer all max messages
    for (int msgNum = 0; msgNum < max && ackSeq < max;) {
        
        int numOfUnAck = msgNum - ackSeq;
        
        // sliding window has space
        if (numOfUnack < windowSize) {

            // set-up message and send
            message[0] = msgNum;
            sock.sendTo((char *)message, MSGSIZE);
            
            // check for acknowledgement
            if (sock.pollRecvFrom() != 0) {
                sock.recvFrom((char *)&ack, sizeof(ack));
                if (ack == ackSeq)
                    ackSeq++;
            }
            msgNum++;
            
        // sliding window is full  
        } else {
            Timer t;
            t.start();
            
            bool ackReceived = false;
            
            // wait for acknowledgement within TIMEOUT
            while (t.lap() < TIMEOUT) {
                
                // check for acknowledgement
                if (sock.pollRecvFrom() != 0) {
                    ackReceived = true;
                    sock.recvFrom((char *)&ack, sizeof(ack));
                    
                    // every message up to ack has been received
                    if (ack >= ackSeq)
                        ackSeq = ack + 1;
                    else {
                        // message # ack never received, resend 
                        message[0] = ack;
                        sock.sendTo((char *)message, MSGSIZE);
                        retransmits++;
                    }                                        
                    break;
                }
            }
            
            // resend minimum unacknowledged sequence number on timeout
            if (!ackReceived) {
                message[0] = ackSeq;
                sock.sendTo((char *)message, MSGSIZE);
                retransmits++;
            }
        }
    }
    return retransmits;
}