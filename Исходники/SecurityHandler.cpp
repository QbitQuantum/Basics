StandardSecurityHandler::StandardSecurityHandler(PDFDoc *docA,
        Object *encryptDictA):
    SecurityHandler(docA)
{
    Object versionObj, revisionObj, lengthObj;
    Object ownerKeyObj, userKeyObj, permObj, fileIDObj;
    Object fileIDObj1;
    Object cryptFiltersObj, streamFilterObj, stringFilterObj;
    Object cryptFilterObj, cfmObj, cfLengthObj;
    Object encryptMetadataObj;

    ok = gFalse;
    fileID = NULL;
    ownerKey = NULL;
    userKey = NULL;

    encryptDictA->dictLookup("V", &versionObj);
    encryptDictA->dictLookup("R", &revisionObj);
    encryptDictA->dictLookup("Length", &lengthObj);
    encryptDictA->dictLookup("O", &ownerKeyObj);
    encryptDictA->dictLookup("U", &userKeyObj);
    encryptDictA->dictLookup("P", &permObj);
    doc->getXRef()->getTrailerDict()->dictLookup("ID", &fileIDObj);
    if (versionObj.isInt() &&
            revisionObj.isInt() &&
            ownerKeyObj.isString() && ownerKeyObj.getString()->getLength() == 32 &&
            userKeyObj.isString() && userKeyObj.getString()->getLength() == 32 &&
            permObj.isInt()) {
        encVersion = versionObj.getInt();
        encRevision = revisionObj.getInt();
        encAlgorithm = cryptRC4;
        // revision 2 forces a 40-bit key - some buggy PDF generators
        // set the Length value incorrectly
        if (encRevision == 2 || !lengthObj.isInt()) {
            fileKeyLength = 5;
        } else {
            fileKeyLength = lengthObj.getInt() / 8;
        }
        encryptMetadata = gTrue;
        //~ this currently only handles a subset of crypt filter functionality
        if (encVersion == 4 && encRevision == 4) {
            encryptDictA->dictLookup("CF", &cryptFiltersObj);
            encryptDictA->dictLookup("StmF", &streamFilterObj);
            encryptDictA->dictLookup("StrF", &stringFilterObj);
            if (cryptFiltersObj.isDict() &&
                    streamFilterObj.isName() &&
                    stringFilterObj.isName() &&
                    !strcmp(streamFilterObj.getName(), stringFilterObj.getName())) {
                if (cryptFiltersObj.dictLookup(streamFilterObj.getName(),
                                               &cryptFilterObj)->isDict()) {
                    cryptFilterObj.dictLookup("CFM", &cfmObj);
                    if (cfmObj.isName("V2")) {
                        encVersion = 2;
                        encRevision = 3;
                        if (cryptFilterObj.dictLookup("Length", &cfLengthObj)->isInt()) {
                            //~ according to the spec, this should be cfLengthObj / 8
                            fileKeyLength = cfLengthObj.getInt();
                        }
                        cfLengthObj.free();
                    } else if (cfmObj.isName("AESV2")) {
                        encVersion = 2;
                        encRevision = 3;
                        encAlgorithm = cryptAES;
                        if (cryptFilterObj.dictLookup("Length", &cfLengthObj)->isInt()) {
                            //~ according to the spec, this should be cfLengthObj / 8
                            fileKeyLength = cfLengthObj.getInt();
                        }
                        cfLengthObj.free();
                    }
                    cfmObj.free();
                }
                cryptFilterObj.free();
            }
            stringFilterObj.free();
            streamFilterObj.free();
            cryptFiltersObj.free();
            if (encryptDictA->dictLookup("EncryptMetadata",
                                         &encryptMetadataObj)->isBool()) {
                encryptMetadata = encryptMetadataObj.getBool();
            }
            encryptMetadataObj.free();
        }
        permFlags = permObj.getInt();
        ownerKey = ownerKeyObj.getString()->copy();
        userKey = userKeyObj.getString()->copy();
        if (encVersion >= 1 && encVersion <= 2 &&
                encRevision >= 2 && encRevision <= 3) {
            if (fileIDObj.isArray()) {
                if (fileIDObj.arrayGet(0, &fileIDObj1)->isString()) {
                    fileID = fileIDObj1.getString()->copy();
                } else {
                    fileID = new GooString();
                }
                fileIDObj1.free();
            } else {
                fileID = new GooString();
            }
            ok = gTrue;
        } else {
            error(-1, "Unsupported version/revision (%d/%d) of Standard security handler",
                  encVersion, encRevision);
        }
    } else {
        error(-1, "Weird encryption info");
    }
    if (fileKeyLength > 16) {
        fileKeyLength = 16;
    }
    fileIDObj.free();
    permObj.free();
    userKeyObj.free();
    ownerKeyObj.free();
    lengthObj.free();
    revisionObj.free();
    versionObj.free();
}