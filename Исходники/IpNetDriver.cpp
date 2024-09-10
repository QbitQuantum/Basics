bool UIpNetDriver::HandleSocketsCommand( const TCHAR* Cmd, FOutputDevice& Ar, UWorld* InWorld )
{
	Ar.Logf(TEXT(""));
	if (Socket != NULL)
	{
		TSharedRef<FInternetAddr> LocalAddr = GetSocketSubsystem()->CreateInternetAddr();
		Socket->GetAddress(*LocalAddr);
		Ar.Logf(TEXT("%s Socket: %s"), *GetDescription(), *LocalAddr->ToString(true));
	}		
	else
	{
		Ar.Logf(TEXT("%s Socket: null"), *GetDescription());
	}
	return UNetDriver::Exec( InWorld, TEXT("SOCKETS"),Ar);
}