void AskFriendWidget::touchReleaseEvent(CCTouch *pTouch, CCEvent *pEvent)
{
    SoundMgr::getInstance()->playEffect(SoundEnum::BTN_EFFECT_NORMAL);
    if(!m_has){
        CCNode *root = this->getParent();
        while(root->getParent())
            root = root->getParent();
        if(m_addDialog == 0){
            m_addDialog = new AddFriendDialog(root,ccc4(0,0,0,128));
            m_addDialog->setCloseCB(this,callfuncND_selector(AskFriendWidget::onAddFriendCloseClicked));
            m_addDialog->setAddCB(this,callfuncND_selector(AskFriendWidget::onAddFriendAddClicked));
            m_addDialog->exec();
        }
        return;
    }
    UiMsgEv::AskFriendInfo *info = m_serverIface->getAskFriendInfo();
    CCNode *root = this->getParent();
    while(root->getParent())
        root = root->getParent();
    if(m_askDialog != 0){
        m_askDialog->destroy();
        m_askDialog = 0;
    }

    m_askDialog = new AskAsFriendDialog(root,ccc4(0,0,0,128));
    m_askDialog->setCloseCB(this,callfuncND_selector(AskFriendWidget::onAskDialogCloseClicked));
    m_askDialog->setOkCB(this,callfuncND_selector(AskFriendWidget::onAskDialogOkClicked));
    m_askDialog->setRejectCB(this,callfuncND_selector(AskFriendWidget::onAskDialogRejectClicked));
    std::string nick = info->m_friendNick;
    if(nick.empty()){
        mailToNickName(info->m_friendMail,nick);
    }
    std::string *head;
    if(m_serverIface->getHeadPortrait(info->m_friendId,&head)){
        m_askDialog->setAskInfo(info->m_friendId,nick,info->m_askWord,*head);
    }else{
        m_askDialog->setAskInfo(info->m_friendId,nick,info->m_askWord,"");
    }
    m_askDialog->exec();
    if(!m_serverIface->hasUnreadAskFriend()){
        askFriendUpdated();
    }
}