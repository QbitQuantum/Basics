bool CComponentInstance::fromXml(const CXmlElement& xmlElement, CXmlSerializingContext& serializingContext)
{
    // Context
    CXmlParameterSerializingContext& parameterBuildContext = static_cast<CXmlParameterSerializingContext&>(serializingContext);

    const CComponentLibrary* pComponentLibrary = parameterBuildContext.getComponentLibrary();

    std::string strComponentType = xmlElement.getAttributeString("Type");

    _pComponentType = pComponentLibrary->getComponentType(strComponentType);

    if (!_pComponentType) {

        serializingContext.setError("Unable to create Component " + xmlElement.getPath() + ". ComponentType " + strComponentType + " not found!");

        return false;
    }
    if (_pComponentType == getParent()) {

        serializingContext.setError("Recursive definition of " + _pComponentType->getName() + " due to " + xmlElement.getPath() + " referring to one of its own type.");

        return false;
    }

    return base::fromXml(xmlElement, serializingContext);
}