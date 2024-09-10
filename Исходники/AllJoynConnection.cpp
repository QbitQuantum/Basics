bool XferObject::CreateInterfaces()
{
    const char* ifName = XFER_SERVICE_INTERFACE_NAME;
    InterfaceDescription* xferIntf = NULL;
    status = ajConnection->busAttachment->CreateInterface(ifName, xferIntf);
    assert(xferIntf);
    if (ER_OK == status) {
        xferIntf->AddMethod("query", "si",  "i", "filename, filesize, acceptsize ", 0);
        xferIntf->AddMethod("initiate", "ii",  "i", "segmentSize, nSegs, acceptsize ", 0);
        xferIntf->AddMethod("receive", "ayii",  "i", "segment, serialNum. segSize , success ", 0);
        xferIntf->AddMethod("status", "i",  "i", "unused , status ", 0);
        xferIntf->AddMethod("close", "i",  "i", "unused , success ", 0);
        xferIntf->AddMethod("error", "i",  "i", "unused , error ", 0);
        xferIntf->Activate();
    } else {
        NotifyUser(MSG_ERROR, "Failed to create interface \"%s\" (%s)\n", XFER_SERVICE_INTERFACE_NAME, QCC_StatusText(status));
        return false;
    }
    NotifyUser(MSG_SYSTEM, "Create interface \"%s\" (%s)\n", XFER_SERVICE_INTERFACE_NAME, QCC_StatusText(status));
    return true;
}