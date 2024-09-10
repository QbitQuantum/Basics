TSharedRef< FChatDisplayService > FChatDisplayServiceFactory::Create(const TSharedRef<IChatCommunicationService>& ChatService, bool FadeChatList, bool FadeChatEntry, float ListFadeTime, float EntryFadeTime)
{
	TSharedRef< FChatDisplayServiceImpl > DisplayService = MakeShareable(new FChatDisplayServiceImpl(ChatService, FadeChatList, FadeChatEntry, ListFadeTime, EntryFadeTime));
	DisplayService->Initialize();
	return DisplayService;
}