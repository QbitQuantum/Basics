int Dynamo::Json2str(const rapidjson::Value &json, std::string& str) {
	StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);

    if (false == json.Accept(writer)) {
    	snprintf(lastErr, sizeof(lastErr), "Value::Accept failed");
    	return -1;
    }
    str.append(buffer.GetString(), buffer.GetSize());

    return 0;
}