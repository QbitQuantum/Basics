void MDHeroPrePromoLayer::showTaskInfo()
{
	this->ShowLoadingIndicator("");

	CCHttpRequest *request = new CCHttpRequest();
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this,httpresponse_selector(MDHeroPrePromoLayer::requestFinishedCallback));
	request->setTag("101");

	string _strUrl = CompleteUrl(URL_FRIEND_LIST);
	_strUrl.append(CCUserDefault::sharedUserDefault()->getStringForKey("userinfo"));

	request->setUrl(_strUrl.c_str());

	CCHttpClient *client = CCHttpClient::getInstance();
	client->send(request);

	request->release();
}