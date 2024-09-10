std::string ASE::QueryLight ( void )
{
    std::stringstream reply;

    int iJoinedPlayers = m_pPlayerManager->CountJoined ();
    int iMaxPlayers = m_pMainConfig->GetMaxPlayers ();
    SString strPlayerCount = SString ( "%d/%d", iJoinedPlayers, iMaxPlayers );

    reply << "EYE2";
    // game
    reply << ( unsigned char ) 4;
    reply << "mta";
    // port
    reply << ( unsigned char ) ( m_strPort.length() + 1 );
    reply << m_strPort;
    // server name
    reply << ( unsigned char ) ( m_pMainConfig->GetServerName ().length() + 1 );
    reply << m_pMainConfig->GetServerName ();
    // game type
    reply << ( unsigned char ) ( m_strGameType.length() + 1 );
    reply << m_strGameType;
    // map name with backwardly compatible large player count
    reply << ( unsigned char ) ( m_strMapName.length() + 1 + strPlayerCount.length () + 1 );
    reply << m_strMapName;
    reply << ( unsigned char ) 0;
    reply << strPlayerCount;
    // version
    std::string temp = MTA_DM_ASE_VERSION;
    reply << ( unsigned char ) ( temp.length() + 1 );
    reply << temp;
    // passworded
    reply << ( unsigned char ) ( ( m_pMainConfig->HasPassword () ) ? 1 : 0 );
    // serial verification?
    reply << ( unsigned char ) ( ( m_pMainConfig->GetSerialVerificationEnabled() ) ? 1 : 0 );
    // players count
    reply << ( unsigned char ) Min ( iJoinedPlayers, 255 );
    // players max
    reply << ( unsigned char ) Min ( iMaxPlayers, 255 );

    // players
    CPlayer* pPlayer = NULL;

    list < CPlayer* > ::const_iterator pIter = m_pPlayerManager->IterBegin ();
    for ( ; pIter != m_pPlayerManager->IterEnd (); pIter++ )
    {
        pPlayer = *pIter;
        if ( pPlayer->IsJoined () )
        {
            // nick
            std::string strPlayerName = RemoveColorCode ( pPlayer->GetNick () );
            if ( strPlayerName.length () == 0 )
                strPlayerName = pPlayer->GetNick ();
            reply << ( unsigned char ) ( strPlayerName.length () + 1 );
            reply << strPlayerName.c_str ();
        }
    }

    return reply.str();
}