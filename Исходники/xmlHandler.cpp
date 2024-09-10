bool MXMLHandler::SetNode(string& xml, string name, string value, unsigned long& start)
{
	Escape(name);
	if (name.length() == 0)
		return false;

	if (value.length() == 0)
	{
		MXMLHandler::RemoveNode(xml, name);
		return true;
	}

	string::size_type begin = xml.find("<"+name+">",start);
	string::size_type end = xml.find("</"+name+">", begin + name.length() + 2);

	if ((begin != string::npos) && (end != string::npos))
	{
		begin += name.length() + 2;
		xml = xml.substr(0, begin) + value + xml.substr(end, xml.length() - end);
		start = begin + value.length() + name.length() + 3;
		return true;
	}
	return false;
}