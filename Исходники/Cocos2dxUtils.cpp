std::string minius::rapidjsonToString(const rapidjson::Document& document)
{
	rapidjson::StringBuffer stringBuffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(stringBuffer);
	document.Accept(writer);

	std::string message = stringBuffer.GetString();
	return message;
}