bool MjpegCarrier::sendHeader(ConnectionState& proto) {
    Name n(proto.getRoute().getCarrierName() + "://test");
    ConstString pathValue = n.getCarrierModifier("path");
    ConstString target = "GET /?action=stream\n\n";
    if (pathValue!="") {
        target = "GET /";
        target += pathValue;
    }
    target += " HTTP/1.1\n\n";
    Bytes b((char*)target.c_str(),target.length());
    proto.os().write(b);
    return true;
}