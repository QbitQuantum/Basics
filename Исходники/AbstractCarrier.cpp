bool AbstractCarrier::sendSenderSpecifier(ConnectionState& proto)
{
    NetInt32 numberSrc;
    Bytes number((char*)&numberSrc, sizeof(NetInt32));
    const ConstString senderName = proto.getSenderSpecifier();
    //const ConstString& senderName = getRoute().getFromName();
    NetType::netInt((int)senderName.length()+1, number);
    OutputStream& os = proto.os();
    os.write(number);
    Bytes b((char*)senderName.c_str(), senderName.length()+1);
    os.write(b);
    os.flush();
    return os.isOk();
}