void SGShowAllLayer::initView()
{
    ResourceManager::sharedInstance()->bindTexture("sgstrenglayer/sgstrenglayer.plist", RES_TYPE_LAYER_UI, sg_showAllLayer, LIM_PNG_AS_PNG);
    ResourceManager::sharedInstance()->bindTexture("sgmainlayer/sgmainlayer.plist", RES_TYPE_LAYER_UI, sg_showAllLayer, LIM_PNG_AS_PNG);
    ResourceManager::sharedInstance()->bindTexture("sgembattlelayer/sgembattlelayer.plist", RES_TYPE_LAYER_UI, sg_showAllLayer, LIM_PNG_AS_PNG);

    float h = SGMainManager::shareMain()->getHeadHeight();
    float b = SGMainManager::shareMain()->getBottomHeight();
    CCSize s= CCDirector::sharedDirector()->getWinSize();
        
    CCSprite *titleBg = CCSprite::createWithSpriteFrameName("barrack_title_bg.png");
    this->addChild(titleBg);
    titleBg->setAnchorPoint(ccp(0.5, 1));
    titleBg->setPosition(ccpAdd(SGLayout::getPoint(kUpCenter), ccp(0, - h )));
    
    SGButton *backBtn = SGButton::create("redbtn_jiao.png",
                                         "public_font_back.png",
                                         this,
                                         menu_selector(SGShowAllLayer::backHandler),
                                         ccp(-18, 0),
                                         false,
                                         true);
    this->addBtn(backBtn);
    backBtn->setAnchorPoint(ccp(0, 0.5));
    backBtn->setPosition(ccp(0, titleBg->getPosition().y-titleBg->getContentSize().height/2));
    
    SGButton *sortBtn = SGButton::create("redbtn_jiao.png",
                                         "public_range.png",
                                         this,
                                         menu_selector(SGShowAllLayer::sortHandler),
                                         ccp(18, 0),
                                         true,
                                         true);
    this->addBtn(sortBtn);
    sortBtn->setAnchorPoint(ccp(1, 1));
    sortBtn->setPosition(ccpAdd(SGLayout::getPoint(kBottomRight),ccp(0, titleBg->getPosition().y)));
    
    CCSprite *font2 = CCSprite::createWithSpriteFrameName("font_szwjscsx.png");
    font2->setPosition(ccp(s.width/2, titleBg->getPosition().y - titleBg->getContentSize().height/2));
    this->addChild(font2);
    
    scrollView = SNSScrollView::create(CCRectMake(0, 280, s.width, s.height - h - b  - titleBg->getContentSize().height-10));
    scrollView->setPosition(ccpAdd(SGLayout::getPoint(kBottomLeft), ccp(0, b)));
    this->addChild(scrollView);
    scrollView->setHorizontal(false);
    scrollView->setVertical(true);
    
//    CCArray *cards = SGPlayerInfo::sharePlayerInfo()->getShowOfficerCards();
    int id = SGTeamgroup::shareTeamgroupInfo()->getiscurrent();
    CCArray *cards = SGTeamgroup::shareTeamgroupInfo()->getEmbattleOfficers(id);
    int bagSize = SGPlayerInfo::sharePlayerInfo()->getPlayerBagSize();
    CCLOG("bagSize:%d",bagSize);
    bagSize = 52;
    float row = (float)bagSize/5;
    int allrow = ceilf(row);
    float itemWidth = 0;
    float itemHeight = 0;
    
    for (int i = 0; i<bagSize; i++)
    {
        SGOfficerCard *card = NULL;
        SGEmbattleItem *item = NULL;
        if (i<cards->count())
        {
            card = (SGOfficerCard *)cards->objectAtIndex(i);
            
        }
        if (card)
        {
            item = SGEmbattleItem::create(this, card,SGTeamgroup::shareTeamgroupInfo()->getiscurrent());
        }
        else
        {
            item = SGEmbattleItem::create(this,(i+1),SGTeamgroup::shareTeamgroupInfo()->getiscurrent());
        }
        
        cardArray->addObject(item);
        scrollView->m_body->addChild(item);
        itemWidth = item->getWidth();
        itemHeight = item->getHeight();
        
        CCSize s = CCDirector::sharedDirector()->getWinSize();
        float wid = s.width - itemWidth*5 ;
        item->setPosition(ccp(i%5*(itemWidth + 20)+10 + wid/2, (item->getHeight() + 20)*allrow - item->getHeight() * .5 - (i/5) * (itemHeight + 20)));
    }
    
    scrollView->setBodySize(CCSizeMake((itemWidth + 20) *5 , (itemHeight + 20)*allrow));
    
    scrollviewRect = CCRectMake(0, b, s.width, s.height - h - b - titleBg->getContentSize().height-10);
    
}