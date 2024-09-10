SVGFontElement* CachedFont::getSVGFontById(const String& fontName) const
{
    RefPtr<NodeList> list = m_externalSVGDocument->getElementsByTagNameNS(SVGNames::fontTag.namespaceURI(), SVGNames::fontTag.localName());
    if (!list)
        return 0;

    unsigned listLength = list->length();
    if (!listLength)
        return 0;

#ifndef NDEBUG
    for (unsigned i = 0; i < listLength; ++i) {
        ASSERT(list->item(i));
        ASSERT(list->item(i)->hasTagName(SVGNames::fontTag));
    }
#endif

    if (fontName.isEmpty())
        return static_cast<SVGFontElement*>(list->item(0));

    for (unsigned i = 0; i < listLength; ++i) {
        SVGFontElement* element = static_cast<SVGFontElement*>(list->item(i));
        if (element->getIdAttribute() == fontName)
            return element;
    }

    return 0;
}