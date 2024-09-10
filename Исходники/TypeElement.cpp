bool CTypeElement::fromXml(const CXmlElement &xmlElement,
                           CXmlSerializingContext &serializingContext)
{
    // Array Length attribute
    xmlElement.getAttribute("ArrayLength", _arrayLength);
    // Manage mapping attribute
    std::string rawMapping;
    if (xmlElement.getAttribute("Mapping", rawMapping) && !rawMapping.empty()) {

        std::string error;
        if (!getMappingData()->init(rawMapping, error)) {

            serializingContext.setError("Invalid Mapping data from XML element '" +
                                        xmlElement.getPath() + "': " + error);
            return false;
        }
    }
    return base::fromXml(xmlElement, serializingContext);
}