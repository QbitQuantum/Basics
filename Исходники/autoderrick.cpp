void CAutoDerrick::DeleteObject(bool bAll)
{
    CObject*    fret;

    if ( !bAll )
    {
        fret = SearchFret();
        if ( fret != 0 && fret->GetLock() )
        {
            fret->DeleteObject();
            delete fret;
        }
    }

    if ( m_soundChannel != -1 )
    {
        m_sound->FlushEnvelope(m_soundChannel);
        m_sound->AddEnvelope(m_soundChannel, 0.0f, 1.0f, 1.0f, SOPER_STOP);
        m_soundChannel = -1;
    }

    CAuto::DeleteObject(bAll);
}