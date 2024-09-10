bool CComponentType::fromXml(const CXmlElement &xmlElement,
                             CXmlSerializingContext &serializingContext)
{
    // Context
    CXmlParameterSerializingContext &parameterBuildContext =
        static_cast<CXmlParameterSerializingContext &>(serializingContext);

    const CComponentLibrary *pComponentLibrary = parameterBuildContext.getComponentLibrary();

    // Populate children
    if (!base::fromXml(xmlElement, serializingContext)) {

        return false;
    }

    // Check for Extends attribute (extensions will be populated after and not before)
    if (xmlElement.hasAttribute("Extends")) {

        std::string strExtendsType;
        xmlElement.getAttribute("Extends", strExtendsType);

        _pExtendsComponentType = pComponentLibrary->getComponentType(strExtendsType);

        if (!_pExtendsComponentType) {

            serializingContext.setError("ComponentType " + strExtendsType + " referred to by " +
                                        xmlElement.getPath() + " not found!");

            return false;
        }

        if (_pExtendsComponentType == this) {

            serializingContext.setError("Recursive ComponentType definition of " +
                                        xmlElement.getPath());

            return false;
        }
    }

    return true;
}