bool YVChannalChatManager::getChannalHistoryData(int channelKeyId, int index)
{
	YVPlatform* platform = YVPlatform::getSingletonPtr();

	//获取一屏的数量历史消息的数量// 
	uint32  count = platform->channelHistoryChatNum;
	m_historyCache->clear();
	m_historyCache->setMaxNum(count);

	ChannelHistoryRequest q;
	q.count = 0 - count;
	q.index = index;
	q.wildCard.append(getChannelKeyById(channelKeyId));

	YVMsgDispatcher*  msgDispatcher = YVPlatform::getSingletonPtr()->getMsgDispatcher();
	return msgDispatcher->send(&q);
}