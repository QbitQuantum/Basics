SVGFontElement* FontResource::getSVGFontById(const String& fontName) const
{
    RefPtr<HTMLCollection> collection = m_externalSVGDocument->getElementsByTagNameNS(SVGNames::fontTag.namespaceURI(), SVGNames::fontTag.localName());
    if (!collection)
        return 0;

    unsigned collectionLength = collection->length();
    if (!collectionLength)
        return 0;

#ifndef NDEBUG
    for (unsigned i = 0; i < collectionLength; ++i) {
        ASSERT(collection->item(i));
        ASSERT(isSVGFontElement(collection->item(i)));
    }
#endif

    if (fontName.isEmpty())
        return toSVGFontElement(collection->item(0));

    for (unsigned i = 0; i < collectionLength; ++i) {
        SVGFontElement* element = toSVGFontElement(collection->item(i));
        if (element->getIdAttribute() == fontName)
            return element;
    }

    return 0;
}