void AddFriendScene::addFriendRequest(std::string &targetUser)
{
	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,httpresponse_selector(AddFriendScene::requestFinishedCallback));
	request->setTag("102");
    
	string _strUrl = CompleteUrl(URL_FRIEND_ADD_NEW);
	_strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));
	_strUrl.append("/" + targetUser);

	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);
    
	request->release();
}