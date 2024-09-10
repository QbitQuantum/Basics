void XmlSchema::addSimpleMember(const XmlNode* child, String& structDefinition, size_t typeWidth,
								 String& readingFunction, String& writingFunction) const
{
	assert(child != NULL);

	XmlAttribute* type = child->findAttribute(ATTR_TYPE);
	XmlAttribute* defaultAttribute = child->findAttribute(ATTR_DEFAULT);
	bool inAttribute = (child->findAttribute(ATTR_ATTRIBUTE) != NULL);
	if (type == NULL)
	{
		return;
	}
	String typeString = getSimpleTypeString(type);
	size_t thisWidth = typeString.size();
	assert(thisWidth < typeWidth + 1);
	for (size_t i = 0; i < typeWidth + 1 - thisWidth; ++i)
	{
		typeString += T(" ");
	}
	
	structDefinition += T("	");
	structDefinition += typeString;
	structDefinition += child->getName();
	structDefinition += T(";\r\n");	

	readingFunction += inAttribute ? T("\r\n	attribute = node->findAttribute(")
									: T("\r\n	childNode = node->findChild(");
	readingFunction += LEFT_QUOTE;
	readingFunction += child->getName();
	readingFunction += inAttribute ? T("\");\r\n	if (attribute != NULL)\r\n	{\r\n		")
									: T("\");\r\n	if (childNode != NULL)\r\n	{\r\n		");
	readingFunction += child->getName();
	readingFunction += inAttribute ? T(" = attribute->get")
									: T(" = childNode->get");
	String typeName = type->getString();
	typeName[0] -= 32;
	readingFunction += typeName;
	readingFunction += T("();\r\n	}\r\n");

	writingFunction += T("\r\n	if (");
	writingFunction += child->getName();
	writingFunction += T(" != ");

	if (defaultAttribute != NULL)
	{
		//with initialized value
		if (Strcmp(type->getString(), T("string")) == 0)
		{
			writingFunction += LEFT_QUOTE;
		}
		writingFunction += defaultAttribute->getString();
		if (Strcmp(type->getString(), T("string")) == 0)
		{
			writingFunction += T("\"");
		}
	}
	else
	{
		writingFunction += getTypeDefaultValue(type->getString());
	}

	writingFunction += inAttribute ? T(")\r\n	{\r\n		attribute = node->addAttribute(")
									: T(")\r\n	{\r\n		childNode = node->addChild(");
	writingFunction += LEFT_QUOTE;
	writingFunction += child->getName();
	writingFunction += inAttribute ? T("\");\r\n		attribute->set")
									: T("\");\r\n		childNode->set");
	typeName = type->getString();
	typeName[0] -= 32;
	writingFunction += typeName;
	writingFunction += T("(");
	writingFunction += child->getName();
	writingFunction += T(");\r\n	}\r\n");
}