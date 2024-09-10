XQAccessPoint XQAccessPointManagerPrivate::accessPointByIdL(unsigned long int id) const
{
    XQAccessPoint ap;

    CApDataHandler* pDataHandler = CApDataHandler::NewLC(*ipCommsDB); 
    
    CApAccessPointItem* pAPItem = CApAccessPointItem::NewLC(); 
    pDataHandler->AccessPointDataL(id,*pAPItem);
    TBuf<KCommsDbSvrMaxColumnNameLength> name;
    pAPItem->ReadTextL(EApIapName, name);
    const HBufC* pGprsName = pAPItem->ReadConstLongTextL(EApGprsAccessPointName);

    ap = XQAccessPoint(QString::fromUtf16(name.Ptr(),name.Length()),id);
    ap.setGprsName(QString::fromUtf16(pGprsName->Ptr(),pGprsName->Length()));
    
    switch (pAPItem->BearerTypeL()) {
        case EApBearerTypeCSD:      
            ap.setModemBearer(XQAccessPoint::ModemBearerCSD);
            break;
        case EApBearerTypeGPRS:
            ap.setModemBearer(XQAccessPoint::ModemBearerGPRS);
            break;
        case EApBearerTypeHSCSD:
            ap.setModemBearer(XQAccessPoint::ModemBearerHSCSD);
            break;
        case EApBearerTypeCDMA:
            ap.setModemBearer(XQAccessPoint::ModemBearerCDMA);
            break;
        case EApBearerTypeWLAN:
            ap.setModemBearer(XQAccessPoint::ModemBearerWLAN);
            break;
        case EApBearerTypeLAN:
            ap.setModemBearer(XQAccessPoint::ModemBearerLAN);
            break;
        case EApBearerTypeLANModem:
            ap.setModemBearer(XQAccessPoint::ModemBearerLANModem);
            break;
        default: ap.setModemBearer(XQAccessPoint::ModemBearerUnknown);
    }        
    
    CleanupStack::PopAndDestroy(pAPItem);
    CleanupStack::PopAndDestroy(pDataHandler);
    
    return ap;
}