void HoleModeResult::onRestart(cocos2d::CCObject *sender){
    closeWindow();
    DoVoidEvent(m_restartListener, m_restartSelector);
}