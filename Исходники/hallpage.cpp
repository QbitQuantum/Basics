void HallPage::onSendMsgClicked()
{
    if(m_sendMsgDialog != 0){
        m_sendMsgDialog->destroy();
        m_sendMsgDialog = 0;
    }
    CCNode *root = this->getParent();
    while(root->getParent())
        root = root->getParent();
    if(m_sendMsgDialog == 0){
        m_sendMsgDialog = new SendMsgDialog(root,ccc4(0,0,0,128));
        m_sendMsgDialog->setCloseCB(this,callfuncND_selector(HallPage::onSendMsgCloseClicked));
        m_sendMsgDialog->setSendCB(this,callfuncND_selector(HallPage::onSendMsgSendClicked));
        m_sendMsgDialog->setInitShowPage(true);
        m_sendMsgDialog->setInitPage(true,false);
        std::string name = m_headNick;
        if(name.empty())
            mailToNickName(m_headMail,name);
        m_sendMsgDialog->setRecInfo(m_headId,name,"");
        m_sendMsgDialog->exec();
    }
}