void
NetGameClient::DoChatMsg(NetMsg* msg)
{
	if (!msg) return;

	NetChatMsg chat_msg;
	chat_msg.Unpack(msg->Data());

	Text name = chat_msg.GetName();
	if (name.length() < 1)
	name = Game::GetText("NetGameClient.chat.unknown");

	HUDView::Message("%s> %s", name.data(), chat_msg.GetText().data());
}