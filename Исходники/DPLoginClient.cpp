void CDPLoginClient::SendCreatePlayer(BYTE nSlot, LPCSTR lpszPlayer/*, LPDWORD adwEquipment*/, BYTE nFace, BYTE nCostume, BYTE nSkinSet, BYTE nHairMesh, DWORD dwHairColor, BYTE nSex, BYTE nJob, BYTE nHeadMesh )
#endif // __2ND_PASSWORD_SYSTEM
{
    BEFORESENDSOLE( ar, PACKETTYPE_CREATE_PLAYER, DPID_UNKNOWN );
#ifdef __GPAUTH_01
    ar.WriteString( g_Neuz.m_bGPotatoAuth?g_Neuz.m_szGPotatoNo: g_Neuz.m_szAccount );
#else	// __GPAUTH_01
    ar.WriteString( g_Neuz.m_szAccount );
#endif	// __GPAUTH_01
    ar.WriteString( g_Neuz.m_szPassword );
    ar << nSlot;

    if( strlen( lpszPlayer ) > 16 )
        Error( "CDPLoginClient::SendCreatePlayer에서 이상 캐릭터 명 E: %s", lpszPlayer );
    ar.WriteString( lpszPlayer );
    if( strlen( lpszPlayer ) > 16 )
        Error( "CDPLoginClient::SendCreatePlayer에서 이상 캐릭터 명 F: %s", lpszPlayer );

    //	ar.Write( adwEquipment, sizeof(DWORD) * MAX_HUMAN_PARTS );

    ar << nFace << nCostume << nSkinSet << nHairMesh;
    ar << dwHairColor;
    ar << nSex << nJob << nHeadMesh;
#if __VER >= 15 // __2ND_PASSWORD_SYSTEM
    ar << nBankPW;
#endif // __2ND_PASSWORD_SYSTEM
    ar << g_Neuz.m_dwAuthKey;
    SEND( ar, this, DPID_SERVERPLAYER );
}