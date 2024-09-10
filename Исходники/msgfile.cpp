void MsgFile::init()
{
    if (!m_edit->topLevelWidget()->isActiveWindow() || m_edit->topLevelWidget()->isMinimized())
        return;
    Command cmd;
    cmd->id		= CmdFileName;
    cmd->param	= m_edit;
    Event eWidget(EventCommandWidget, cmd);
    CToolEdit *edtName = (CToolEdit*)(eWidget.process());
    if (edtName){
        if (edtName->text().isEmpty()){
            selectFile();
            return;
        }
        edtName->setFocus();
    }
}