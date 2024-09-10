//------------------------------------------------------------
// CNsmlObexClient::ReceiveDataL( TDes8& aStartPtr, TRequestStatus &aStatus )
//------------------------------------------------------------
void CNsmlObexClient::ReceiveDataL( TPtr8& aStartPtr, TRequestStatus &aStatus )
    {
	iAgentStatus = &aStatus;
	// agent
	*iAgentStatus = KRequestPending;
	
	iDataPtr.Set( aStartPtr );

    if ( iState != EWaitingToReceive )
        {
        User::Leave( KErrDisconnected );
        }
    else if ( IsActive() ) 
        {
        User::Leave( KErrInUse );
        }
	iDataBuf->Reset();
	iCurrObject->Reset();

	TBuf8<KNameLen> str;
	str.Copy( this->iMimeType->Des() );
	iCurrObject->SetTypeL( str );

	iClient->Get( *iCurrObject, iStatus );
	
	DBG_DUMP((void*)aStartPtr.Ptr(), aStartPtr.Length(), 
	_S8("ReceiveDataL (WBXML)"));
#ifdef __NSML_DEBUG__
	_DBG_FILE("CNsmlObexClient::ReceiveDataL: CWbxml2XmlConverter::ConvertL()\
	 begin");
	CWbxml2XmlConverter* c = CWbxml2XmlConverter::NewLC();
	c->ConvertL(aStartPtr.Ptr(), aStartPtr.Length());
	DBG_DUMP((void*)c->Document().Ptr(), c->Document().Length(), 
	_S8("ReceiveDataL (XML)") );
	CleanupStack::PopAndDestroy(); // c
	_DBG_FILE("CNsmlObexClient::ReceiveDataL: CWbxml2XmlConverter::ConvertL() end");
#endif // __NSML_DEBUG__

	SetActive ();
    }