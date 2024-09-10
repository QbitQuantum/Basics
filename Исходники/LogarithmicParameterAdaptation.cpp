bool CLogarithmicParameterAdaptation::fromXml(const CXmlElement& xmlElement,
                                            CXmlSerializingContext& serializingContext)
{
    if (xmlElement.getAttribute("LogarithmBase", _dLogarithmBase)
        && (_dLogarithmBase <= 0 || _dLogarithmBase == 1)) {
        // Avoid negative and 1 values
        serializingContext.setError("LogarithmBase attribute cannot be negative or 1 on element"
                                    + xmlElement.getPath());

        return false;
    }

    xmlElement.getAttribute("FloorValue", _dFloorValue);

    // Base
    return base::fromXml(xmlElement, serializingContext);
}