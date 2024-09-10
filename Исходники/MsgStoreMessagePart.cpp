/** list all the child part to this part 
    /note This method leaves with KErrNotSupported if it is NOT multi-part.
*/
EXPORT_C void CMsgStoreMessagePart::ChildPartsL( RPointerArray<CMsgStoreMessagePart>& aParts )
{
	
	TPartsArray partsArray( iContext, iMailBoxId, aParts );
	
	iContext.iSession.ChildrenPropertiesL( iId,               // aId
	                                       iParentId,         // aParentId
	                                       EMsgStorePartBits, // aContainerType
	                                       EFalse,            // aQuickProperties
	                                       EFalse,            // aRecursive	                                        	                                        
	                                       partsArray );	
	
	// make sure body come before attachments
	TInt count = aParts.Count(); 
	if ( count > 1 )
		{
		for ( TInt i = 0 ; i < count; i++ )
			{
			CMsgStoreMessagePart* part = aParts[i];
			TUint index = 0;
			if ( part->FindProperty( KMsgStorePropertyContentType, index ) )
				{
				const TDesC& contentType = part->PropertyValueDesL( index );
				if ( contentType == KFSMailContentTypeMultipartAlternative )
					{
						if( i > 0 )  
							{
							//body is not the first child, move it to the first place
							aParts.Remove(i);
							aParts.InsertL( part, 0 );
							}
						break;
					}
				}
			}
		}
}