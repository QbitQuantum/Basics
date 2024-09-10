void XmlConfigFile::SetInteger( const std::string& key, long nValue )
{
	if (key.empty())
	{
		LOGE<<"key is empty.";
		return;
	}
	tinyxml2::XMLNode* pNode = _GetXmlNode(key);
	if (pNode == nullptr)
	{
		LOGE<<"pNode is null.";
		return ;
	}

	tinyxml2::XMLElement* pXmlElement = pNode->ToElement();
	if (pXmlElement != NULL)
	{
		if (_IsAttribute(key))
		{
			std::string strAttrName = _GetAttributeName(key);
			pXmlElement->SetAttribute(strAttrName.c_str(), nValue);
		}
		else
		{
			char buff[32] = {0};
			_ltoa(nValue, buff, 10);
			pXmlElement->SetText(buff);
		}
	}
}