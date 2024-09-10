/* ===  FUNCTION  ==============================================================
 *         Name:  listenerFlow
 *  Description:  The bird listens for incoming messages here
 * =============================================================================
 */
static void listenerFlow ()
{
 UDPSocket listenSocket (DB_LISTEN_PORT);

  while (true) {
    // Block for msg receipt
    int inMsgSize;
    char *inMsg;
    inMsg = new char[MAX_MSG_SIZE]();
    try {
      inMsgSize = listenSocket.recv(inMsg, MAX_MSG_SIZE);
    } catch (SocketException &e) {
      cout<<"DB: "<<e.what()<<endl;
    }
    inMsg[inMsgSize] = '\0';

    thread handlerThread (dbMsgHandler, inMsgSize, inMsg);
    handlerThread.detach();
  }
}   /* -----  end of function listenerFlow  ----- */