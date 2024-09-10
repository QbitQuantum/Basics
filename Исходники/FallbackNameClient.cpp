void FallbackNameClient::run() {
    NameConfig nc;
    Contact call = FallbackNameServer::getAddress();
    DgramTwoWayStream send;
    send.join(call, true);
    listen.join(call, false);
    if (!listen.isOk()) {
        YARP_ERROR(Logger::get(), ConstString("Multicast not available"));
        return;
    }
    ConstString msg = ConstString("NAME_SERVER query ") + nc.getNamespace();
    send.beginPacket();
    send.writeLine(msg.c_str(), (int)msg.length());
    send.flush();
    send.endPacket();
    for (int i=0; i<5; i++) {
        listen.beginPacket();
        ConstString txt = listen.readLine();
        listen.endPacket();
        if (closed) return;
        YARP_DEBUG(Logger::get(), ConstString("Fallback name client got ") + txt);
        if (txt.find("registration ")==0) {
            address = NameClient::extractAddress(txt);
            YARP_INFO(Logger::get(), ConstString("Received address ") +
                      address.toURI());
            return;
        }
    }
}