bool XmlRpcCarrier::sendHeader(ConnectionState& proto) {
    shouldInterpretRosMessages(proto);
    ConstString target = "POST /RPC2";
    Name n(proto.getRoute().getCarrierName() + "://test");
    ConstString pathValue = n.getCarrierModifier("path");
    if (pathValue!="") {
        target = "POST /";
        target += pathValue;
        // on the wider web, we should provide real host names
        host = NetworkBase::queryName(proto.getRoute().getToName());
    }
    target += " HTTP/1.1\n";
    http = target;
    Bytes b((char*)target.c_str(),target.length());
    proto.os().write(b);
    return true;
}