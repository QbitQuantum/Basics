void GuideManager::handleEvent(cocos2d::EventCustom* event)
{
    void* userdata = event->getUserData();
    if (userdata)
    {
        setParent((Node*)userdata);
    }
    
    if (event->getEventName() == GUIDE_EVENT_TOUCH_IN_RECT)
    {
        nextStep(getNextStepId());
    }
    else if (event->getEventName() == GUIDE_EVENT_BEGIN_GUIDE)
    {
        nextStep(0); // test here
    }
    else if (event->getEventName() == GUIDE_EVENT_CONTENUE)
    {
        setWait(false);
        nextStep(getNextStepId());
    }
    else
    {}
}