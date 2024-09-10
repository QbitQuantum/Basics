/// Blocks until either the stream encounters a pause mark or the sourceSocket errors.
/// This function is intended to be run after the 'q' command is sent, throwing away superfluous packets.
/// It will time out after 5 seconds, disconnecting the sourceSocket.
void DTSC::Stream::waitForPause(Socket::Connection & sourceSocket) {
  bool wasBlocking = sourceSocket.isBlocking();
  sourceSocket.setBlocking(false);
  //cancel the attempt after 5000 milliseconds
  long long int start = Util::getMS();
  while (lastType() != DTSC::PAUSEMARK && sourceSocket.connected() && Util::getMS() - start < 5000) {
    //we have data? parse it
    if (sourceSocket.Received().size()) {
      //return value is ignored because we're not interested.
      parsePacket(sourceSocket.Received());
    }
    //still no pause mark? check for more data
    if (lastType() != DTSC::PAUSEMARK) {
      if (sourceSocket.spool()) {
        //more received? attempt to read
        //return value is ignored because we're not interested in data packets, just metadata.
        parsePacket(sourceSocket.Received());
      } else {
        //nothing extra to receive? wait a bit and retry
        Util::sleep(10);
      }
    }
  }
  sourceSocket.setBlocking(wasBlocking);
  //if the timeout has passed, close the socket
  if (Util::getMS() - start >= 5000) {
    sourceSocket.close();
    //and optionally print a debug message that this happened
    DEBUG_MSG(DLVL_DEVEL, "Timing out while waiting for pause break");
  }
}