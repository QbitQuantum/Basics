/**
 *  \brief Returns the recording we should switch to
 *
 *   This returns a ProgramInfo* and tells us if this is a discontiuous
 *   switch and whether the recording type is changing.
 *
 *   This also clears the NeedsToSwitch()/NeedsToJump() state.
 *
 *   NOTE: The caller is resposible for deleting the ProgramInfo
 */
ProgramInfo *LiveTVChain::GetSwitchProgram(bool &discont, bool &newtype,
                                           int &newid)
{
    ReloadAll();
    QMutexLocker lock(&m_lock);

    if (m_switchid < 0 || m_curpos == m_switchid)
    {
        ClearSwitch();
        return NULL;
    }

    LiveTVChainEntry oldentry, entry;
    GetEntryAt(m_curpos, oldentry);

    ProgramInfo *pginfo = NULL;
    while (!pginfo && m_switchid < (int)m_chain.count() && m_switchid >= 0)
    {
        GetEntryAt(m_switchid, entry);

        bool at_last_entry = 
            ((m_switchid > m_curpos) &&
             (m_switchid == (int)(m_chain.count()-1))) ||
            ((m_switchid <= m_curpos) && (m_switchid == 0));

        // Skip dummy recordings, if possible.
        if (at_last_entry || (entry.cardtype != "DUMMY"))
            pginfo = EntryToProgram(entry);

        // Skip empty recordings, if possible
        if (pginfo && (0 == pginfo->GetFilesize()) &&
            m_switchid < (int)(m_chain.count()-1))
        {
            LOG(VB_GENERAL, LOG_WARNING,
                QString("Skipping empty program %1")
                .arg(pginfo->MakeUniqueKey()));
            delete pginfo;
            pginfo = NULL;
        }

        if (!pginfo)
        {
            if (m_switchid > m_curpos)
                m_switchid++;
            else
                m_switchid--;
        }
    }

    if (!pginfo)
    {
        ClearSwitch();
        return NULL;
    }

    discont = true;
    if (m_curpos == m_switchid - 1)
        discont = entry.discontinuity;

    newtype = (oldentry.cardtype != entry.cardtype);

    // Some cards can change their streams dramatically on a channel change...
    if (discont)
        newtype |= CardUtil::IsChannelChangeDiscontinuous(entry.cardtype);

    newid = m_switchid;

    ClearSwitch();

    return pginfo;
}