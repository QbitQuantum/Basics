 std::shared_ptr<std::string> JIMDBClient::toString(rapidjson::Value& data)
 {
     // Convert JSON document to string
     rapidjson::StringBuffer strbuf;
     rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
     data.Accept(writer);
     return std::make_shared<std::string>(strbuf.GetString());
 }