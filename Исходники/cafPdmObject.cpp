//--------------------------------------------------------------------------------------------------
/// Check if a string is a valid Xml element name
//
/// http://www.w3schools.com/xml/xml_elements.asp
///
/// XML elements must follow these naming rules:
///   Names can contain letters, numbers, and other characters
///   Names cannot start with a number or punctuation character
///   Names cannot start with the letters xml (or XML, or Xml, etc)
///   Names cannot contain spaces
//--------------------------------------------------------------------------------------------------
bool PdmObject::isValidXmlElementName(const QString& name)
{
    if (name.size() > 0)
    {
        QChar firstChar = name[0];
        if (firstChar.isDigit() || firstChar == '.')
        {
            return false;
        }
    }

    if (name.size() >= 3)
    {
        if (name.left(3).compare("xml", Qt::CaseInsensitive) == 0)
        {
            return false;
        }
    }

    if (name.contains(' '))
    {
        return false;
    }

    return true;
}