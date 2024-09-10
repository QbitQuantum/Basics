void CSaveDataBase::WorkFunction()
{
	IComHistIntPtr  pHistory = NULL;
	IMessagesPtr    pMessagesList = NULL;
	/// UnMarshaling ...
	if(SUCCEEDED(hr))
		hr = CoGetInterfaceAndReleaseStream(pHistoryStream,__uuidof(IComHistInt),(LPVOID*)&pHistory);
	if(SUCCEEDED(hr))
		hr = CoGetInterfaceAndReleaseStream(pMessagesStream,__uuidof(IMessages),(LPVOID*)&pMessagesList);
	
	if(SUCCEEDED(hr))
	{
		/// Save To History ...
		bstr_t SID, MID, Body; 
		long   Time, ToId , FromId, RecipientSize; 
		IMessagePtr pMessage;
		IUsersPtr pUserList;
		
		try
		{
			long Size = pMessagesList->GetCount();
			SID = LoadSID;
			
			for(int i=1;i<=Size;i++)
			{
				if(bExit)
				{
					SetEvent(hExitEvent);
					return;
				}
				pMessage = pMessagesList->GetItem(i);
				
				MID  = pMessage->GetMID(); 
				Body = pMessage->GetBody();
				Time = pMessage->Getdate_time(); 
				pUserList = pMessage->GetRecipients();
				RecipientSize = pUserList->GetCount();
				FromId = CUser(pMessage->GetSender()).GetGlobalID();
				
				for(int j=0;j<RecipientSize;j++)
				{
					ToId   = CUser(pUserList->GetItem(j)).GetGlobalID();
					try
					{
						hr = pHistory->AddMessage(FromId,ToId,SID, MID,Time,TRUE,Body,VARIANT_FALSE);
					}
					catch(...)
					{}
				}
			}
		}
		
		catch(...)
		{
			ASSERT(FALSE);
		}
	}

	/// PostMessage About Ok
	if(::IsWindow(hWindow))
		PostMessage(hWindow,dwMessage,(WPARAM)hr,(LPARAM)this);
	else
		delete this;		
	/// End 
	SetEvent(hExitEvent);
}