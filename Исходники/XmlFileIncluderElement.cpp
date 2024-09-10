// From IXmlSink
bool CXmlFileIncluderElement::fromXml(const CXmlElement& xmlElement, CXmlSerializingContext& serializingContext)
{
    // Context
    CXmlElementSerializingContext& elementSerializingContext = static_cast<CXmlElementSerializingContext&>(serializingContext);

    // Parse included document
    std::string strPath;
    xmlElement.getAttribute("Path", strPath);

    // Relative path?
    if (strPath[0] != '/') {

        strPath = elementSerializingContext.getXmlFolder() + "/" + strPath;
    }

    // Instantiate parser
    std::string strIncludedElementType = getIncludedElementType();
    {
        // Open a log section titled with loading file path
        CAutoLog autolog(this, "Loading " + strPath);

        // Use a doc source that load data from a file
        std::string strPathToXsdFile = elementSerializingContext.getXmlSchemaPathFolder() + "/" +
                               strIncludedElementType + ".xsd";

        _xmlDoc *doc = CXmlDocSource::mkXmlDoc(strPath, true, true, elementSerializingContext);

        CXmlDocSource docSource(doc, _bValidateSchemasOnStart,
                                strPathToXsdFile,
                                strIncludedElementType);

        if (!docSource.isParsable()) {

            elementSerializingContext.setError("Could not parse document \"" + strPath + "\"");

            return false;
        }

        // Get top level element
        CXmlElement childElement;

        docSource.getRootElement(childElement);

        // Create child element
        CElement* pChild = elementSerializingContext.getElementLibrary()->createElement(childElement);

        if (pChild) {

            // Store created child!
            getParent()->addChild(pChild);
        } else {

            elementSerializingContext.setError("Unable to create XML element " + childElement.getPath());

            return false;
        }

        // Use a doc sink that instantiate the structure from the doc source
        CXmlMemoryDocSink memorySink(pChild);

        if (!memorySink.process(docSource, elementSerializingContext)) {

            return false;
        }
    }
    // Detach from parent
    getParent()->removeChild(this);

    // Self destroy
    delete this;

    return true;
}