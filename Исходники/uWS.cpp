// default fragment handler
void Server::internalFragment(Socket socket, const char *fragment, size_t length, OpCode opCode, bool fin, size_t remainingBytes)
{
    uv_poll_t *p = (uv_poll_t *) socket.socket;
    SocketData *socketData = (SocketData *) p->data;

    // Text or binary
    if (opCode < 3) {

        if (!remainingBytes && fin && !socketData->buffer.length()) {

            // todo: check chapter 6 here also!
            /*if (opCode == 1 && !Server::isValidUtf8(socketData->buffer)) {
                socketData->server->disconnectionCallback(p);
                socket.fail();
                return;
            }*/

            socketData->server->messageCallback(socket, (char *) fragment, length, opCode);
        } else {

            socketData->buffer.append(fragment, length);
            if (!remainingBytes && fin) {

                // Chapter 6
                if (opCode == 1 && !Server::isValidUtf8(socketData->buffer)) {
                    socketData->server->disconnectionCallback(p);
                    socket.fail();
                    return;
                }

                socketData->server->messageCallback(socket, (char *) socketData->buffer.c_str(), socketData->buffer.length(), opCode);
                socketData->buffer.clear();
            }
        }

    } else {

        // swap PING/PONG
        if (opCode == PING) {
            opCode = PONG;
        } else if (opCode == PONG) {
            opCode = PING;
        }

        /*if (remainingBytes) {
            if ()
        } else {
        socket.send((char *) fragment, length, opCode);*/

        // append to a separate buffer for control messages
        socketData->controlBuffer.append(fragment, length);
        if (!remainingBytes && fin) {
            socket.send((char *) socketData->controlBuffer.c_str(), socketData->controlBuffer.length(), opCode);
            socketData->controlBuffer.clear();
        }
    }
}