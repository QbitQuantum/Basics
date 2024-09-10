// From IXmlSink
bool CLinearParameterAdaptation::fromXml(const CXmlElement& xmlElement, CXmlSerializingContext& serializingContext)
{
    // Get SlopeNumerator
    xmlElement.getAttribute("SlopeNumerator", _dSlopeNumerator);

    // Get SlopeDenominator
    if (xmlElement.getAttribute("SlopeDenominator", _dSlopeDenominator)
        && (_dSlopeDenominator == 0)) {

        // Avoid by 0 division errors
        serializingContext.setError("SlopeDenominator attribute can't be 0 on element" + xmlElement.getPath());
        return false;
    }

    // Base
    return base::fromXml(xmlElement, serializingContext);
}