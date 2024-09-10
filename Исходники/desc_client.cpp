void CLIENT_DESC::SetPhase(int iPhase)
{
    switch (iPhase)
    {
    case PHASE_CLIENT_CONNECTING:
        sys_log(1, "PHASE_CLIENT_DESC::CONNECTING");
        m_pInputProcessor = NULL;
        break;

    case PHASE_DBCLIENT:
    {
        sys_log(1, "PHASE_DBCLIENT");

        if (!g_bAuthServer)
        {
            static bool bSentBoot = false;

            if (!bSentBoot)
            {
                bSentBoot = true;
                TPacketGDBoot p;
                p.dwItemIDRange[0] = 0;
                p.dwItemIDRange[1] = 0;
                memcpy(p.szIP, g_szPublicIP, 16);
                DBPacket(HEADER_GD_BOOT, 0, &p, sizeof(p));
            }
        }

        TEMP_BUFFER buf;

        TPacketGDSetup p;

        memset(&p, 0, sizeof(p));
        strlcpy(p.szPublicIP, g_szPublicIP, sizeof(p.szPublicIP));

        if (!g_bAuthServer)
        {
            p.bChannel	= g_bChannel;
            p.wListenPort = mother_port;
            p.wP2PPort	= p2p_port;
            p.bAuthServer = false;
            map_allow_copy(p.alMaps, 32);

            const DESC_MANAGER::DESC_SET & c_set = DESC_MANAGER::instance().GetClientSet();
            DESC_MANAGER::DESC_SET::const_iterator it;

            for (it = c_set.begin(); it != c_set.end(); ++it)
            {
                LPDESC d = *it;

                if (d->GetAccountTable().id != 0)
                    ++p.dwLoginCount;
            }

            buf.write(&p, sizeof(p));

            if (p.dwLoginCount)
            {
                TPacketLoginOnSetup pck;

                for (it = c_set.begin(); it != c_set.end(); ++it)
                {
                    LPDESC d = *it;

                    TAccountTable & r = d->GetAccountTable();

                    if (r.id != 0)
                    {
                        pck.dwID = r.id;
                        strlcpy(pck.szLogin, r.login, sizeof(pck.szLogin));
                        strlcpy(pck.szSocialID, r.social_id, sizeof(pck.szSocialID));
                        strlcpy(pck.szHost, d->GetHostName(), sizeof(pck.szHost));
                        pck.dwLoginKey = d->GetLoginKey();
#ifndef _IMPROVED_PACKET_ENCRYPTION_
                        thecore_memcpy(pck.adwClientKey, d->GetDecryptionKey(), 16);
#endif

                        buf.write(&pck, sizeof(TPacketLoginOnSetup));
                    }
                }
            }

            sys_log(0, "DB_SETUP current user %d size %d", p.dwLoginCount, buf.size());

            // 파티를 처리할 수 있게 됨.
            CPartyManager::instance().EnablePCParty();
            //CPartyManager::instance().SendPartyToDB();
        }
        else
        {
            p.bAuthServer = true;
            buf.write(&p, sizeof(p));
        }

        DBPacket(HEADER_GD_SETUP, 0, buf.read_peek(), buf.size());
        m_pInputProcessor = &m_inputDB;
    }
    break;

    case PHASE_P2P:
        sys_log(1, "PHASE_P2P");

        if (m_lpInputBuffer)
            buffer_reset(m_lpInputBuffer);

        if (m_lpOutputBuffer)
            buffer_reset(m_lpOutputBuffer);

        m_pInputProcessor = &m_inputP2P;
        break;

    case PHASE_CLOSE:
        m_pInputProcessor = NULL;
        break;

    case PHASE_TEEN:
        m_inputTeen.SetStep(0);
        m_pInputProcessor = &m_inputTeen;
        break;

    }

    m_iPhase = iPhase;
}