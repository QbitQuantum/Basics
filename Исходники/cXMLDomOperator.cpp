bool cXMLDom::operator () (const bool value)
{
    // get the attribute as a boolean...
    if (this->getAttribute ())
    {
        // boolean can be alphanumerical...
        if (this->_attributeValue[0] == 'T') return true;
        else if (this->_attributeValue[0] == 't') return true;
        else if (this->_attributeValue[0] == 'Y') return true;
        else if (this->_attributeValue[0] == 'y') return true;
        // boolean can be numerical...
        else if (_wtol (this->_attributeValue)) return true;
        // no truths...
        return false;
    }
    // return the value as default...
    return value;
}