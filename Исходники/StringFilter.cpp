StringFilter* StringFilter::GetFilter(
    /* [in] */ ValueProvider* valueProvider,
    /* [in] */ IXmlPullParser* parser,
    /* [in] */ Int32 attributeIndex)
{
    String attributeName;
    String attriValue;
    parser->GetAttributeName(attributeIndex, &attributeName);
    parser->GetAttributeValue(attributeIndex, &attriValue);

    switch (attributeName.GetChar(0)) {
        case 'e':
            if (!attributeName.Equals(ATTR_EQUALS)) {
                return NULL;
            }
            return new EqualsFilter(valueProvider, attriValue);
        case 'i':
            if (!attributeName.Equals(ATTR_IS_NULL)) {
                return NULL;
            }
            return new IsNullFilter(valueProvider, attriValue);
        case 's':
            if (!attributeName.Equals(ATTR_STARTS_WITH)) {
                return NULL;
            }
            return new StartsWithFilter(valueProvider, attriValue);
        case 'c':
            if (!attributeName.Equals(ATTR_CONTAINS)) {
                return NULL;
            }
            return new ContainsFilter(valueProvider, attriValue);
        case 'p':
            if (!attributeName.Equals(ATTR_PATTERN)) {
                return NULL;
            }
            return new PatternStringFilter(valueProvider, attriValue);
        case 'r':
            if (!attributeName.Equals(ATTR_REGEX)) {
                return NULL;
            }
            return new RegexFilter(valueProvider, attriValue);
    }
    return NULL;
}