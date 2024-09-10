	virtual TSharedRef<FFriendViewModel> Create(const TSharedRef<IFriendItem>& FriendItem) override
	{
		TSharedRef<FFriendViewModelImpl> ViewModel = MakeShareable(
			new FFriendViewModelImpl(FriendItem, NavigationService, FriendsAndChatManager.Pin().ToSharedRef()));
		ViewModel->Initialize();
		return ViewModel;
	}