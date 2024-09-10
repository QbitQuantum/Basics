//private
void StartLayer::helpVisible(bool visible)
{
	Sprite *help = (Sprite*)this->getChildByTag((int)ChildTag::HELP);
    Label *helpTitle = (Label*)this->getChildByTag((int)ChildTag::HELP_TITLE);
    Label *helpLab1 = (Label*)this->getChildByTag((int)ChildTag::HELP_LAB1);
    Label *helpLab2 = (Label*)this->getChildByTag((int)ChildTag::HELP_LAB2);
    Label *helpLab3 = (Label*)this->getChildByTag((int)ChildTag::HELP_LAB3);
    Button *helpBtnBack = (Button*)this->getChildByTag((int)ChildTag::HELP_BTN_BACK);
    
	if (visible)
	{
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Fishtales.plist");
        
		if (!help)
		{
			Size winSize = Director::getInstance()->getWinSize();

			help = Sprite::createWithSpriteFrameName("howtoplay.png");
			help->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
			help->setTag((int)ChildTag::HELP);
			this->addChild(help);
		}
        
        //title
        if(!helpTitle)
        {
            helpTitle = Label::createWithSystemFont(this->m_strings["help_title"], GAME_CONFIG_GLOBAL_FONTNAME_02, 36);
            helpTitle->setTag((int)ChildTag::HELP_TITLE);
            helpTitle->setPosition(Vec2(480, 535));
            helpTitle->setTextColor(Color4B(255, 255, 0, 255));
            this->addChild(helpTitle);
        }
        
        //lab1
        if(!helpLab1)
        {
			helpLab1 = Label::createWithSystemFont(this->m_strings["help_lab1"], GAME_CONFIG_GLOBAL_FONTNAME_01, 24);
            helpLab1->setTag((int)ChildTag::HELP_LAB1);
            helpLab1->setPosition(Vec2(480, 385));
            helpLab1->setTextColor(Color4B(255, 255, 255, 255));
            this->addChild(helpLab1);
        }
        
        //lab2
        if(!helpLab2)
        {
			helpLab2 = Label::createWithSystemFont(this->m_strings["help_lab2"], GAME_CONFIG_GLOBAL_FONTNAME_01, 24);
            helpLab2->setTag((int)ChildTag::HELP_LAB2);
            helpLab2->setPosition(Vec2(480, 245));
            helpLab2->setTextColor(Color4B(255, 255, 255, 255));
            this->addChild(helpLab2);
        }
        
        //lab3
        if(!helpLab3)
        {
			helpLab3 = Label::createWithSystemFont(this->m_strings["help_lab3"], GAME_CONFIG_GLOBAL_FONTNAME_01, 24);
            helpLab3->setTag((int)ChildTag::HELP_LAB3);
            helpLab3->setPosition(Vec2(480, 105));
            helpLab3->setTextColor(Color4B(255, 255, 255, 255));
            this->addChild(helpLab3);
        }
        
        if(!helpBtnBack)
        {
            helpBtnBack = Button::create();
            helpBtnBack->loadTextureNormal("btn1_up.png");
            helpBtnBack->loadTexturePressed("btn1_dw.png");
            helpBtnBack->setPosition(Vec2(830, 60));
            helpBtnBack->addTouchEventListener(CC_CALLBACK_2(StartLayer::onButton, this));
            helpBtnBack->setTag((int)ChildTag::HELP_BTN_BACK);
            helpBtnBack->setTitleFontName(GAME_CONFIG_GLOBAL_FONTNAME_01);
            helpBtnBack->setTitleFontSize(32.0f);
			helpBtnBack->setTitleText(this->m_strings["help_btn_back"]);
            this->addChild(helpBtnBack);
        }
        
	}
	else
	{
		if (help)
			help->removeFromParentAndCleanup(true);
        
        if (helpTitle)
			helpTitle->removeFromParentAndCleanup(true);
        
        if (helpLab1)
			helpLab1->removeFromParentAndCleanup(true);
        
        if (helpLab2)
			helpLab2->removeFromParentAndCleanup(true);
        
        if (helpLab3)
			helpLab3->removeFromParentAndCleanup(true);
        
        if (helpBtnBack)
			helpBtnBack->removeFromParentAndCleanup(true);
        
        SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Fishtales.plist");
        Director::getInstance()->getTextureCache()->removeTextureForKey("Fishtales.png");
	}

}