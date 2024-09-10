void HttpRequestTest::requestHttpInfo(CAControl* btn, CCPoint point)
{
	loading = CAView::createWithColor(ccc4(255, 255, 255, 0));
	loading->setTag(200);
	loading->setFrame(this->getView()->getBounds());
	this->getView()->addSubview(loading);

	loadImage = CAImageView::createWithImage(CAImage::create("loading.png"));
	loadImage->setCenterOrigin(CADipPoint(size.width*0.5, size.height*0.5));
	loadImage->setScale(0.5);
	loading->addSubview(loadImage);
	CAScheduler::schedule(schedule_selector(HttpRequestTest::loadingAnim), this, 0.01, false);

	CALabel* msg = CALabel::createWithCenter(CADipRect(size.width*0.5, size.height*0.5, loadImage->getFrame().size.width*0.9, 50));
	msg->setText("Loading");
	msg->setColor(CAColor_blueStyle);
	msg->setFontSize(_px(22));
	msg->setTextAlignment(CATextAlignmentCenter);
	msg->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
	loading->addSubview(msg);

	string url = "";
	if (inputWebsite->getText().find("http://")==string::npos)
	{
		url = "http://" + inputWebsite->getText();
	}
	else
	{
		url = inputWebsite->getText();
	}
	CCHttpRequest* request = new CCHttpRequest();
	request->setTag("Getpage");
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setUrl(url.c_str());
	request->setResponseCallback(this,httpresponse_selector(HttpRequestTest::requestResult));
	CCHttpClient* httpClient = CCHttpClient::getInstance();
	httpClient->setTimeoutForConnect(30);
	httpClient->send(request); 
	request->release();
}