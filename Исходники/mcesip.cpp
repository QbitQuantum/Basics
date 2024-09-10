// -----------------------------------------------------------------------------
// MceSip::ToSIPExtensionHeadersL
// -----------------------------------------------------------------------------
//
void MceSip::ToSIPExtensionHeadersL( RPointerArray<CSIPHeaderBase>& aSIPHeaders, 
                                     const MDesC8Array& aHeaders )
    {
    
	for ( int i = 0; i < aHeaders.MdcaCount(); i++ )
		{
		TPtrC8 param = aHeaders.MdcaPoint( i );
		TInt index = param.Locate( KMceSipSeparator );
		if ( index != KErrNotFound && 
					param.Left( index ) != KMceSipSubscriptionStateHeader )
			{
    		CSIPExtensionHeader* extHeader = CSIPExtensionHeader::NewL( 
    		                param.Left(index), 
    			            param.Right( param.Length() - ( index + 1 ) ) );
    		CleanupStack::PushL( extHeader );
    		User::LeaveIfError( aSIPHeaders.Append( extHeader ) );
    		CleanupStack::Pop( extHeader );
			}
		}
    }