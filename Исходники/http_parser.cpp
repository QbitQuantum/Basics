/// After receiving a header with this object, this function call will:
/// - Forward the headers to the 'to' Socket::Connection.
/// - Retrieve all the body from the 'from' Socket::Connection.
/// - Forward those contents as-is to the 'to' Socket::Connection.
/// It blocks until completed or either of the connections reaches an error state.
void HTTP::Parser::Proxy(Socket::Connection & from, Socket::Connection & to) {
  SendResponse(url, method, to);
  if (getChunks) {
    unsigned int proxyingChunk = 0;
    while (to.connected() && from.connected()) {
      if ((from.Received().size() && (from.Received().size() > 1 || *(from.Received().get().rbegin()) == '\n')) || from.spool()) {
        if (proxyingChunk) {
          while (proxyingChunk && from.Received().size()) {
            unsigned int toappend = from.Received().get().size();
            if (toappend > proxyingChunk) {
              toappend = proxyingChunk;
              to.SendNow(from.Received().get().c_str(), toappend);
              from.Received().get().erase(0, toappend);
            } else {
              to.SendNow(from.Received().get());
              from.Received().get().clear();
            }
            proxyingChunk -= toappend;
          }
        } else {
          //Make sure the received data ends in a newline (\n).
          if (*(from.Received().get().rbegin()) != '\n') {
            if (from.Received().size() > 1) {
              //make a copy of the first part
              std::string tmp = from.Received().get();
              //clear the first part, wiping it from the partlist
              from.Received().get().clear();
              from.Received().size();
              //take the now first (was second) part, insert the stored part in front of it
              from.Received().get().insert(0, tmp);
            } else {
              Util::sleep(100);
            }
            if (*(from.Received().get().rbegin()) != '\n') {
              continue;
            }
          }
          //forward the size and any empty lines
          to.SendNow(from.Received().get());

          std::string tmpA = from.Received().get().substr(0, from.Received().get().size() - 1);
          while (tmpA.find('\r') != std::string::npos) {
            tmpA.erase(tmpA.find('\r'));
          }
          unsigned int chunkLen = 0;
          if (!tmpA.empty()) {
            for (unsigned int i = 0; i < tmpA.size(); ++i) {
              chunkLen = (chunkLen << 4) | unhex(tmpA[i]);
            }
            if (chunkLen == 0) {
              getChunks = false;
              to.SendNow("\r\n", 2);
              return;
            }
            proxyingChunk = chunkLen;
          }
          from.Received().get().clear();
        }
      } else {
        Util::sleep(100);
      }
    }
  } else {
    unsigned int bodyLen = length;
    while (bodyLen > 0 && to.connected() && from.connected()) {
      if (from.Received().size() || from.spool()) {
        if (from.Received().get().size() <= bodyLen) {
          to.SendNow(from.Received().get());
          bodyLen -= from.Received().get().size();
          from.Received().get().clear();
        } else {
          to.SendNow(from.Received().get().c_str(), bodyLen);
          from.Received().get().erase(0, bodyLen);
          bodyLen = 0;
        }
      } else {
        Util::sleep(100);
      }
    }
  }
}