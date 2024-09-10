LOCAL_C void WaitForServerClose()
	{
	// Wait 10 seconds for server to exit
	TInt count = 10;
	while(count--)
		{
		TFullName name;
		TFindProcess find(KMsvServerPattern);
		if (find.Next(name) != KErrNone)
			return;
		else if (count <= 0)
			{
			RProcess process;
			process.Open(find);
			process.Terminate(KErrGeneral);
			process.Close();
			}
		User::After(1000000);
		}
	}