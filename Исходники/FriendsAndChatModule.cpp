	virtual TSharedRef<IFriendsAndChatManager> GetFriendsAndChatManager(FName MCPInstanceName,  bool InGame) override
	{
		if(MCPInstanceName == TEXT(""))
		{
			if (!DefaultManager.IsValid())
			{
				DefaultManager = MakeShareable(new FFriendsAndChatManager());
				DefaultManager->Initialize(InGame);
			}
			return DefaultManager.ToSharedRef();
		}
		else
		{
			TSharedRef<FFriendsAndChatManager>* FoundManager = ManagerMap.Find(MCPInstanceName);
			if(FoundManager != nullptr)
			{
				return *FoundManager;
			}
		}

		TSharedRef<FFriendsAndChatManager> NewManager = MakeShareable(new FFriendsAndChatManager());
		NewManager->Initialize(InGame);
		ManagerMap.Add(MCPInstanceName, NewManager);
		return NewManager;
	}