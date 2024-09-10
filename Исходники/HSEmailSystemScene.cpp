void HSEmailSystemLayer::Load()
{
    CCSprite* pBackground = HSCCSprite::create("Image/BEIJING.png");
	pBackground->setPosition(HSBase::GetTemplateScreenCentre());
	this->addChild(pBackground);
	HSTool::SetNodeFilldScreen(pBackground);
    
	HSReadUI::ShareReadUI()->ReadUI("Image/EmailSystem.data","Image/",this);

	CCSprite* pMoneyFrame = HS_FIND_UI_PANEL_SPRITE("UI_Jinbidiandikuang","Jinbidiandikuang");
	CCTexture2D* pMoneyTexture = CCTextureCache::sharedTextureCache()->addImage("Image/moneyNumber.png");
	m_pMoney =  CCLabelAtlas::create("0","Image/moneyNumber.png",pMoneyTexture->getPixelsWide() / 11,pMoneyTexture->getPixelsHigh(),'0');
	m_pMoney->setAnchorPoint(HS_ANCHOR_CENTER);
	m_pMoney->setPosition(HS_SizeHalf_Point(pMoneyFrame->getContentSize()));
	pMoneyFrame->addChild(m_pMoney);


	CCSprite* pEmailSystemFrame = HS_FIND_UI_PANEL_SPRITE("UI_FriendFrame","gerenxinxilanfanwei");
	m_pEmailListView = HSEmailListVeiw::create(pEmailSystemFrame->getContentSize(),CCSizeMake(505,100),HS_GAME_CACHE()->m_EmailResponse.emaillist_size());
	CCPoint pos = CCPointZero;
	pos.x = -pEmailSystemFrame->getContentSize().width / 2.f - 15.f;

	pos.y = pEmailSystemFrame->getPosition().y - pEmailSystemFrame->getContentSize().height / 2.f - 20.f;
	m_pEmailListView->setPosition(pos);
	pEmailSystemFrame->getParent()->addChild(m_pEmailListView,1000);
	m_pEmailListView->reloadData();

	HS_SET_MENU_TARGET("UI_fh_01",this,HSEmailSystemLayer::Call_Back);

	HS_SET_MENU_TARGET("UI_Goumaijinbianniu_01",this,HSEmailSystemLayer::Call_Shop);
    
    if (HS_GAME_CACHE()->m_EmailResponse.emaillist_size() == 0)
    {
        CCMenu* pMenu = HS_FIND_UI_MENU("UI_quanbulingqu");
        pMenu->setVisible(false);
    }else{
        HS_SET_MENU_TARGET("UI_quanbulingqu",this,HSEmailSystemLayer::Call_AllRevc);
    }
    

	this->schedule(schedule_selector(HSEmailSystemLayer::Updata));
}