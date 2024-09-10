void SearchTeamResultLayer::initLayer()
{
	//±³¾°
	CCSprite* background=CCSprite::create(PVE_FIELD_POPWIN_BACKGROUND);
	this->addChild(background);
	background->setPosition(ccp(480,320));

	CCLabelTTF* lbResult=ToolsFun::createLabel(LanguageManager::shareManager()->getContentByKey("SEARCH_RESULT").c_str(),DEF_FONT_NAME,30,ccp(495,525),this);
	CCLabelTTF* lbTeamID=ToolsFun::createLabel(LanguageManager::shareManager()->getContentByKey("TEAM_ID").c_str(),DEF_FONT_NAME,28,ccp(421,440),this);
	CCLabelTTF* lbTeamName=ToolsFun::createLabel(LanguageManager::shareManager()->getContentByKey("TEAM_NAME").c_str(),DEF_FONT_NAME,28,ccp(421,368),this);
	CCLabelTTF* lbPlayerNum=ToolsFun::createLabel(LanguageManager::shareManager()->getContentByKey("PLAYER_NUM").c_str(),DEF_FONT_NAME,28,ccp(388,297),this);

	m_LbTeamID=ToolsFun::createLabel("111",DEF_FONT_NAME,30,ccp(490,440),this);
	m_LbTeamName=ToolsFun::createLabel("111",DEF_FONT_NAME,30,ccp(490,368),this);
	m_LbPlayerNum=ToolsFun::createLabel("11/11",DEF_FONT_NAME,30,ccp(435,297),this);
	m_LbTeamID->setAnchorPoint(ccp(0.0f,0.5f));
	m_LbTeamName->setAnchorPoint(ccp(0.0f,0.5f));
	m_LbPlayerNum->setAnchorPoint(ccp(0.0f,0.5f));

	createMenu();
	this->setTouchEnabled(true);
}