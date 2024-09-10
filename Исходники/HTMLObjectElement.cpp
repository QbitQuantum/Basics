bool HTMLObjectElement::shouldAllowQuickTimeClassIdQuirk()
{
    // This site-specific hack maintains compatibility with Mac OS X Wiki Server,
    // which embeds QuickTime movies using an object tag containing QuickTime's
    // ActiveX classid. Treat this classid as valid only if OS X Server's unique
    // 'generator' meta tag is present. Only apply this quirk if there is no
    // fallback content, which ensures the quirk will disable itself if Wiki
    // Server is updated to generate an alternate embed tag as fallback content.
    if (!document()->page()
        || !document()->page()->settings()->needsSiteSpecificQuirks()
        || hasFallbackContent()
        || !equalIgnoringCase(classId(), "clsid:02BF25D5-8C17-4B23-BC80-D3488ABDDC6B"))
        return false;

    RefPtr<NodeList> metaElements = document()->getElementsByTagName(HTMLNames::metaTag.localName());
    unsigned length = metaElements->length();
    for (unsigned i = 0; i < length; ++i) {
        ASSERT(metaElements->item(i)->isHTMLElement());
        HTMLMetaElement* metaElement = static_cast<HTMLMetaElement*>(metaElements->item(i));
        if (equalIgnoringCase(metaElement->name(), "generator") && metaElement->content().startsWith("Mac OS X Server Web Services Server", false))
            return true;
    }
    
    return false;
}