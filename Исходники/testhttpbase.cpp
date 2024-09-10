bool TestThread::test_02_get_with_keepalive()
{
    if(! connectSocket())
	return false;

    String req("GET /test/1 HTTP/1.0\r\nConnection: keep-alive\r\n\r\n");
    int w = m_sock.send(req.c_str(), req.length());
    Debug(DebugAll, "Sent %d bytes to server: <<%s>>", w, req.c_str());
    Debug(DebugAll, "Shutting down sending part");
    m_sock.shutdown(false, true);
    char buf[8192];
    Debug(DebugAll, "Waiting for reply");
    int r = m_sock.readData(buf, sizeof(buf) - 1);
    if(r < 0) {
	Debug(DebugFail, "Socket read error: %s", strerror(m_sock.error()));
	return false;
    }
    String s;
    if(r >= 0) {
	buf[r] = 0;
	s = buf;
    }
    Output("Got HTTP response (%d bytes): %s\n", r, s.c_str());
    m_sock.shutdown(true, true);
    m_sock.terminate();

    m_sock.shutdown(true, true);
    m_sock.terminate();
    return true;
}