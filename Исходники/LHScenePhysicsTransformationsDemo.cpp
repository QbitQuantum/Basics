bool LHScenePhysicsTransformationsDemo::initWithContentOfFile(const std::string& plistLevelFile)
{
    bool retValue = LHSceneDemo::initWithContentOfFile(plistLevelFile);
    
    /*INITIALIZE YOUR CONTENT HERE*/
    /*AT THIS POINT EVERYTHING IS LOADED AND YOU CAN ACCESS YOUR OBJECTS*/
    

    Size size = this->getContentSize();
    
    Label* ttf = Label::create();
    
//#if LH_USE_BOX2D
    ttf->setString("PHYSICS TRANSFORMATIONS DEMO\nLevelHelper API takes care of setting the correct transformations when using physics.\nIt handles transformations in both directions from  Box2d to Cocos2d-X and from Cocos2d-X to Box2d.\nClick on a node to transform it with a random scale and rotation.");
//#else
//    ttf->setString("PHYSICS TRANSFORMATIONS DEMO\nWhen using default Cocos2d-X physics engine (Chipmunk),\nCocos2d-X handles the transformations from the physics engine to its own coordinate system.\nClick on a node to transform it with a random scale and rotation.\nNotice that scaling currently does not work.\nIn Xcode, switch to the Box2d target for complete transformations using the LevelHelper API.");
//#endif
    
#if LH_DEBUG == 0
    ttf->setString("This demo needs debug drawing enabled.\nGo to LHConfig.h and set LH_DEBUG = 1");
#endif
    
    
    ttf->setTextColor(Color4B::BLACK);
    ttf->setHorizontalAlignment(TextHAlignment::CENTER);
    ttf->setPosition(Point(size.width*0.5, size.height*0.5));
    ttf->setSystemFontSize(20);
    this->getUINode()->addChild(ttf);//add the text to the ui element as we dont want it to move with the camera
    
        
    return retValue;
}