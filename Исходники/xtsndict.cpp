// The createXrecord() functions creates an xrecord object, 
// adds data to it, and then adds the xrecord to the extension 
// dictionary of a user selected object.
// 
// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.
//
void
createXrecord()
{
    AcDbXrecord *pXrec = new AcDbXrecord;
    AcDbObject *pObj;
    AcDbObjectId dictObjId, xrecObjId;
    AcDbDictionary* pDict;

    pObj = selectObject(AcDb::kForWrite);
    if (pObj == NULL) {
        return;
    }

    // Try to create an extension dictionary for this
    // object.  If the extension dictionary already exists,
    // this will be a no-op.
    // 
    pObj->createExtensionDictionary();

    // Get the object ID of the extension dictionary for the
    // selected object.
    // 
    dictObjId = pObj->extensionDictionary();
    pObj->close();

    // Open the extension dictionary and add the new
    // xrecord to it.
    //
    acdbOpenObject(pDict, dictObjId, AcDb::kForWrite);
    pDict->setAt("ASDK_XREC1", pXrec, xrecObjId);
    pDict->close();

    // Create a resbuf list to add to the xrecord.
    //
    struct resbuf* head;
    ads_point testpt = {1.0, 2.0, 0.0};
    head = acutBuildList(AcDb::kDxfText,
        "This is a test Xrecord list",
        AcDb::kDxfXCoord, testpt,
        AcDb::kDxfReal, 3.14159,
        AcDb::kDxfAngle, 3.14159,
        AcDb::kDxfColor, 1,
        AcDb::kDxfInt16, 180,
        0);

    // Add the data list to the xrecord.  Notice that this
    // member function takes a reference to a resbuf NOT a
    // pointer to a resbuf, so you must dereference the
    // pointer before sending it.
    // 
    pXrec->setFromRbChain(*head);
    pXrec->close();
    acutRelRb(head);
}