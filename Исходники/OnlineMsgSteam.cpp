/**
 *	Async task is given a chance to trigger it's delegates
 */
void FOnlineAsyncMsgSteam::TriggerDelegates() 
{
	FOnlineAsyncItem::TriggerDelegates();

	AActor* Actor = ActorPtr.Get();
	if (Actor)
	{
		UFunction* Function = (*ResponseMessage)->OwnerFunc.Get();
		if (Function)
		{
			Actor->ProcessEvent(Function, ResponseBuffer);
		}
		else
		{
			UE_LOG_ONLINE(Warning, TEXT("UFunction missing, unable to call RPC response.")); 
		}
	}

	Destroy();
}