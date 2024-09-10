AsynchIO::AsynchIO(const Socket& s,
                   ReadCallback rCb, EofCallback eofCb, DisconnectCallback disCb,
                   ClosedCallback cCb, BuffersEmptyCallback eCb, IdleCallback iCb) :

    DispatchHandle(s, 
                   boost::bind(&AsynchIO::readable, this, _1),
                   boost::bind(&AsynchIO::writeable, this, _1),
                   boost::bind(&AsynchIO::disconnected, this, _1)),
    readCallback(rCb),
    eofCallback(eofCb),
    disCallback(disCb),
    closedCallback(cCb),
    emptyCallback(eCb),
    idleCallback(iCb),
    socket(s),
    queuedClose(false),
    writePending(false) {

    s.setNonblocking();
}