//--------------------------------------------------------------------------------------------------
/// 
//--------------------------------------------------------------------------------------------------
bool XmlElementImpl::getAttributeBool(const String& attributeName, bool defaultVal, bool* found /*= NULL*/) const
{
    if (found) *found = false;

    String val;
    const char* attrValue = Attribute(attributeName.toUtf8().ptr());
    if (attrValue)
    {
        val = attrValue;
    }
    
    if (val.isEmpty()) return defaultVal;

    if (found) *found = true;

    if (val[0] == '1') return true;
    if (val[0] == '0') return false;

    val.toLower();

    if (val == "yes" || val == "on" || val == "true") return true;
    if (val == "no"  || val == "off" || val == "false") return false;

    return defaultVal;
}