void GameEndBuy::onCloseClicked(CCObject* sender){
    DoVoidEvent(m_lose_listener, m_lose_selector);
    closeWindow();
}