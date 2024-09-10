///////////////////////////////////////////////////////////////////////////////
//
// Private methods
//
///////////////////////////////////////////////////////////////////////////////
HBufC8* CIkev1Dialog::CreateDialogInput(TIPSecDialogInfo& aDialogInfo, TBool aUserNameCache)
{
	//
	// Create dialog input data buffer. Concatenate cached user name
	// string into input data if requested and if cached name exists
	//
	HBufC8* DialogInput;
	HBufC8* UserName = NULL;
	TInt    UserNameLth = 0;	
	TPckgBuf<TIPSecDialogInfo> infoBuf(aDialogInfo);
	
	if ( aUserNameCache ) {
	   UserName = GetUserNameFromFile();
	   if ( UserName )
		  UserNameLth = UserName->Length();
	}

	DialogInput = HBufC8::New(sizeof(TIPSecDialogInfo) + UserNameLth);
	if ( DialogInput ) {
	   DialogInput->Des().Copy(infoBuf);
	   if ( UserName ) {
	      DialogInput->Des().Append(UserName->Des());
		  delete UserName;
	   }	  
	}   

	return DialogInput;
}   