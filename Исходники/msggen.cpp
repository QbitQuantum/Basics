bool MsgGen::processEvent(Event *e)
{
    if (e->type() == eEventCheckCommandState){
        EventCheckCommandState *ecs = static_cast<EventCheckCommandState*>(e);
        CommandDef *cmd = ecs->cmd();
        if (cmd->param == m_edit){
            unsigned id = cmd->bar_grp;
            if ((id >= MIN_INPUT_BAR_ID) && (id < MAX_INPUT_BAR_ID)){
                cmd->flags |= BTN_HIDE;
                return true;
            }
            switch (cmd->id){
            case CmdTranslit:
            case CmdSmile:
            case CmdSend:
            case CmdSendClose:
                e->process(this);
                cmd->flags &= ~BTN_HIDE;
                return true;
            case CmdNextMessage:
            case CmdMsgAnswer:
                e->process(this);
                cmd->flags |= BTN_HIDE;
                return true;
            }
        }
    } else
    if (e->type() == eEventCommandExec){
        EventCommandExec *ece = static_cast<EventCommandExec*>(e);
        CommandDef *cmd = ece->cmd();
        if ((cmd->id == CmdSend) && (cmd->param == m_edit)){
            QString msgText = m_edit->m_edit->text();
            if (!msgText.isEmpty()){
                log(L_DEBUG, "Send: %s", msgText.local8Bit().data());
                Message *msg = new Message;
                msg->setText(msgText);
                msg->setContact(m_edit->m_userWnd->id());
                msg->setClient(m_client);
                msg->setFlags(MESSAGE_RICHTEXT);
                msg->setForeground(m_edit->m_edit->foreground().rgb() & 0xFFFFFF);
                msg->setBackground(m_edit->m_edit->background().rgb() & 0xFFFFFF);
                msg->setFont(CorePlugin::m_plugin->getEditFont());
                m_edit->sendMessage(msg);
            }
            return true;
        }
    }
    return false;
}