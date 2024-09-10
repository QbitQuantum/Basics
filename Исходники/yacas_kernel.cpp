void YacasKernel::Request::reply(zmqpp::socket& socket, const std::string& msg_type, const Json::Value& content) const
{
    Json::Value header;
    header["username"] = "******";
    header["version"] = "5.0";
    header["session"] = boost::uuids::to_string(_session.uuid());
    header["date"]  = now();
    header["msg_id"] = boost::uuids::to_string(_session.generate_msg_uuid());
    header["msg_type"] = msg_type;

    Json::StreamWriterBuilder builder;

    const std::string content_buf = Json::writeString(builder, content);
    // FIXME:
    const std::string metadata_buf = "{}";
    const std::string header_buf = Json::writeString(builder, header);
    const std::string parent_header_buf = Json::writeString(builder, _header);
    
    HMAC_SHA256 auth(_session.auth());
    
    auth.update(header_buf);
    auth.update(parent_header_buf);
    auth.update(metadata_buf);
    auth.update(content_buf);
    
    zmqpp::message msg;
    msg.add(_identities_buf);
    msg.add("<IDS|MSG>");
    msg.add(auth.hexdigest());
    msg.add(header_buf);
    msg.add(parent_header_buf);
    msg.add(metadata_buf);
    msg.add(content_buf);
    
    socket.send(msg);
}