void ShowEditbox(const char* aTitleUtf8, const char* aTextUtf8, SsdKeyboardCallback callback, void *context, TEditBoxType aBoxType )
{
  kbd_callback = callback;
  kbd_context = context;
  if ( pAddNoteDialog == NULL )
  {
    TBuf<128> enterText;
    TBuf<128> title;
    TPtrC8 ptr( ( const TUint8* ) aTitleUtf8, User::StringLength( ( const TUint8* ) aTitleUtf8 ) );
    CnvUtfConverter::ConvertToUnicodeFromUtf8( title, ptr );
    
    ptr.Set( (const TUint8* ) aTextUtf8, User::StringLength( ( const TUint8* ) aTextUtf8 ) );
    CnvUtfConverter::ConvertToUnicodeFromUtf8( enterText, ptr );
    
    pAddNoteDialog = CRoadMapQueryDialog::NewL( enterText, CAknQueryDialog::ENoTone );
    

    if ( aBoxType == EEditBoxPassword )
	{
		// For password use the secured edit box
		pAddNoteDialog->PrepareLC( R_ADD_NOTE_QUERY );
	}
    else
	{
    	pAddNoteDialog->PrepareLC( R_ADD_NOTE_QUERY );
    	pAddNoteDialog->SetPredictiveTextInputPermitted(ETrue);
	}
    // Set prompt 
    pAddNoteDialog->SetPromptL(title);
    // Set the soft left key visible (in case of empty string ) 
    // 				for all types except the EEditBoxEmptyForbidden  
    pAddNoteDialog->SetLeftSoftKeyVisible( !( aBoxType == EEditBoxEmptyForbidden ) );
    
    TInt answer = pAddNoteDialog->RunLD();
    if(answer == EEikBidOk) 
    {
      int bits = (enterText.Length()+1)* 4;
      unsigned char* textBuf = (unsigned char*)calloc(bits+1,1);
      TPtr8 textBufPtr(textBuf, bits);
      CnvUtfConverter::ConvertFromUnicodeToUtf8(textBufPtr, enterText);
      kbd_callback(SSD_KEYBOARD_OK, (const char*) textBuf, kbd_context);
      free(textBuf);
    }
    else
    {
      //Do nothing
    }
    pAddNoteDialog = NULL;
  }
}