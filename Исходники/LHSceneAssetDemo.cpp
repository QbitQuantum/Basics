bool LHSceneAssetDemo::initWithContentOfFile(const std::string& plistLevelFile)
{
    bool retValue = LHSceneDemo::initWithContentOfFile(plistLevelFile);
    
    /*INITIALIZE YOUR CONTENT HERE*/
    /*AT THIS POINT EVERYTHING IS LOADED AND YOU CAN ACCESS YOUR OBJECTS*/
    
    Size size = this->getContentSize();
    
    Label* ttf = Label::create();
    
    
//#if LH_USE_BOX2D
    ttf->setString("ASSETS DEMO\nAssets are special objects that when edited they will change\nto the new edited state everywhere they are used in your project.\nClick to create a new officer (asset) of a random scale and rotation.");
//#else
//    ttf->setString("ASSETS DEMO\nAssets are special objects that when edited they will change\nto the new edited state everywhere they are used in your project.\nClick to create a new officer (asset) of a random scale and rotation.\nChipmunk detected:\nSorry but currently Cocos2d-X has a bug where it does not update children physics body position.\nWhen using Chipmunk and having physics bodies\non children of the node that gets transformed the bodies will not get updated.\nSwitch to the Box2d target for correct physics transformations.\nCheck LHSceneAssetDemo source code for a possible work around.");
//#endif

    
    
    ttf->setTextColor(Color4B::BLACK);
    ttf->setHorizontalAlignment(TextHAlignment::CENTER);
    ttf->setPosition(Point(size.width*0.5, size.height*0.5));
    ttf->setSystemFontSize(20);
    this->getUINode()->addChild(ttf);//add the text to the ui element as we dont want it to move with the camera
    
        
    return retValue;
}