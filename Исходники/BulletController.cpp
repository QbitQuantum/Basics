void BulletController::onAdd()
{
    ComController::onAdd();

    ComAudio* pSceneAudio = static_cast<ComAudio*>(_owner->getComponent("CCComAudio"));
    if (pSceneAudio)
    {
        pSceneAudio->playEffect("res/sound/pew-pew-lei.wav");
    }
    
    LayerMainGame* pMainGameLyr = dynamic_cast<LayerMainGame*>(_owner->getParent());
    if (pMainGameLyr == nullptr)
    {
        return;
    }
    Vec2 playerPosition = pMainGameLyr->getPlayerSprite()->getPosition();
    Size winSize = Director::getInstance()->getWinSize();
    
    Vec2 touchDir = m_ptTouch-playerPosition;
    
    _owner->setPosition(playerPosition);
    float targetDis = fabs(touchDir.length() * winSize.width / (m_ptTouch.x - playerPosition.x));
    touchDir.normalize();
    Vec2 ptTarget = playerPosition + targetDis*touchDir;
    
    float velocity = 480/1; // 480pixels/1sec
    float realMoveDuration = targetDis/velocity;
    ActionInterval* pMoveAction = MoveTo::create(realMoveDuration, ptTarget);
    _owner->runAction(Sequence::create(pMoveAction, RemoveSelf::create(), nullptr));
}