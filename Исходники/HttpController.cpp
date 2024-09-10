void CHttpController::ProcessResponseBodyDataL( RHTTPTransaction& aTransaction )
	{
	MHTTPDataSupplier* body = aTransaction.Response().Body();

	TPtrC8 dataPart;
	body->GetNextDataPart( dataPart );

	if ( iOutputStream )
		{
		iOutputStream->WriteL( dataPart );
		}
	else
		{
		TInt bufLength( iResponseData->Des().Length() );
		TInt maxBufLength( iResponseData->Des().MaxLength() );
		if ( bufLength + dataPart.Length() > maxBufLength )
			{
			iResponseData = iResponseData->ReAllocL( bufLength + dataPart.Length() );
			}
		iResponseData->Des().Append( dataPart );
		}
	body->ReleaseData();
	StartTimeout();
	}