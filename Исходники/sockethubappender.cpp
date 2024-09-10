void* APR_THREAD_FUNC SocketHubAppender::monitor(apr_thread_t* /* thread */, void* data) {
        SocketHubAppender* pThis = (SocketHubAppender*) data;

        ServerSocket* serverSocket = 0;

        try
        {
                serverSocket = new ServerSocket(pThis->port);
                serverSocket->setSoTimeout(1000);
        }
        catch (SocketException& e)
        {
                LogLog::error(LOG4CXX_STR("exception setting timeout, shutting down server socket."), e);
                delete serverSocket;
                return NULL;
        }

        bool stopRunning = pThis->closed;
        while (!stopRunning)
        {
                SocketPtr socket;
                try
                {
                        socket = serverSocket->accept();
                }
                catch (InterruptedIOException&)
                {
                        // timeout occurred, so just loop
                }
                catch (SocketException& e)
                {
                        LogLog::error(LOG4CXX_STR("exception accepting socket, shutting down server socket."), e);
                        stopRunning = true;
                }
                catch (IOException& e)
                {
                        LogLog::error(LOG4CXX_STR("exception accepting socket."), e);
                }

                // if there was a socket accepted
                if (socket != 0)
                {
                        try
                        {
                                InetAddressPtr remoteAddress = socket->getInetAddress();
                                LogLog::debug(LOG4CXX_STR("accepting connection from ")
                                       + remoteAddress->getHostName()
                                       + LOG4CXX_STR(" (")
                                       + remoteAddress->getHostAddress()
                                       + LOG4CXX_STR(")"));

                                // add it to the oosList.
                                synchronized sync(pThis->mutex);
                                OutputStreamPtr os(new SocketOutputStream(socket));
                                Pool p;
                                ObjectOutputStreamPtr oos(new ObjectOutputStream(os, p));
                                pThis->streams.push_back(oos);
                        }
                        catch (IOException& e)
                        {
                                LogLog::error(LOG4CXX_STR("exception creating output stream on socket."), e);
                        }
                }
                stopRunning = (stopRunning || pThis->closed);
        }
        delete serverSocket;
        return NULL;
}