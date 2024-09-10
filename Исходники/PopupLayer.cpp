void PopupLayer::buttonCallback(cocos2d::CCObject *pSender){
    CCNode* node = dynamic_cast<CCNode*>(pSender);
	int tag = node->getTag();
	//quit
	if(tag == 40)
	{
		#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
			MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
			return;
		#endif

			Director::getInstance()->end();

		#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			exit(0);
		#endif
	}
	//resume
	else if (tag == 41)
	{
		node->getParent()->getParent()->getParent()->resume();
	}
	//restart
	else if(tag == 42)
	{
		GameMain::score = 0;
		GameMain::gravity = 0;
		ui::TextAtlas* score_lbl = (ui::TextAtlas*)(node->getParent()->getParent()->getParent()->getChildByTag(1)->getChildByTag(5)->getChildByTag(2));
		String* s = String::createWithFormat("%d", GameMain::score*5);
		score_lbl->setStringValue(s->getCString());
		ui::LoadingBar* score_bar = (ui::LoadingBar* )(node->getParent()->getParent()->getParent()->getChildByTag(1)->getChildByTag(5)->getChildByTag(1));
		score_bar->setPercent(GameMain::score*5);
		node->getParent()->getParent()->getParent()->resume();
	}
	//next
	else if (tag == 43)
	{
		GameMain::score = 0;
		GameMain::gravity = 0;
		ui::TextAtlas* score_lbl = (ui::TextAtlas*)(node->getParent()->getParent()->getParent()->getChildByTag(1)->getChildByTag(5)->getChildByTag(2));
		String* s = String::createWithFormat("%d", GameMain::score*5);
		score_lbl->setStringValue(s->getCString());
		GameMain::page+=2;
		ui::LoadingBar* score_bar = (ui::LoadingBar* )(node->getParent()->getParent()->getParent()->getChildByTag(1)->getChildByTag(5)->getChildByTag(1));
		score_bar->setPercent(GameMain::score*5);
		node->getParent()->getParent()->getParent()->resume();
	}
    this->removeFromParent();
}