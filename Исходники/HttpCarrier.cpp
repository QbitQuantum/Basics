bool yarp::os::impl::HttpCarrier::sendHeader(ConnectionState& proto) {
    ConstString target = "GET / HTTP/1.0\r\n";
    ConstString path = proto.getRoute().getToName();
    if (path.size()>=2) {
        target = "GET " + path + " HTTP/1.0\r\n";
    }
    Contact host = proto.getRoute().getToContact();
    if (host.getHost()!="") {
        target += "Host: ";
        target += host.getHost();
        target += "\r\n";
    }
    target += "\r\n";
    Bytes b((char*)target.c_str(),target.length());
    proto.os().write(b);
    return true;

}