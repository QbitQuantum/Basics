//////////////////
// Shutdown the news menu
void Menu_Net_ChatShutdown()
{
	cChatGuiInitialized = false;
	cChat.Shutdown();
}