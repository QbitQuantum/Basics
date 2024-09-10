void ZhuangbeiXilianUI::onEnter()
{
	BaseLayer::onEnter();

	CCMenu *menu = CCMenu::create();
	menu->setAnchorPoint(CCPointZero);
	menu->setPosition(CCPointZero);
	addChild(menu);
	m_mMenu = menu;
	/*
	CCMenuItemImage *item = CCMenuItemImage::create("CloseNormal.png","CloseSelected.png",this,SEL_MenuHandler(&MainLayerUI::click));
	menu->addChild(item);
	item->setAnchorPoint(CCPointZero);
	item->setPosition(CCPointZero);
	*/
	{
		int max = 0;
		if (mEquipment->getEquipColor() == ZhuangbeiColour_Xiyou)
		{
			max = 23;
		}
		else if (mEquipment->getEquipColor() == ZhuangbeiColour_Chuanqi)
		{
			max = 50;
		}

		CCLabelTTF *titleTTF = CCLabelTTF::create();
		CCLabelTTF *ttf1 = CCLabelTTF::create(LFStrings::getValue("XilianFanwei").c_str(),fontStr_kaiti, 25.0f);
		ttf1->setColor(ccc3(195,145,96));
		ttf1->setPosition(ccp(ttf1->getContentSize().width / 2, ttf1->getContentSize().height / 2));
		//
		titleTTF->addChild(ttf1);

		CCLabelTTF *ttf2 = CCLabelTTF::create(CCString::createWithFormat(" %s1~%d%s%%",LFStrings::getValue("dakuohaoLeft").c_str(),max,LFStrings::getValue("dakuohaoRight").c_str())->getCString(),fontStr_kaiti, 25.0f);
		ttf2->setColor(ccc3(79,110,217));
		ttf2->setPosition(ccp(ttf2->getContentSize().width / 2 + ttf1->getContentSize().width, ttf2->getContentSize().height / 2));
		//ttf1->setPosition(ccp(this->getContentSize().width / 2,645));
		titleTTF->addChild(ttf2);
		titleTTF->setPosition(ccp(this->getContentSize().width / 2 - ( ttf1->getContentSize().width + ttf2->getContentSize().width ) / 2,655));
		addChild(titleTTF);
	}
	

	
	CCLabelTTF *nameTTF = CCLabelTTF::create(mEquipment->getName().c_str(),fontStr_kaiti, 30.0f);
	nameTTF->setPosition(POS_EqName);

	switch (mEquipment->getEquipColor())
	{
	case ZhuangbeiColour_Xiyou:
		{
			nameTTF->setColor(ccc3(253,180,40));
		}
		break;
	case ZhuangbeiColour_Chuanqi:
		{
			nameTTF->setColor(ccc3(181,93,6));
		}
		break;
	default:
		break;
	}
	
	m_sBackSpr->addChild(nameTTF);

	{
		CCMenuItemImage* closeItem = CCMenuItemImage::create(
			"close.png",
			"close_select.png",
			this,menu_selector(ZhuangbeiXilianUI::cilickClose)    
			);
		CCPoint pos = POS_EqName;
		closeItem->setPosition(ccp(m_sBackSpr->getContentSize().width - closeItem->getContentSize().width,pos.y));
		m_mMenu->addChild(closeItem);
	}
	

	CCSprite *shuomingSpr = CCSprite::create("zhuangbei_xiangxi_xilian_shuoming_1.png");

	shuomingSpr->setPosition(POS_ShuoMing);
	m_sBackSpr->addChild(shuomingSpr);

	bool isFirstIn = false;
	if (!History::getHistory()->getBoolFromCurrentHero(Key_First_LookXilianShuoming,isFirstIn))
	{
		History::getHistory()->putInCurrentHero(Key_First_LookXilianShuoming,false);
		CCPoint pos = shuomingSpr->getParent()->convertToWorldSpace(shuomingSpr->getPosition());
		GuideLayerBase *guideLayer = new GuideLayer_SimpleLayer;
		guideLayer->init(shuomingSpr->getContentSize(), pos
			, LFStrings::getValue("first_chuanqi_shuoming"), NULL, false);
		CCDirector::sharedDirector()->getRunningScene()->addChild(guideLayer, 1024);
	}

	CCMenuItemImage *item = CCMenuItemImage::create("zhuangbei_xiangxi_xilian.png","zhuangbei_xiangxi_xilian_select.png",this,SEL_MenuHandler(&ZhuangbeiXilianUI::clickXilian));
	menu->addChild(item);
	item->setPosition(ccp(POS_ShuoMing.x,50));

	CCMenuItemImage *shuomingItem = CCMenuItemImage::create("xuesejiaotang_anniu_shuoming.png","xuesejiaotang_anniu_shuoming_select.png",this,SEL_MenuHandler(&ZhuangbeiXilianUI::clickShuoming));
	menu->addChild(shuomingItem);
	shuomingItem->setPosition(ccp(shuomingItem->getContentSize().width / 2 + 10,POS_ShuoMing.y));

	vector<ZBAttr> data_list = mEquipment->getEquipData().purify_attr_vec;

	int max_count = CS::getPurifyMaxHoles(mEquipment->getEquipData().zhuangbei_type,mEquipment->getEquipColor(),mEquipment->getLevel());
	int count = data_list.size();

	CCSprite *layer = CCSprite::create("zhuangbei_xiangxi_xilian_shuxing_bg.png");
	layer->setPosition(ccp(POS_EqName.x,465));
	m_sBackSpr->addChild(layer);
	int atter_type_index[5] = {AttrType_baoshang,AttrType_hp_percent,AttrType_skillresult,mEquipment->getMainProType(),0};

	float side = 0;
	{
		CCSprite *bgSpr = CCSprite::create("zhuangbei_xiangxi_xilian_shuxing.png");

		side = (layer->getContentSize().height - bgSpr->getContentSize().height * 5 ) / 10.0f;
	}
	
	m_sShuxingShowSpr = layer;
	for(int i=0; i!= max_count; ++i)
	{
		ZhuangbeiXilianOption *option = ZhuangbeiXilianOption::create();
		option->setCallBack(this,SEL_CallFuncN(&ZhuangbeiXilianUI::clickSelect));
		if (i < count)
		{
			option->setValue(i,CS::getPurifyLevel(data_list[i].attr_value),data_list[i].attr_value,atter_type_index[i]);
			m_uOptionList.push_back(option);
		}
		else
		{
			option->setValue(i,-1,-1,-1);
		}
		layer->addChild(option);
		option->setPosition(ccp(layer->getContentSize().width / 2,layer->getContentSize().height - (i * 2 + 1) * ( side + option->getContentSize().height / 2)));
		
	}
	if (m_uOptionList.size() == 1)
	{
		for (vector<ZhuangbeiXilianOption *>::iterator iter = m_uOptionList.begin() ; iter != m_uOptionList.end() ; iter ++)
		{
			(*iter)->selectSelf();
		}
	}
	m_nTodayFreeCount = MyselfManager::getManager()->getRuntionData()->purify_free_times;
	if (m_nTodayFreeCount <= 0)
	{
		CCSprite *bgSpr = CCSprite::create("daoju_kuang_bg.png");
		bgSpr->setPosition(ccp(this->getContentSize().width / 2 + 2,185));
		m_sBackSpr->addChild(bgSpr);

		CCMenuItemImage *XilianJinghuaItem = CCMenuItemImage::create("daoju_youlanzhiye.png","daoju_youlanzhiye.png",this,SEL_MenuHandler(&ZhuangbeiXilianUI::clickXilianJingHua));
		XilianJinghuaItem->setPosition(ccp(this->getContentSize().width / 2,185));
		m_mMenu->addChild(XilianJinghuaItem);
		/*CCSprite *spr = CCSprite::create("daoju_youlanzhiye.png");
		spr->setPosition(ccp(this->getContentSize().width / 2,185));
		m_sBackSpr->addChild(spr);*/

		int haveCount =  WuPinManager::getManager()->getWuPin(ItemsType_Purify_Scroll)->getCount();
		int count = 1;

		CCLabelTTF *strTTF = CCLabelTTF::create(LFStrings::getValue("XilianJinghua").c_str(),fontStr_kaiti, 20.0f);
		strTTF->setPosition(ccp(bgSpr->getPositionX() - bgSpr->getContentSize().width / 2 + strTTF->getContentSize().width / 2 - 30,115));
		m_sBackSpr->addChild(strTTF);
		strTTF->setColor(ccc3(255,255,255));

		CCLabelTTF *xuTTF = CCLabelTTF::create(CCString::createWithFormat(" %d / ",count)->getCString(),fontStr_kaiti, 20.0f);
		xuTTF->setPosition(ccp(strTTF->getPositionX() + strTTF->getContentSize().width / 2 + xuTTF->getContentSize().width / 2,115));
		m_sBackSpr->addChild(xuTTF);
		xuTTF->setColor(ccc3(255,255,255));

		CCLabelTTF *countTTF = CCLabelTTF::create(CCString::createWithFormat("%d",haveCount)->getCString(),fontStr_kaiti, 20.0f);
		countTTF->setPosition(ccp(xuTTF->getPositionX() + xuTTF->getContentSize().width / 2 + countTTF->getContentSize().width / 2,115));
		m_sBackSpr->addChild(countTTF);
		if (haveCount <= 0)
		{
			countTTF->setColor(ccRED);
		}

		

		m_tXilianJinghuaCountTTF = countTTF; 
	}
	else
	{
		m_tXilianJinghuaTTF = CCLabelTTF::create(LFStrings::getValue("Free").c_str(),fontStr_kaiti, 30.0f);
		m_tXilianJinghuaTTF->setPosition(ccp(POS_EqName.x,172));
		m_sBackSpr->addChild(m_tXilianJinghuaTTF);
		m_tXilianJinghuaTTF->setColor(ccGREEN);
	}
	CCLabelTTF *countTTF = CCLabelTTF::create(CCString::createWithFormat("%s %u",LFStrings::getValue("todayFreeCount").c_str(),m_nTodayFreeCount)->getCString(),fontStr_kaiti, 20.0f);
	countTTF->setPosition(ccp(POS_EqName.x,252));
	m_sBackSpr->addChild(countTTF);
	countTTF->setColor(ccc3(255,255,255));

	m_tFreeCountsTTF = countTTF;

	m_lData_list = data_list;
}