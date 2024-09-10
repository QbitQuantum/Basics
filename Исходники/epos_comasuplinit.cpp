// -----------------------------------------------------------------------------
// COMASuplInit::CloneNotification()
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void COMASuplInit::CloneNotificationL(const COMASuplInit* aSuplInit)
{
    TInt error = KErrNone;

    delete iNotification;
    iNotification = NULL;
    iNotification = COMASuplNotification::NewL();

    COMASuplNotification::TOMASuplEncodingType encodeType;

    COMASuplNotification* cloneNotification = NULL;
    aSuplInit->Notification(cloneNotification);


    COMASuplNotification::TOMASuplNotificationType notifyType = cloneNotification->SuplNotification();
    iNotification->SetSuplNotification(notifyType);

    error = cloneNotification->EncodingType(encodeType);
    if(!error)
    {
        iNotification->SetEncodingType(encodeType);
    }

    COMASuplNotification::TOMASuplFormatIndicator formatIndicator;
    HBufC8* cloneName = NULL;
    error = cloneNotification->ClientName(cloneName,formatIndicator);
    if(!error)
    {
        HBufC8* name = HBufC8::NewL(cloneName->Length());
        *name = *cloneName;
        iNotification->SetClientName(name,formatIndicator);
    }

    HBufC8* cloneRequestor = NULL;
    error = cloneNotification->RequestorId(cloneRequestor,formatIndicator);
    if(!error)
    {
        HBufC8* requestor = HBufC8::NewL(cloneRequestor->Length());
        *requestor = *cloneRequestor;
        iNotification->SetRequestorId(requestor,formatIndicator);
    }
}