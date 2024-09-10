string CXmlElement::getPath() const
{
    string strPathElement = "/" + getType();

    if (hasAttribute("Name")) {

        strPathElement += "[@Name=" + getNameAttribute() + "]";
    }

    CXmlElement parentElement;

    if (getParentElement(parentElement)) {

        // Done
        return parentElement.getPath() + strPathElement;
    }
    return strPathElement;
}