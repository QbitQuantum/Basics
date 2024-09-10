bool ChatHandler::HandleGOActivate(const char* args, WorldSession *m_session)
{
    GameObject* GObj = NULLGOB;

    GObj = m_session->GetPlayer()->m_GM_SelectedGO;
    if( !GObj )
    {
        RedSystemMessage(m_session, "No selected GameObject...");
        return true;
    }

    if(GObj->GetState() == 1)
    {
        // Close/Deactivate
        GObj->SetState(0);
        GObj->SetFlags(GObj->GetFlags()-1);
    }
    else
    {
        // Open/Activate
        GObj->SetState(1);
        GObj->SetFlags(GObj->GetFlags()+1);
    }
    BlueSystemMessage(m_session, "Gameobject opened/closed.");
    return true;
}