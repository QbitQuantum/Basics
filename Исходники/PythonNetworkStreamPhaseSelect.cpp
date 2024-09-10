bool CPythonNetworkStream::__RecvChangeName()
{
    TPacketGCChangeName ChangeNamePacket;
    if (!Recv(sizeof(TPacketGCChangeName), &ChangeNamePacket))
        return false;

    for (int i = 0; i < PLAYER_PER_ACCOUNT4; ++i)
    {
        if (ChangeNamePacket.pid == m_akSimplePlayerInfo[i].dwID)
        {
            m_akSimplePlayerInfo[i].bChangeName = FALSE;
            strncpy(m_akSimplePlayerInfo[i].szName, ChangeNamePacket.name, CHARACTER_NAME_MAX_LEN);

            PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_SELECT], "OnChangeName", Py_BuildValue("(is)", i, ChangeNamePacket.name));
            return true;
        }
    }

    PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_SELECT], "OnCreateFailure", Py_BuildValue("(i)", 100));
    return true;
}