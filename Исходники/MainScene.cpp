bool MainScene::init() {
	if (!Layer::init())
		return false;

	auto director = Director::getInstance();
	auto pView = director->getOpenGLView();
	pView->setDesignResolutionSize(RESOLUTION_WIDTH, RESOLUTION_HEIGHT, ResolutionPolicy::SHOW_ALL);

	Size visibleSize = director->getVisibleSize();
	Vec2 origin = director->getVisibleOrigin();

	//Title 'Kid Sudoku'
	auto labelTitle = Label::createWithTTF("Kid Remember It", "fonts/Marker Felt.ttf", 188);
	labelTitle->setTextColor(Color4B(0xe3, 0x54, 0xf4, 0xff));
	labelTitle->setPosition(Vec2(origin.x + visibleSize.width / 2,
						 	origin.y + visibleSize.height - labelTitle->getContentSize().height/2 - 40)
						);
	this->addChild(labelTitle);

	//Cool Papa-Legend announcement
	auto labelAnn = Label::createWithTTF("Cool Papa-Legend :   Produce product for our kids.", "fonts/Marker Felt.ttf", 30);
	labelAnn->setTextColor(Color4B(0x00, 0xff, 0x00, 0xff));
	labelAnn->setPosition(Vec2(origin.x + visibleSize.width / 2,
						 	labelTitle->getPosition().y - labelTitle->getContentSize().height/2 - 60 - labelAnn->getContentSize().height / 2)
						);
	this->addChild(labelAnn);

	//Campaign Button
	auto btnPlay = ui::Button::create("btn-menu-0.png",
											  "btn-menu-1.png",
											  "btn-menu-2.png");
	btnPlay->setScale9Enabled(true);
	btnPlay->setCapInsets(Rect(15, 15, 4, 4));
	btnPlay->setTitleText("Play");
	btnPlay->setTitleFontSize(40);
	btnPlay->setContentSize(Size(300, 90));
	btnPlay->setPosition(Vec2(origin.x + visibleSize.width / 2,
			 	 	 	   	 	  labelAnn->getPosition().y - labelAnn->getContentSize().height / 2 - 140 - btnPlay->getContentSize().height/2)
							);
	btnPlay->addClickEventListener(CC_CALLBACK_1(MainScene::onMenuPlayClicked, this));
	this->addChild(btnPlay, 1);

	//Exit Button
	auto btnExit = ui::Button::create("btn-menu-0.png",
											  "btn-menu-1.png",
											  "btn-menu-2.png");
	btnExit->setScale9Enabled(true);
	btnExit->setCapInsets(Rect(15, 15, 4, 4));
	btnExit->setTitleText("Exit");
	btnExit->setTitleFontSize(40);
	btnExit->setContentSize(Size(300, 90));
	btnExit->setPosition(Vec2(origin.x + visibleSize.width / 2,
							btnPlay->getPosition().y - btnPlay->getContentSize().height / 2 - 40 - btnExit->getContentSize().height/2)
							);
	btnExit->addClickEventListener(CC_CALLBACK_1(MainScene::onMenuExitClicked, this));
	this->addChild(btnExit, 1);
	return true;
}