bool Victory::init()
{
    // init the super
    if ( !LayerColor::initWithColor(Color4B(205, 203, 166, 120))) {
        
        return false;
    }
    
    Size parentVisibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // this->setVisible(false);
    
    dialog = Sprite::create("Graphics/levelComplete.png");
    if (!dialog) {
        printf("Error opening levelComplete.png\n");
        return false;
    }
    
    Size rawSize = dialog->getBoundingBox().size;
    
    dialog->setAnchorPoint(Vec2(0,0));
    createMenu();
    
    dialog->setScale((rawSize.width/parentVisibleSize.width)*0.66);
    
    Size dialogSize = dialog->getBoundingBox().size;
    
    posX = (parentVisibleSize.width-dialogSize.width)/2.0;
    posY = (parentVisibleSize.height-dialogSize.height)/2.0;
    
    auto move = MoveTo::create(1.0, Vec2(posX, posY));
    auto bounceIn = EaseElasticOut::create(move->clone());
    dialog->setPosition(Vec2(posX, -dialogSize.height));
    
    
    // is there any way to fade this in nicely?
    // How do we scale to fit the phone size?
    this->addChild(dialog, 1);
    dialog->runAction(bounceIn);
    return true;
}