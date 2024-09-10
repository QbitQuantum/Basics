	virtual TSharedRef<FFriendsChatMarkupService> Create() override
	{
		TSharedRef<FFriendsChatMarkupServiceImpl> Service = MakeShareable(
			new FFriendsChatMarkupServiceImpl(CommunicationService, NavigationService,FriendsListFactory));
		Service->Initialize();
		return Service;
	}