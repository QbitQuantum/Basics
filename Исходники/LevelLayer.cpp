bool LevelLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	loadResource();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	m_screenWidth = visibleSize.width;
	m_screenHeight = visibleSize.height;

	//背景图片精灵
	auto bgSprite = Sprite::create("pic/levelSelect.png");
	bgSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bgSprite);

	//返回图片
	auto back = Sprite::create("pic/back.png");
	back->setPosition(40, 40);
	back->setScale(0.5f);
	back->setTag(100);
	this->addChild(back);

	m_successLevel = LevelUtils::readLevelFromFile();

	//显示8个关卡
	std::string imagepath = "";
	for (int i = 0; i < 8; i++) {
		//i小于读到关卡数，说明当前关卡已经通关
		if (i < m_successLevel) {
			imagepath = "pic/level.png";
			//加入卡通关卡数字
			std::string str = StringUtils::format("%d", i + 1);
			auto num = Label::createWithSystemFont(str, "Arial", 40, Size(70, 70), TextHAlignment::CENTER);
			// 一排放4个关卡图标，所以i % 4
			float x = 100 + i % 4 * 300;
			float y = m_screenHeight - 180 - i / 4 * 150;
			num->setPosition(x, y);
			this->addChild(num, 2);
		}
		else {  //加锁的关卡图片
			imagepath = "pic/lock.png";
		}

		auto level = Sprite::create(imagepath);
		// 设置关卡精灵
		level->setTag(i + 1);
		// 设置每一个关卡图片一定的距离
		float x = 100 + i % 4 * 300;
		float y = m_screenHeight - 180 - i / 4 * 150;
		level->setPosition(x, y);
		level->setScale(0.5f);
		this->addChild(level, 1);
	}

	addTouchListener();

	return true;
}