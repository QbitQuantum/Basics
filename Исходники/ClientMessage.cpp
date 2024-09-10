            int32_t ClientMessage::writeTo(Socket &socket, int32_t offset, int32_t frameLen) {
                int32_t numBytesSent = 0;

                int32_t numBytesLeft = frameLen - offset;
                if (numBytesLeft > 0) {
                    numBytesSent = socket.send(buffer + offset, numBytesLeft);
                }

                return numBytesSent;
            }