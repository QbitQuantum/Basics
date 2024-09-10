void CMetadata::toJsonstring(rapidjson::Value& json, std::string& str)
{
	rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    json.Accept(writer);
	str.assign(buffer.GetString(), buffer.Size());
}