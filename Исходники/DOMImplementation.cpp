PassRefPtr<Document> DOMImplementation::createDocument(const String& namespaceURI,
    const String& qualifiedName, DocumentType* doctype, ExceptionCode& ec)
{
    if (!qualifiedName.isEmpty()) {
        // INVALID_CHARACTER_ERR: Raised if the specified qualified name contains an illegal character.
        String prefix, localName;
        if (!Document::parseQualifiedName(qualifiedName, prefix, localName)) {
            ec = INVALID_CHARACTER_ERR;
            return 0;
        }

        // NAMESPACE_ERR:
        // - Raised if the qualifiedName is malformed,
        // - if the qualifiedName has a prefix and the namespaceURI is null, or
        // - if the qualifiedName has a prefix that is "xml" and the namespaceURI is different
        //   from "http://www.w3.org/XML/1998/namespace" [Namespaces].
        int colonpos = -1;
        unsigned i;
        StringImpl *qname = qualifiedName.impl();
        for (i = 0; i < qname->length() && colonpos < 0; i++) {
            if ((*qname)[i] == ':')
                colonpos = i;
        }
    
        if (qualifiedNameIsMalformed(qualifiedName) ||
            (colonpos >= 0 && namespaceURI.isNull()) ||
            (colonpos == 3 && qualifiedName[0] == 'x' && qualifiedName[1] == 'm' && qualifiedName[2] == 'l' &&
#if ENABLE(SVG)
             namespaceURI != SVGNames::svgNamespaceURI &&
#endif
             namespaceURI != XMLNames::xmlNamespaceURI)) {

            ec = NAMESPACE_ERR;
            return 0;
        }
    }
    
    // WRONG_DOCUMENT_ERR: Raised if doctype has already been used with a different document or was
    // created from a different implementation.
    if (doctype && (doctype->document() || doctype->implementation() != this)) {
        ec = WRONG_DOCUMENT_ERR;
        return 0;
    }

    RefPtr<Document> doc;
#if ENABLE(SVG)
    if (namespaceURI == SVGNames::svgNamespaceURI)
        doc = new SVGDocument(this, 0);
    else
#endif
        if (namespaceURI == HTMLNames::xhtmlNamespaceURI)
            doc = new Document(this, 0, true);
        else
            doc = new Document(this, 0);

    // now get the interesting parts of the doctype
    if (doctype) {
        doc->setDocType(doctype);
        doctype->setDocument(doc.get());
    }

    if (!qualifiedName.isEmpty())
        doc->addChild(doc->createElementNS(namespaceURI, qualifiedName, ec));
    
    ec = 0;
    return doc.release();
}