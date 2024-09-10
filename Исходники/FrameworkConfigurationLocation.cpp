// From IXmlSink
bool CFrameworkConfigurationLocation::fromXml(const CXmlElement &xmlElement,
                                              CXmlSerializingContext &serializingContext)
{
    xmlElement.getAttribute("Path", _configurationUri);

    if (_configurationUri.empty()) {

        serializingContext.setError("Empty Path attribute in element " + xmlElement.getPath());

        return false;
    }
    return true;
}