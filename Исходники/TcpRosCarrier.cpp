bool TcpRosCarrier::checkHeader(const Bytes& header) {
    if (header.length()!=8) {
        return false;
    }
    setParameters(header);
    if (!(headerLen1<60000&&headerLen1>0 &&
          headerLen2<60000&&headerLen2>0)) {
        // not tcpros
        return false;
    }
    // plausibly tcpros.
    dbg_printf("tcpros! %d %d\n", headerLen1,headerLen2);
    return true;
}