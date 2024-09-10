// From IXmlSink
bool CSelectionCriterionRule::fromXml(const CXmlElement &xmlElement,
                                      CXmlSerializingContext &serializingContext)
{
    // Retrieve actual context
    CXmlDomainImportContext &xmlDomainImportContext =
        static_cast<CXmlDomainImportContext &>(serializingContext);

    // Get selection criterion
    string strSelectionCriterion;
    xmlElement.getAttribute("SelectionCriterion", strSelectionCriterion);

    _pSelectionCriterion =
        xmlDomainImportContext.getSelectionCriteriaDefinition()->getSelectionCriterion(
            strSelectionCriterion);

    // Check existence
    if (!_pSelectionCriterion) {

        xmlDomainImportContext.setError("Couldn't find selection criterion " +
                                        strSelectionCriterion + " in " + getKind() + " " +
                                        xmlElement.getPath());

        return false;
    }

    // Get MatchesWhen
    string strMatchesWhen;
    xmlElement.getAttribute("MatchesWhen", strMatchesWhen);
    string strError;

    if (!setMatchesWhen(strMatchesWhen, strError)) {

        xmlDomainImportContext.setError("Wrong MatchesWhen attribute " + strMatchesWhen + " in " +
                                        getKind() + " " + xmlElement.getPath() + ": " + strError);

        return false;
    }

    // Get Value
    string strValue;
    xmlElement.getAttribute("Value", strValue);

    if (!_pSelectionCriterion->getCriterionType()->getNumericalValue(strValue, _iMatchValue)) {

        xmlDomainImportContext.setError("Wrong Value attribute value " + strValue + " in " +
                                        getKind() + " " + xmlElement.getPath());

        return false;
    }

    // Done
    return true;
}