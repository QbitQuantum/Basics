Element *Element::createFromStream(Context *rsc, IStream *stream) {
    // First make sure we are reading the correct object
    RsA3DClassID classID = (RsA3DClassID)stream->loadU32();
    if (classID != RS_A3D_CLASS_ID_ELEMENT) {
        LOGE("element loading skipped due to invalid class id\n");
        return NULL;
    }

    String8 name;
    stream->loadString(&name);

    Component component;
    component.loadFromStream(stream);

    uint32_t fieldCount = stream->loadU32();
    if (!fieldCount) {
        return (Element *)Element::create(rsc,
                                          component.getType(),
                                          component.getKind(),
                                          component.getIsNormalized(),
                                          component.getVectorSize());;
    }

    const Element **subElems = new const Element *[fieldCount];
    const char **subElemNames = new const char *[fieldCount];
    size_t *subElemNamesLengths = new size_t[fieldCount];
    uint32_t *arraySizes = new uint32_t[fieldCount];

    String8 elemName;
    for (uint32_t ct = 0; ct < fieldCount; ct ++) {
        stream->loadString(&elemName);
        subElemNamesLengths[ct] = elemName.length();
        char *tmpName = new char[subElemNamesLengths[ct]];
        memcpy(tmpName, elemName.string(), subElemNamesLengths[ct]);
        subElemNames[ct] = tmpName;
        arraySizes[ct] = stream->loadU32();
        subElems[ct] = Element::createFromStream(rsc, stream);
    }

    const Element *elem = Element::create(rsc, fieldCount, subElems, subElemNames,
                                          subElemNamesLengths, arraySizes);
    for (uint32_t ct = 0; ct < fieldCount; ct ++) {
        delete [] subElemNames[ct];
        subElems[ct]->decUserRef();
    }
    delete[] subElems;
    delete[] subElemNames;
    delete[] subElemNamesLengths;
    delete[] arraySizes;

    return (Element *)elem;
}