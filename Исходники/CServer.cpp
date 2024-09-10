void CServer::DoPulse()
{
    UNCLOCK( "Top", "Other" );
    if ( m_pGame )
    {
        CLOCK( "Top", "Game->DoPulse" );
        m_pGame->DoPulse ();
        UNCLOCK( "Top", "Game->DoPulse" );
    }
    CLOCK( "Top", "Other" );
}