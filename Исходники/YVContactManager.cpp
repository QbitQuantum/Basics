bool YVContactManager::addFriend(uint32 uid, std::string greet)
{
	YVPlatform* platform = YVPlatform::getSingletonPtr();
	YVMsgDispatcher* msgDispatcher = platform->getMsgDispatcher();

	if (platform->getLoginUserInfo()->userid == uid)
	{
		return false;
	}

	AddFriendRequest r;
	r.userid = uid;
	r.greet = greet;
	return msgDispatcher->send(&r);
}