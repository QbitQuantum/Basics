//this function received the command from ios, and push them to the queue.
int SocketServerManager::run(){
    TCPStream* stream = NULL;
    TCPAcceptor* acceptor = NULL;
    CommandQueue cmdQueue;
    Command rcvCmd;
    acceptor = new TCPAcceptor(8081);
    if (acceptor->start() == 0) {
        while (1) {
            stream = acceptor->accept();
            if (stream != NULL) {
                ssize_t len;
                char line[256];
                while ((len = stream->receive(line, sizeof(line))) > 0) {
                    line[len] = 0;
                    string cmd = string(line);
                    std::cout << "running Command: " << cmd << std::endl;
                    if( cmd == "forward"){
                        rcvCmd.type = pi2::FORWARD;
                        rcvCmd.m1speed = 15;
                        rcvCmd.m2speed = 15;
                        cmdQueue.putCommand(rcvCmd);
                    }
                    else if( cmd == "back"){
                        rcvCmd.type = pi2::BACK;
                        rcvCmd.m1speed = -15;
                        rcvCmd.m2speed = -15;
                        cmdQueue.putCommand(rcvCmd);
                    }
                    else if( cmd == "left"){
                        rcvCmd.type = pi2::LEFT;
                        rcvCmd.m1speed = 0;
                        rcvCmd.m2speed = 8;
                        cmdQueue.putCommand(rcvCmd);
                    }
                    else if( cmd == "right"){
                        rcvCmd.type = pi2::RIGHT;
                        rcvCmd.m1speed = 8;
                        rcvCmd.m2speed = 0;
                        cmdQueue.putCommand(rcvCmd);
                    }
                    else if( cmd == "stop"){
                        rcvCmd.type = pi2::STOP;
                        rcvCmd.m1speed = 0;
                        rcvCmd.m2speed = 0;
                        cmdQueue.putCommand(rcvCmd);
                    }
                    else if( cmd == "conndone"){
                        rcvCmd.type = pi2::CONNDONE;
                        rcvCmd.m1speed = 0;
                        rcvCmd.m2speed = 0;
                        cmdQueue.putCommand(rcvCmd);
                    }
                    else{
                        rcvCmd.type = pi2::NOCOMMAND;
                        rcvCmd.m1speed = 0;
                        rcvCmd.m2speed = 0;
                        cmdQueue.putCommand(rcvCmd);
                    }
                    stream->send(line, len);
                }
                delete stream;
            }

        }
    }
}